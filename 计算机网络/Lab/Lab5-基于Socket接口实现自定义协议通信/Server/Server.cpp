#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

#define MaxClient 10
#define MaxBufSize 1024
#define _CRT_SECURE_NO_WARINGS

#include <cstdio>
#include<iostream>
#include<string>
#include<WinSock2.h>
#include<ctime>
#include<vector>

using namespace std;
const int PORT = 4392; //设置监听端口为4392
using client = pair<SOCKET*, int>;
vector<client> clients; //已连接的用户列表

//服务线程
DWORD WINAPI ServerThread(LPVOID lpParameter) {
	SOCKET* ClientSocket = (SOCKET*)lpParameter;
	int receByt = 0;
	char RecvBuf[MaxBufSize];
	char SendBuf[MaxBufSize];
	while (1) {
		receByt = recv(*ClientSocket, RecvBuf, sizeof(RecvBuf), 0);
		//buf[receByt]='\0';
		if (receByt > 0) {
			cout << "[system] Recieve message: " << RecvBuf << " -- from client " << *ClientSocket << endl;
			//cout << receByt << endl;

			switch (RecvBuf[0])
			{
			case 't':		// 服务端所在机器的当前时间
			{
				time_t now = time(0); // 把 now 转换为字符串形式
				char* dt = ctime(&now);
				cout << "[system] Local date & time: " << dt << endl;
				SendBuf[0] = 't';
				strcpy((SendBuf + 1), dt);

				int k = 0;
				k = send(*ClientSocket, SendBuf, sizeof(SendBuf), 0);
				if (k < 0) {
					cout << "[system] Send failed!" << endl;
				}

				memset(SendBuf, 0, sizeof(SendBuf));
				break;
			}
			case 'n':		// 服务端所在机器的名称
			{
				DWORD ComputerNameLength = MAX_COMPUTERNAME_LENGTH + 1;
				strcpy(SendBuf, "n");

				TCHAR t_name[MAX_COMPUTERNAME_LENGTH + 1];
				GetComputerName(t_name, &ComputerNameLength); //获取本机名称
				char name[MAX_COMPUTERNAME_LENGTH + 1];
				wcstombs(name, t_name, MAX_COMPUTERNAME_LENGTH + 1);
				strcat(SendBuf, name);

				int k = 0;
				k = send(*ClientSocket, SendBuf, sizeof(SendBuf), 0);
				if (k < 0) {
					cout << "[system] Send failed!" << endl;
				}
				cout << "[system] Server's machine name: " << SendBuf + 1 << endl;

				memset(SendBuf, 0, sizeof(SendBuf));
				break;
			}
			case 'l':		// 当前连接的所有客户端信息
			{
				for (auto iter : clients)
				{
					cout << iter.second << endl;
				}
				cout << endl;
				SendBuf[0] = 'l';
				SendBuf[1] = clients.size();
				//int offset = 2;
				char Buf[4] = { 0 };
				for (auto iter : clients)
				{
					char Buf[4] = { 0 };
					itoa(iter.second, Buf, 10);
					strcat(SendBuf, Buf);
				}

				int k = 0;
				k = send(*ClientSocket, SendBuf, sizeof(SendBuf), 0);
				if (k < 0) {
					cout << "[system] Send failed!" << endl;
				}

				memset(SendBuf, 0, sizeof(SendBuf));
				break;
			}
			case 's':
			{
				char dst_port[10];
				//提取接收方id
				int idx = 1;
				while (RecvBuf[idx] != '&') {
					dst_port[idx - 1] = RecvBuf[idx];
					idx++;
				}

				int dst_port_id = atoi(dst_port);
				SOCKET* dst_client = NULL;

				for (auto iter : clients)
				{
					if (iter.second == dst_port_id)
					{
						dst_client = iter.first;
						break;
					}
				}
				if (!dst_client)
				{
					cout << "[system] Client(" << dst_port_id << ") is not connected" << endl;
					//发个反馈包
					strcpy(SendBuf, "eInvalid receiver ID!");
					send(*ClientSocket, SendBuf, sizeof(SendBuf), 0);
					break;
				}

				memset(SendBuf, 0, sizeof(SendBuf));
				SendBuf[0] = 's';
				char Buf[4] = { 0 };
				for (auto iter : clients)
				{
					if (iter.first == ClientSocket)
					{
						itoa(iter.second, Buf, 10);
						strcat(SendBuf, Buf);
						break;
					}
				}
				strcat_s(SendBuf, RecvBuf + idx + 1);

				int k = 0;
				k = send(*dst_client, SendBuf, sizeof(SendBuf), 0);
				if (k < 0) {
					cout << "[system] Send failed!" << endl;
				}
				cout << "[system] Sender(" << *ClientSocket << ") Receiver(" << *dst_client << ")" << endl;
				cout << "         Message is :" << SendBuf << endl;
				//发个反馈包
				strcpy(SendBuf, "eSuccessfully sent!");
				send(*ClientSocket, SendBuf, sizeof(SendBuf), 0);
				memset(SendBuf, 0, sizeof(SendBuf));
				break;
			}
			case 'c'://返回用户id
			{
				strcpy(SendBuf, "c");
				int id = *ClientSocket;
				char usr_id[10];
				strcat(SendBuf, itoa(id, usr_id, 10));
				int k = 0;
				k = send(*ClientSocket, SendBuf, sizeof(SendBuf), 0);
				if (k < 0) {
					cout << "[system] Send failed!" << endl;
				}

				memset(SendBuf, 0, sizeof(SendBuf));
				break;
			}
			default:
				cout << "Undefined Behavior" << endl; break;
			}
		}
		else
		{
			cout << "[system] Client(" << *ClientSocket << ") has been disconnected" << endl;

			for (auto iter = clients.begin(); iter != clients.end(); iter++) {
				if ((*iter).first == ClientSocket) {
					iter = clients.erase(iter);
					break;
				}
			}
			break;
		}

		memset(RecvBuf, 0, sizeof(RecvBuf));
	}
	closesocket(*ClientSocket);
	free(ClientSocket);
	return 0;
}

int main() {
	WSAData wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	cout << "[initialize] Socket initialized!" << endl;
	SOCKADDR_IN ListenAddr;
	ListenAddr.sin_family = AF_INET;
	ListenAddr.sin_addr.S_un.S_addr = INADDR_ANY;//表示填入本机ip
	ListenAddr.sin_port = htons(PORT);
	int n;
	n = bind(ListenSocket, (LPSOCKADDR)&ListenAddr, sizeof(ListenAddr));
	if (n == SOCKET_ERROR) {
		cout << "[initialize] Bind failed!" << endl;
		return -1;
	}
	else {
		cout << "[initialize] Bind Port " << PORT << " succeded!" << endl;
	}
	int l = listen(ListenSocket, 20);
	cout << "[initialize] Wating for clients ..." << endl;

	while (1) {
		//循环接收客户端连接请求并创建服务线程
		SOCKET* ClientSocket = new SOCKET;
		ClientSocket = (SOCKET*)malloc(sizeof(SOCKET));
		//接收客户端连接请求
		int SockAddrlen = sizeof(sockaddr);
		*ClientSocket = accept(ListenSocket, 0, 0);
		clients.push_back(make_pair(ClientSocket, int(*ClientSocket)));

		cout << "[system] Client(" << *ClientSocket << ") has been connected" << endl;
		CreateThread(NULL, 0, &ServerThread, ClientSocket, 0, NULL);
	}
	closesocket(ListenSocket);
	WSACleanup();
	return(0);
}