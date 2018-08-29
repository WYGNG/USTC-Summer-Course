#include <stdio.h>
#include <winsock2.h>
#pragma comment ( lib, "ws2_32.lib" )

int main()
{
	printf("|=============================================|\n");
	printf("|                                             |\n");
	printf("|                  客户端                     |\n");
	printf("|                                             |\n");
	printf("|=============================================|\n");

	int len=1024;
	char Server_IP[20]={'0'};
	char recvBuf[1024]="\0";
	char sendBuf[1024]="\0";
	char path[100]={'0'};

	printf("请输入服务端IP:");
	gets(Server_IP);
	WORD wVersion = MAKEWORD(2, 0);
	WSADATA wsData;
	if (WSAStartup(wVersion, &wsData)!=0)
	{
		printf("初始化失败!\n");
	}

	SOCKET sockCli=socket(AF_INET,SOCK_STREAM,0);

	sockaddr_in addClient;
	addClient.sin_family=AF_INET;
	addClient.sin_addr.S_un.S_addr=inet_addr(Server_IP);
	addClient.sin_port=htons(8000);

	if(connect(sockCli,(SOCKADDR*)&addClient,sizeof(SOCKADDR))!=0)
		printf("连接服务器失败!\n");

	else
	{
		printf("连接成功!\n");
		while (1)
		{
			//fflush(stdin);
			recv(sockCli,recvBuf,len,0);
			if (strcmp(recvBuf,"exit")==0)
			{
				break;
			}
			else//接收保存文件
			{
		        printf("接受：%s\n",recvBuf);
				printf("发送：");
				gets(sendBuf);
				send(sockCli,sendBuf,strlen(sendBuf)+1,0);
				if (strcmp(sendBuf,"exit")==0)
				{
					break;
				}
			}
		}
		closesocket(sockCli);
	}
	return 0;
}
