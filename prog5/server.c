#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
void str_echo(int connfd1,int connfd2)
{	
	int n=1024;
	char *buf=malloc(n);
	int cont=0;
	
	while(1)
	{
		//scanf("%s",buf);
		//buff to store
		//if recv in connfd1 then send to connfd3
		if((cont=recv(connfd1,buf,n,0))>0)
		{	send(connfd2,buf,cont,0);
			cont=recv(connfd2,buf,n,0);
			send(connfd1,buf,cont,0);
		}
		//if recv connfd2 then send to connfd1
		else if(cont=recv(connfd2,buf,n,0)>0)
		{
			send(connfd1,buf,cont,0);
			cont=recv(connfd1,buf,n,0);
			send(connfd2,buf,cont,0);
		}
		
	}
}
int main()
{
	int sockfd,connfd1,connfd2,n,pid;
	
	struct sockaddr_in servaddr,cliaddr;
	if(sockfd=socket(AF_INET,SOCK_STREAM,0))
		printf("\n Socket created");
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(15001);
	servaddr.sin_addr.s_addr=INADDR_ANY;
	
	
	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(sockfd,30);

	n=sizeof(servaddr);
		
	while(1)
	{
	
		connfd1=accept(sockfd,(struct sockaddr *)&cliaddr,&n);
		connfd2=accept(sockfd,(struct sockaddr *)&cliaddr,&n);
		
		if((pid=fork())==0)
		{
			close(sockfd);
			str_echo(connfd1,connfd2);
			exit(0);
		}
	}
	close(connfd1);
	close(connfd2);
	return 0;
}
