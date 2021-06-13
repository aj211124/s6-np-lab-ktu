#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#define MAX 100

void server()
{
  printf("Server side:\n");
  char msg[MAX];
  int sockfd,socket;
  struct sockaddr_in addr1, addr2;
  addr1.sin_family=AF_INET;
  addr1.sin_addr.s_addr=INADDR_ANY;
  addr1.sin_port=3008;
  int size=sizeof(struct sockaddr_in); 
  bind(sockfd,(struct sockaddr *)&addr1,sizeof(addr1));
  listen(sockfd,5);
  socket=accept(sockfd,(struct sockaddr *)&addr2,(&size));
  do
 {
  printf("Connection Established\n");
  printf("Receiving message from client: ");
  recv(socket,msg,sizeof(msg),0);
  printf("%s",msg);
  printf("\nEnter the message:");
  scanf("%s",msg);
  send(socket,msg,sizeof(msg),0);
  printf("\n");
  }
  while(strcmp(msg,"stop")!=0);
  close(socket);
  close(sockfd);
}
