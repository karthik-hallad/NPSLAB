#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
void str_echo(int sockfd)
{
	int n=1024,cont;
	char *buf=malloc(n);
	//fputs((buf)inp,out)
	//fgets(buf,sizeofb(maxsize),stdin)
	
	//do this while ctrl d
	while(fgets(buf,n,stdin)!=NULL)
	{
		//printf("\nEnter the string:\n");
		//scanf("%s",buf);
		send(sockfd,buf,n,0);
	
	//	printf("%s",buf);
		if((n=recv(sockfd,buf,n,0))>0)
			fputs(buf,stdout);
	}
	printf("\nEOF\n");
}
int main(int argc,char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;
	
	
	//passing the ip address
	printf("%s\n",argv[1]);
	if(sockfd=socket(AF_INET,SOCK_STREAM,0))
		printf("\nSocket created\n");
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(15001);
	
	//same things to work with but do use inet_pton
	//servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	//address passed is saved into servaaddr
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	
	//connect
	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	//stdin- where we type and sockfd-socket des to connect from
	str_echo(sockfd);
	close(sockfd);
}
