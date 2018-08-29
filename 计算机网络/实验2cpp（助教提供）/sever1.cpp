#include <stdio.h>//在windows中我们一般使用WinSock2头文件中的函数来进行网络通信
#include <winsock2.h>
#pragma comment ( lib, "ws2_32.lib" )


/*静态加入一个lib文件，也就是库文件。ws2_32.lib文件，提供了对以下网络相关API的支持，
用到winsock2.h中的API时要用到ws3_32.lib文件。*/
int main()
{
	printf("|=============================================|\n");
	printf("|                                             |\n");
	printf("|                                             |\n");
	printf("|                     服务器端                |\n");
	printf("|                                             |\n");
	printf("|                                             |\n");
	printf("|=============================================|\n");

	int len=1024;
	int flag=0;
	char Local_IP[20]={'0'};
	char recvBuf[1024]="\0";//接收缓冲区，大小1024
	char sendBuf[1024]="\0";//发送缓冲区，大小1024
	char TempBuf[1024]="\0";//发送缓冲区，大小1024
	char path[100]={'0'};

	printf("请输入本地IP:");
	gets(Local_IP);
	WORD wVersion = MAKEWORD(2, 0);
	WSADATA wsData;
	if (WSAStartup(wVersion, &wsData)!=0)
	{
		printf("初始化失败!\n");
	}

	SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);

	sockaddr_in addServer,addrClient;
	addServer.sin_family=AF_INET;
	addServer.sin_addr.S_un.S_addr=inet_addr(Local_IP);
	addServer.sin_port=htons(8000);

	if (bind(sockSrv,(SOCKADDR*)&addServer,sizeof(SOCKADDR))!=0)
	{
		printf("端口连接失败!\n");
	}
	else
	{
loop:
	listen(sockSrv,5);
	addrClient.sin_family=AF_INET;
	addrClient.sin_addr.S_un.S_addr=INADDR_ANY;
	addrClient.sin_port=htons(8000);
	printf("等待客户端连接……\n");
	SOCKET sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
	printf("连接成功!\n");
	while (1)
	{

		printf("发送：");
		fflush(stdin);
		gets(sendBuf);
		if (strcmp(sendBuf,"exit")==0)
		{
			send(sockConn,sendBuf,len,0);
			break;
		}
		else
		{
			send(sockConn,sendBuf,strlen(sendBuf)+1,0);
			recv(sockConn,recvBuf,1024,0);
			if (strcmp(recvBuf,"exit")==0)
			{
				printf("客户端已下线!\n");
				goto loop;
			}
		  	printf("接受：%s\n",recvBuf);
					fflush(stdin);
		}
	}
	closesocket(sockConn);
	}
	return 0;
}
