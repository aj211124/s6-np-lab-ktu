#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#define MAX 100
void main()
{
  printf("Client side\n");
 char buffer[50];
 int sockfd;

//Creating a socket for communication
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 struct sockaddr_in addr1,addr2;

//Assigning family,ipaddress and port
 addr2.sin_family=AF_INET;
 addr2.sin_addr.s_addr=INADDR_ANY;
 addr2.sin_port=3008;

//connecting to the server
 connect(sockfd,(struct sockaddr *)&addr2,sizeof(addr2));

//Sending and receiving message from client and server
 do
 {
  printf("Sending message to server: ");
  scanf("%s",buffer);
  send(sockfd,buffer,sizeof(buffer),0);
  recv(sockfd,buffer,sizeof(buffer),0);
  printf("Received from server:%s\n",buffer);
  printf("\n");
  }
  while(strcmp(buffer,"stop")!=0);

//closing the open sockets
  close(sockfd);
}

