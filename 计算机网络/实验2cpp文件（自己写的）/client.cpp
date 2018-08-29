#include <WinSock2.h>//在windows中我们一般使用WinSock2头文件中的函数来进行网络通信
#include <stdio.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")
int main() {
    printf("这是客户机端程序！\n");
    WSADATA wsaData;//WSADATA数据类型用来存储被WSAStartup函数调用后返回的Windows Sockets数据。
    char buff[1024];//发送缓冲区
    char recvBuf[1024];//接收缓冲区
    memset(buff, 0, sizeof(buff));//初始化缓冲区值为0
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKADDR_IN addrSrv;//定义一个SOCKADDR_IN类型变量addsrv,表示服务器端的套接字描述符
    addrSrv.sin_family = AF_INET;//地址族赋值，AF_INET表示IPv4
    addrSrv.sin_port = htons(8000);//端口号赋值，1024以上的端口号
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//ip地址赋值，INADDR_ANY表示填入本机ip地址
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);//创建客户机端套接字
    connect(sockClient, (struct sockaddr *) &addrSrv, sizeof(addrSrv));
    printf("客户机端已连接服务器！\n");
    while(1){
        memset(recvBuf, 0, sizeof(recvBuf));
        printf("接收服务器端发来的信息：\n");
        recv(sockClient, recvBuf, sizeof(recvBuf), 0);//接收数据
        printf("%s\n", recvBuf);//打印接收的数据
        printf("请输入要发送给服务器端的信息(字符串），不大于1024个字符，回车停止输入,当最后一个字符为#时关闭客户机：\n");//发送数据
        gets(buff);
        fflush(stdin);
        int temp=strlen(buff);
        if(buff[temp-1]=='#')
            break;
        send(sockClient, buff, sizeof(buff), 0);
        printf("发送给服务器端的信息发送完成\n");
        printf("将接收到的信息由小写字母改成大写字母，并将改写后的信息发给服务器端\n");
        int length=strlen(recvBuf);
        memset(buff, 0, sizeof(buff));
        for(int i=0;i<length;i++){
            buff[i]=recvBuf[i];
            if(recvBuf[i]>=97&&recvBuf[i]<=122)
                buff[i]-=32;
        }
        send(sockClient, buff, sizeof(buff), 0);
        printf("改写后的信息发送完成\n");
        memset(recvBuf, 0, sizeof(recvBuf));
        printf("接收到服务器端发来的改写后的信息：\n");
        recv(sockClient, recvBuf, sizeof(recvBuf), 0);
        printf("%s\n", recvBuf);//打印接收的数据
    }
    printf("关闭套接字\n");
    closesocket(sockClient);//关闭客户机套接字
    WSACleanup();//操作成功返回值为0；否则返回值为SOCKET_ERROR，可以通过调用WSAGetLastError获取错误代码。
    system("pause");//system("pause")就是从程序里调用“pause”命令.
    return 0;
}
