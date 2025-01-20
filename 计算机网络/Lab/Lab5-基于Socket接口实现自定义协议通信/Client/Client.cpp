#pragma comment(lib,"ws2_32.lib")

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define MaxBufSize 1024

#include <cstdio>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

void Ini();            //初始化
void PrintMenu();      //打印服务菜单
void Handle();         //处理键盘输入
void PrintUsrPrefix(); //输出用户操作前缀
void Menu_handle();    //处理用户在menu中的方向键选择
void Handle_num(int c_num);     //处理menu命令
void Print_line(int line_no, bool connect_status); //打印menu中的一行
bool connect_server();        //连接服务器，返回是否成功
void send_message();          //发送信息
void reqiure_time();          //向服务器请求时间
void reqiure_name();          //向都武器请求机器名称
void require_list();          //请求用户列表
DWORD WINAPI RecvHandleThread(LPVOID lpParameter);         //接受数据子线程

SOCKET c_socket;       //连接套接字
struct sockaddr_in addr_server; //服务器地址信息
char RecvBuff[MaxBufSize];
HANDLE hThread; //监听线程句柄

bool connect_status;   //连接状态
HANDLE hConsole;       //用于更改文本颜色
char usr_name[26];     //用户名
char line[7][36] = {   //已连接时可选菜单
	"Disconnect and Exit.[↑]           ",
	"Send message to chosen user.[↑/↓]" ,
	"Show the user list.[↑/↓]         ",
	"Get your user name.[↑/↓]         ",
	"Get current time.[↑/↓]           ",
	"Disconnect from the server. [↑/↓]",
	"Connect to the chosen server. [↓] "
};
char dis_line[2][36] = {//未连接时可选菜单
	"Exit.[↑]                          ",
	"Connect to the chosen server. [↓] "
};

int main(void) {
	Ini();             //初始化

	system("pause");
	return 0;
}

//初始化
void Ini() {
	connect_status = false;                     //初始化连接状态
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //用于更改文本颜色

	//处理用户名
	FILE* fp;
	fp = fopen("usr", "r");
	if (!fp) {
		//初始运行：要求用户输入用户名
		printf("Pleas input user name: ");
		scanf("%s", usr_name);
		fp = fopen("usr", "w");
		fwrite(usr_name, sizeof(usr_name), 1, fp);
		fclose(fp);
	}
	else {
		//读取已有用户名
		fscanf(fp, "%s", usr_name);
		fclose(fp);
	}

	//Socket初始化放到connect里去了 -- 避免重新连接时出错

	//初始操作提示
	printf("[system] Hello, "); SetConsoleTextAttribute(hConsole, 0x3); printf("%s", usr_name); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
	printf("[system] You can use -h to view the Help Menu!\n");
	PrintUsrPrefix();

	//处理用户输入
	Handle();

	return;
}

//打印服务菜单
void PrintMenu() {
	printf("[system] Supported functions are as follows:\n");
	printf("         Use [↑] [↓] + Enter to choose, Esc to quit.\n");
	printf("+---------------------+-------------------------------+\n");
	printf("|       Command       |            Function           |\n");
	printf("+---------------------+-------------------------------+\n");
	if (connect_status) {
		printf("| -c (host_ip) (port) | Connect to the chosen server. |\n");
		printf("|         -d          | Disconnect from the server.   |\n");
		printf("|         -t          | Get current time.             |\n");
		printf("|         -n          | Get your user name.           |\n");
		printf("|         -l          | Show the user list.           |\n");
		printf("| -s (name) (message) | Send message to chosen user.  |\n");
		printf("|         -e          | Disconnect and Exit.          |\n");
	}
	else {
		printf("| -c (host_ip) (port) | Connect to the chosen server. |\n");
		printf("|         -e          | Exit.                         |\n");
	}
	printf("+---------------------+-------------------------------+\n");

	Menu_handle(); //处理用户在menu中的选择操作
	return;
}

