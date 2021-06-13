#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

void main()
{
 printf("Client side\n");
 char buffer[50];
 int sockfd;
 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 struct sockaddr_in addr;
 addr.sin_family=AF_INET;
 addr.sin_addr.s_addr=INADDR_ANY;
 addr.sin_port=3008;
 int s=sizeof(struct sockaddr_in);
 connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
 do
 {
  printf("Sending message to server: ");
  scanf("%s",buffer);
  sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,s);
  recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,&s);
  printf("Received from server:%s\n",buffer);
  }while(strcmp(buffer,"bye")!=0);
  close(sockfd);
}
