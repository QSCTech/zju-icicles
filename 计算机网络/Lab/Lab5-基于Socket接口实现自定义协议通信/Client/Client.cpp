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

void Ini();            //��ʼ��
void PrintMenu();      //��ӡ����˵�
void Handle();         //�����������
void PrintUsrPrefix(); //����û�����ǰ׺
void Menu_handle();    //�����û���menu�еķ����ѡ��
void Handle_num(int c_num);     //����menu����
void Print_line(int line_no, bool connect_status); //��ӡmenu�е�һ��
bool connect_server();        //���ӷ������������Ƿ�ɹ�
void send_message();          //������Ϣ
void reqiure_time();          //�����������ʱ��
void reqiure_name();          //�����������������
void require_list();          //�����û��б�
DWORD WINAPI RecvHandleThread(LPVOID lpParameter);         //�����������߳�

SOCKET c_socket;       //�����׽���
struct sockaddr_in addr_server; //��������ַ��Ϣ
char RecvBuff[MaxBufSize];
HANDLE hThread; //�����߳̾��

bool connect_status;   //����״̬
HANDLE hConsole;       //���ڸ����ı���ɫ
char usr_name[26];     //�û���
char line[7][36] = {   //������ʱ��ѡ�˵�
	"Disconnect and Exit.[��]           ",
	"Send message to chosen user.[��/��]" ,
	"Show the user list.[��/��]         ",
	"Get your user name.[��/��]         ",
	"Get current time.[��/��]           ",
	"Disconnect from the server. [��/��]",
	"Connect to the chosen server. [��] "
};
char dis_line[2][36] = {//δ����ʱ��ѡ�˵�
	"Exit.[��]                          ",
	"Connect to the chosen server. [��] "
};

int main(void) {
	Ini();             //��ʼ��

	system("pause");
	return 0;
}

//��ʼ��
void Ini() {
	connect_status = false;                     //��ʼ������״̬
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //���ڸ����ı���ɫ

	//�����û���
	FILE* fp;
	fp = fopen("usr", "r");
	if (!fp) {
		//��ʼ���У�Ҫ���û������û���
		printf("Pleas input user name: ");
		scanf("%s", usr_name);
		fp = fopen("usr", "w");
		fwrite(usr_name, sizeof(usr_name), 1, fp);
		fclose(fp);
	}
	else {
		//��ȡ�����û���
		fscanf(fp, "%s", usr_name);
		fclose(fp);
	}

	//Socket��ʼ���ŵ�connect��ȥ�� -- ������������ʱ����

	//��ʼ������ʾ
	printf("[system] Hello, "); SetConsoleTextAttribute(hConsole, 0x3); printf("%s", usr_name); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
	printf("[system] You can use -h to view the Help Menu!\n");
	PrintUsrPrefix();

	//�����û�����
	Handle();

	return;
}

//��ӡ����˵�
void PrintMenu() {
	printf("[system] Supported functions are as follows:\n");
	printf("         Use [��] [��] + Enter to choose, Esc to quit.\n");
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

	Menu_handle(); //�����û���menu�е�ѡ�����
	return;
}