//处理键盘输入
void Handle() {
	char str[101];
	while (1) {
		scanf("%s", str);
		if (str[0] != '-') {
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Syntax Error"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		}
		else {
			switch (str[1]) {
			case 'c':
				//连接成功/失败反馈
				connect_status = connect_server();
				break;
			case 'd':
			{
				//关闭连接
				if (!connect_status) {
					printf("[system] You are not connected.\n");
					break;
				}
				//关闭连接
				int iResult = shutdown(c_socket, SD_SEND);
				if (iResult == SOCKET_ERROR) {
					cout << "[system] Shutdown failed" << endl;
					WSAGetLastError();
					closesocket(c_socket);
					WSACleanup();
				}
				printf("[system] Connection has been closed.\n");
				connect_status = false;
				break;
			}
			case 't':
				//time
				reqiure_time();
				break;
			case 'n':
				//name
				reqiure_name();
				break;
			case 'l':
				//usr list
				require_list();
				break;
			case 's':
				//send msg
				send_message();
				break;
			case 'e':
				//关闭连接并退出
				if (connect_status) {
					closesocket(c_socket);  //关闭套接字
					WSACleanup();
					CloseHandle(hThread);
					printf("[system] Connection has been closed. Bye, "); SetConsoleTextAttribute(hConsole, 0x3); printf("%s", usr_name); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
					connect_status = false;
				}
				else {
					printf("[system] Bye, "); SetConsoleTextAttribute(hConsole, 0x3); printf("%s", usr_name); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
					system("pause");
					exit(0);
				}
				return;
			case 'h':
				PrintMenu();
				break;
			default:
				printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Syntax Error"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
				break;
			}
		}
		PrintUsrPrefix();
	}
	return;
}

//输出用户操作前缀
void PrintUsrPrefix() {
	SetConsoleTextAttribute(hConsole, 0x3);
	printf("[%s] ", usr_name);
	SetConsoleTextAttribute(hConsole, 0x7);
	return;
}

//处理用户在menu中的选择操作
void Menu_handle() {
	printf(" Your choice: ");
	if (connect_status) Print_line(6, true);
	else Print_line(1, false);
	int cur_line = connect_status ? 6 : 1;
	int ch;
	while (1) {
		if (_kbhit()) {
			ch = _getch();
			switch (ch) {
			case 80:
				//down
				if (cur_line) {
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					Print_line(--cur_line, connect_status);
				}
				break;
			case 72:
				//up
				if ((connect_status && cur_line != 6) || (!connect_status && cur_line != 1)) {
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					Print_line(++cur_line, connect_status);
				}
				break;
			case 27://esc
				printf("\n");
				return;
			case 13://enter
				//处理请求
				printf("\n");
				Handle_num(cur_line);
				return;
			default:
				break;
			}
		}
	}
	return;
}

//以蓝色打印指令
void Print_line(int line_no, bool connect_status) {
	SetConsoleTextAttribute(hConsole, 0x3);
	if (connect_status) printf("%s", line[line_no]);
	else printf("%s", dis_line[line_no]);
	SetConsoleTextAttribute(hConsole, 0x7);
	return;
}

//处理menu命令
void Handle_num(int c_num) {
	if (connect_status) {
		//已连接状态下
		switch (c_num) {
		case 6:
			//连接成功/失败反馈
			connect_status = connect_server();
			break;
		case 5:
		{
			//关闭连接
			int iResult = shutdown(c_socket, SD_SEND);
			if (iResult == SOCKET_ERROR) {
				cout << "[system] Shutdown failed" << endl;
				WSAGetLastError();
				closesocket(c_socket);//关闭套接字
				WSACleanup();
			}
			printf("[system] Connection has been closed.\n");
			connect_status = false;
			break;
		}
		case 4:
			//time
			reqiure_time();
			break;
		case 3:
			//name
			reqiure_name();
			break;
		case 2:
			//usr list
			require_list();
			break;
		case 1:
			//send msg
			send_message();
			break;
		case 0:
		{
			//关闭连接并退出
			int iResult = shutdown(c_socket, SD_SEND);
			if (iResult == SOCKET_ERROR) {
				cout << "[system] Shutdown failed" << endl;
				WSAGetLastError();
				closesocket(c_socket);//关闭套接字
				WSACleanup();
			}
			CloseHandle(hThread);
			printf("[system] Connection has been closed. Bye, "); SetConsoleTextAttribute(hConsole, 0x3); printf("%s", usr_name); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			connect_status = false;
			system("pause");
			exit(0);
		}
		default:
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Menu Selection Error"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			break;
		}
	}
	else {
		//未连接状态下
		switch (c_num) {
		case 0:
			//退出
			printf("[system] Bye, "); SetConsoleTextAttribute(hConsole, 0x3); printf("%s", usr_name); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			system("pause");
			exit(0);
		case 1:
			//连接成功/失败反馈
			connect_status = connect_server();
			break;
		default:
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Menu Selection Error"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			break;
		}
	}
	return;
}

//连接服务器，返回是否成功
bool connect_server() {
	if (connect_status) {
		//避免重复连接
		printf("[system] You has been connected\n");
		return true;
	}

	char server_ip[18];   //服务器地址
	int server_port = -1; //端口号

	//WinSock初始化
	WORD RequestVersion = MAKEWORD(2, 2);//希望使用的WinSock DLL的版本
	WSADATA Data;
	int startup = WSAStartup(RequestVersion, &Data);
	if (startup) {
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("WSAStartup() error"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		system("pause");
		exit(-1);
	}

	//确认WinSock DLL支持版本2.2
	if (LOBYTE(Data.wVersion) != 2 || HIBYTE(Data.wVersion) != 2)
	{
		WSACleanup();
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Invalid Winsock version"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		system("pause");
		exit(-1);
	}

	//调用socket()，向系统申请socket句柄
	c_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c_socket == INVALID_SOCKET) {
		WSACleanup();
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("socket() error!"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		system("pause");
		exit(-1);
	}

	//提示输入服务器地址 & 端口
	printf("[system] Please input srvers's ip: "); SetConsoleTextAttribute(hConsole, 0x3);
	scanf("%s", server_ip); SetConsoleTextAttribute(hConsole, 0x7);
	printf("[system] Please input port number: "); SetConsoleTextAttribute(hConsole, 0x3);
	scanf("%d", &server_port); SetConsoleTextAttribute(hConsole, 0x7);

	//构建服务器地址信息
	addr_server.sin_family = AF_INET;//地址家族
	addr_server.sin_port = htons(server_port);//注意转化为网络字节序
	addr_server.sin_addr.S_un.S_addr = inet_addr(server_ip);

	//连接服务器
	if (connect(c_socket, (struct sockaddr*)&addr_server, sizeof(addr_server)) == SOCKET_ERROR) {
		//失败提示
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Connection failed"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		return false;
	}
	else {
		//连接成功
		printf("[system] Successfully connect to the sever!\n");
		//创建接受服务器回复的线程
		hThread = CreateThread(NULL, 0, &RecvHandleThread, &c_socket, 0, NULL);

		//发送一个连接请求包 - 拿到自己的id
		char SendBuff[2] = "c";
		int status = send(c_socket, SendBuff, sizeof(SendBuff), 0);
		connect_status = true;
		return true;
	}
}

DWORD WINAPI RecvHandleThread(LPVOID lpParameter)
{
	SOCKET* SocketClient = (SOCKET*)lpParameter;

	char RecvBuff[MaxBufSize];

	while (1) {
		int n = 0;
		n = recv(*SocketClient, RecvBuff, sizeof(RecvBuff), 0);

		if (n > 0) {
			SetConsoleTextAttribute(hConsole, 0x6);
			cout << "\n[server] ";
			switch (RecvBuff[0]) {
			case 'e': //服务器对信息转发的反馈
			{
				cout << RecvBuff + 1 << endl;
				PrintUsrPrefix();
				break;
			}
			case 't':
				cout << "Current time is: " << RecvBuff + 1;
				PrintUsrPrefix();
				break;
			case 'n':
				cout << "Server machine's name: " << RecvBuff + 1 << endl;
				PrintUsrPrefix();
				break;
			case 'l':
			{
				int n_clients = int(RecvBuff[1]);
				cout << "Total number of clients connected to the server: " << n_clients << endl;
				cout << "+----------------------+" << endl;
				cout << "|     User Id List     |" << endl;
				cout << "+----------------------+" << endl;
				for (int i = 0; i < n_clients; i++) {
					char Buf[4];
					strncpy_s(Buf, RecvBuff + 2 + 3 * i, 3);
					cout << "|         " << atoi(Buf) << "          |" << endl;
				}
				cout << "+----------------------+" << endl;
				PrintUsrPrefix();
				break;
			}
			case 's':
			{
				char Buf[4] = { 0 };
				strncpy_s(Buf, RecvBuff + 1, 3);
				int src_socket_id = atoi(Buf);
				cout << "Message from [" << src_socket_id << "]: " << RecvBuff + 4 << endl;
				PrintUsrPrefix();
				break;
			}
			case 'c':
			{
				char ID[10];
				strcpy(ID, RecvBuff + 1);
				cout << "Your ID is: " << ID << endl;
				PrintUsrPrefix();
				break;
			}
			default:
				cout << endl;
				break;
			}
		}
		::memset(RecvBuff, 0, sizeof(RecvBuff));
	}
}

//发送信息
void send_message() {
	if (connect_status) {
		int rec_id = -1;
		char info[1024], SendBuff[MaxBufSize] = "s";
		char recv_id[10];
		//读取接收方id
		cout << "[system] Please input receiver's id: "; SetConsoleTextAttribute(hConsole, 0x3);
		cin >> rec_id; getchar();  SetConsoleTextAttribute(hConsole, 0x7);
		_itoa(rec_id, recv_id, 10);
		strcat(recv_id, "&");

		//读取待发送信息
		cout << "[system] Please input message to be sent: "; SetConsoleTextAttribute(hConsole, 0x3);
		gets_s(info); SetConsoleTextAttribute(hConsole, 0x7);

		//处理用户输入
		strcat(SendBuff, recv_id);
		strcat(SendBuff, info);
		int status = send(c_socket, SendBuff, sizeof(SendBuff), 0);
		if (status < 0) {
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Send failed"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			return;
		}
		//Sleep(100);
		return;
	}
	else {
		//未连接提示
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("No server connected"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		return;
	}
}

//向服务器请求时间
void reqiure_time() {
	if (connect_status) {
		char SendBuff[2] = "t";
		int status = send(c_socket, SendBuff, sizeof(SendBuff), 0);
		if (status < 0) {
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Send failed"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			return;
		}
		else {
			//成功到达服务器
			return;
		}
		//Sleep(100);
		return;
	}
	else {
		//未连接提示
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("No server connected"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		return;
	}
	return;
}

//请求服务器机器名
void reqiure_name() {
	if (connect_status) {
		char SendBuff[2] = "n";
		int status = send(c_socket, SendBuff, sizeof(SendBuff), 0);
		if (status < 0) {
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Send failed"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			return;
		}
		else {
			//成功到达服务器
			return;
		}
		//Sleep(100);
		return;
	}
	else {
		//未连接提示
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("No server connected"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		return;
	}
	return;
}

//请求用户列表
void require_list() {
	if (connect_status) {
		char SendBuff[2] = "l";
		int status = send(c_socket, SendBuff, sizeof(SendBuff), 0);
		if (status < 0) {
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Send failed"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			return;
		}
		else {
			//成功到达服务器
			return;
		}
		//Sleep(100);
		return;
	}
	else {
		//未连接提示
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("No server connected"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		return;
	}
	return;
}