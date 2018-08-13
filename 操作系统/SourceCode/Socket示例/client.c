/* File Name: client.c */  
  
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include <arpa/inet.h>
#include <unistd.h> 
#define MAXLINE 4096  
  
  
int main(int argc, char** argv)  
{  
    int    sockfd, n,rec_len;
    int     i_port = 8000; //默认8000端口
    
    char    recvline[4096], sendline[4096];  
    char    buf[MAXLINE];  
    char   *c_ipAddr = "127.0.0.1";
    
    struct sockaddr_in    servaddr;      
  
    if( argc == 1)
    {
        printf("This client will connect server message: IP=127.0.0.1 , Port=8000 \n");        
    }
    else if( argc ==2 )
    {
        c_ipAddr = argv[1];
        printf("This client will connect server message: IP=%s , Port=8000 \n",c_ipAddr);    
    }
    else if( argc == 3)
    {
        c_ipAddr = argv[1];    
        i_port = atoi(argv[2]);
        printf("This client will connect server message: IP=%s , Port=%d \n",c_ipAddr, i_port);    
    }
    else
    {  
        printf("usage: ./client <ipaddress> and port \n");  
        exit(0);  
    }  
  
      
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
    exit(0);  
    }  
  
  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(i_port);  
    
    if( inet_pton(AF_INET, c_ipAddr, &servaddr.sin_addr) <= 0){  
    printf("inet_pton error for %s\n",argv[1]);  
    exit(0);  
    }  
  
  
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }  
  
  
    printf("send msg to server: \n");  
    fgets(sendline, 4096, stdin);  
    if( send(sockfd, sendline, strlen(sendline), 0) < 0)  
    {  
    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);  
    exit(0);  
    }  
    if((rec_len = recv(sockfd, buf, MAXLINE,0)) == -1) {  
       perror("recv error");  
       exit(1);  
    }  
    buf[rec_len]  = '\0';  
    printf("Received : %s ",buf);  
    close(sockfd);  
    exit(0);  
}