//�����������
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
				//���ӳɹ�/ʧ�ܷ���
				connect_status = connect_server();
				break;
			case 'd':
			{
				//�ر�����
				if (!connect_status) {
					printf("[system] You are not connected.\n");
					break;
				}
				//�ر�����
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
				//�ر����Ӳ��˳�
				if (connect_status) {
					closesocket(c_socket);  //�ر��׽���
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

//����û�����ǰ׺
void PrintUsrPrefix() {
	SetConsoleTextAttribute(hConsole, 0x3);
	printf("[%s] ", usr_name);
	SetConsoleTextAttribute(hConsole, 0x7);
	return;
}

//�����û���menu�е�ѡ�����
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
				//��������
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

//����ɫ��ӡָ��
void Print_line(int line_no, bool connect_status) {
	SetConsoleTextAttribute(hConsole, 0x3);
	if (connect_status) printf("%s", line[line_no]);
	else printf("%s", dis_line[line_no]);
	SetConsoleTextAttribute(hConsole, 0x7);
	return;
}

//����menu����
void Handle_num(int c_num) {
	if (connect_status) {
		//������״̬��
		switch (c_num) {
		case 6:
			//���ӳɹ�/ʧ�ܷ���
			connect_status = connect_server();
			break;
		case 5:
		{
			//�ر�����
			int iResult = shutdown(c_socket, SD_SEND);
			if (iResult == SOCKET_ERROR) {
				cout << "[system] Shutdown failed" << endl;
				WSAGetLastError();
				closesocket(c_socket);//�ر��׽���
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
			//�ر����Ӳ��˳�
			int iResult = shutdown(c_socket, SD_SEND);
			if (iResult == SOCKET_ERROR) {
				cout << "[system] Shutdown failed" << endl;
				WSAGetLastError();
				closesocket(c_socket);//�ر��׽���
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
		//δ����״̬��
		switch (c_num) {
		case 0:
			//�˳�
			printf("[system] Bye, "); SetConsoleTextAttribute(hConsole, 0x3); printf("%s", usr_name); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			system("pause");
			exit(0);
		case 1:
			//���ӳɹ�/ʧ�ܷ���
			connect_status = connect_server();
			break;
		default:
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Menu Selection Error"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			break;
		}
	}
	return;
}

//���ӷ������������Ƿ�ɹ�
bool connect_server() {
	if (connect_status) {
		//�����ظ�����
		printf("[system] You has been connected\n");
		return true;
	}

	char server_ip[18];   //��������ַ
	int server_port = -1; //�˿ں�

	//WinSock��ʼ��
	WORD RequestVersion = MAKEWORD(2, 2);//ϣ��ʹ�õ�WinSock DLL�İ汾
	WSADATA Data;
	int startup = WSAStartup(RequestVersion, &Data);
	if (startup) {
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("WSAStartup() error"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		system("pause");
		exit(-1);
	}

	//ȷ��WinSock DLL֧�ְ汾2.2
	if (LOBYTE(Data.wVersion) != 2 || HIBYTE(Data.wVersion) != 2)
	{
		WSACleanup();
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Invalid Winsock version"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		system("pause");
		exit(-1);
	}

	//����socket()����ϵͳ����socket���
	c_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c_socket == INVALID_SOCKET) {
		WSACleanup();
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("socket() error!"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		system("pause");
		exit(-1);
	}

	//��ʾ�����������ַ & �˿�
	printf("[system] Please input srvers's ip: "); SetConsoleTextAttribute(hConsole, 0x3);
	scanf("%s", server_ip); SetConsoleTextAttribute(hConsole, 0x7);
	printf("[system] Please input port number: "); SetConsoleTextAttribute(hConsole, 0x3);
	scanf("%d", &server_port); SetConsoleTextAttribute(hConsole, 0x7);

	//������������ַ��Ϣ
	addr_server.sin_family = AF_INET;//��ַ����
	addr_server.sin_port = htons(server_port);//ע��ת��Ϊ�����ֽ���
	addr_server.sin_addr.S_un.S_addr = inet_addr(server_ip);

	//���ӷ�����
	if (connect(c_socket, (struct sockaddr*)&addr_server, sizeof(addr_server)) == SOCKET_ERROR) {
		//ʧ����ʾ
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Connection failed"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		return false;
	}
	else {
		//���ӳɹ�
		printf("[system] Successfully connect to the sever!\n");
		//�������ܷ������ظ����߳�
		hThread = CreateThread(NULL, 0, &RecvHandleThread, &c_socket, 0, NULL);

		//����һ����������� - �õ��Լ���id
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
			case 'e': //����������Ϣת���ķ���
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

//������Ϣ
void send_message() {
	if (connect_status) {
		int rec_id = -1;
		char info[1024], SendBuff[MaxBufSize] = "s";
		char recv_id[10];
		//��ȡ���շ�id
		cout << "[system] Please input receiver's id: "; SetConsoleTextAttribute(hConsole, 0x3);
		cin >> rec_id; getchar();  SetConsoleTextAttribute(hConsole, 0x7);
		_itoa(rec_id, recv_id, 10);
		strcat(recv_id, "&");

		//��ȡ��������Ϣ
		cout << "[system] Please input message to be sent: "; SetConsoleTextAttribute(hConsole, 0x3);
		gets_s(info); SetConsoleTextAttribute(hConsole, 0x7);

		//�����û�����
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
		//δ������ʾ
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("No server connected"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		return;
	}
}

//�����������ʱ��
void reqiure_time() {
	if (connect_status) {
		char SendBuff[2] = "t";
		int status = send(c_socket, SendBuff, sizeof(SendBuff), 0);
		if (status < 0) {
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Send failed"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			return;
		}
		else {
			//�ɹ����������
			return;
		}
		//Sleep(100);
		return;
	}
	else {
		//δ������ʾ
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("No server connected"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		return;
	}
	return;
}

//���������������
void reqiure_name() {
	if (connect_status) {
		char SendBuff[2] = "n";
		int status = send(c_socket, SendBuff, sizeof(SendBuff), 0);
		if (status < 0) {
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Send failed"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			return;
		}
		else {
			//�ɹ����������
			return;
		}
		//Sleep(100);
		return;
	}
	else {
		//δ������ʾ
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("No server connected"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		return;
	}
	return;
}

//�����û��б�
void require_list() {
	if (connect_status) {
		char SendBuff[2] = "l";
		int status = send(c_socket, SendBuff, sizeof(SendBuff), 0);
		if (status < 0) {
			printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("Send failed"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
			return;
		}
		else {
			//�ɹ����������
			return;
		}
		//Sleep(100);
		return;
	}
	else {
		//δ������ʾ
		printf("[system] "); SetConsoleTextAttribute(hConsole, 0xC); printf("No server connected"); SetConsoleTextAttribute(hConsole, 0x7); printf("!\n");
		return;
	}
	return;
}