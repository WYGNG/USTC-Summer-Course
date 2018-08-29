#include <WinSock2.h>//在windows中我们一般使用WinSock2头文件中的函数来进行网络通信
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")
int main() {
    printf("这是服务器端程序！\n");
    WSADATA wsadata;//WSADATA数据类型用来存储被WSAStartup函数调用后返回的Windows Sockets数据。
    int port=8000;//设置服务器端口号
    char buff[1024];//发送缓冲区
    char recvBuf[1024];//接收缓冲区
    printf("服务器端口号设为8000\n");
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//创建用于监听的套接字
    SOCKADDR_IN addrSrv;//定义一个SOCKADDR_IN类型变量addsrv,表示服务器端的套接字描述符
    addrSrv.sin_family = AF_INET;//地址族赋值，AF_INET表示IPv4
    addrSrv.sin_port = htons(port); //端口号赋值，1024以上的端口号
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip地址赋值，INADDR_ANY表示填入本机ip地址
    bind(sockSrv, (LPSOCKADDR) & addrSrv, sizeof(SOCKADDR_IN));
    listen(sockSrv, 10);
    printf("服务器端准备完成，开始等待客户机连接请求：\n");
    while(1){
        SOCKADDR_IN addrClient;//定义一个SOCKADDR_IN类型变量Client,表示客户机端的套接字描述符
        int len = sizeof(SOCKADDR);//取得SOCKADDR_IN结构体的长度
        SOCKET sockConn = accept(sockSrv, (SOCKADDR * ) & addrClient, &len);//sockConn接收连接请求的套接字描述符
        printf("与客户机端连接成功，连接的客户机端IP为:%s\n", inet_ntoa(addrClient.sin_addr));//打印客户机ip地址
        while (1) {//等待客户请求到来
            printf("请输入要发送给客户机端的信息(字符串），不大于1024个字符,回车停止输入,当最后一个字符为#时关闭与客户端连接：\n");//开始发送数据
            gets(buff);
            fflush(stdin);
            int temp=strlen(buff);
            if(buff[temp-1]=='#')
                break;
            send(sockConn, buff, sizeof(buff), 0);
            printf("发送给客户机端的信息发送完成\n");
            memset(recvBuf, 0, sizeof(recvBuf));//初始化接收服务器端的缓冲区
            recv(sockConn, recvBuf, sizeof(recvBuf), 0);  //接收数据
            printf("接收到客户机端发来的信息：\n");//打印接收到的数据
            printf("%s\n",recvBuf);//打印接收到的数据
            printf("将接收到的信息由小写字母改成大写字母，并将改写后的信息发给客户机端\n");
            int length=strlen(recvBuf);
            memset(buff, 0, sizeof(buff));
            for(int i=0;i<length;i++){
                buff[i]=recvBuf[i];
                if(recvBuf[i]>=97&&recvBuf[i]<=122)
                    buff[i]-=32;
            }
            send(sockConn, buff, sizeof(buff), 0);
            printf("改写后的信息发送完成\n");
            memset(recvBuf, 0, sizeof(recvBuf));//初始化接收服务器端的缓冲区
            printf("接收到客户机端发来的改写后的信息：\n");//打印接收到的数据
            recv(sockConn, recvBuf, sizeof(recvBuf), 0);//接收数据
            printf("%s\n",recvBuf);//打印接收到的数据
        }
        printf("关闭套接字\n");//打印接收到的数据
        closesocket(sockConn);// closesocket函数用来关闭一个描述符为sockConn的套接字
        int flag;
        printf("是否还想运行服务器端程序？输入Y或N\n");
        scanf("%c",&flag);
        if(flag=='N')
            break;
    }
    closesocket(sockSrv);
    WSACleanup();//操作成功返回值为0；否则返回值为SOCKET_ERROR，可以通过调用WSAGetLastError获取错误代码。
    system("pause");//system("pause")就是从程序里调用“pause”命令.
    return 0;
}
