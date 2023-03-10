#include<string.h>
#include<netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc,char* argv[]) {
	int* port = (int*) argv[1];
	int sockfd,ret,confd,check,clilen;
	struct sockaddr_in sockaddr,clientaddr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	sockaddr.sin_family=AF_INET;
	sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	sockaddr.sin_port=htons((*port));
	if(sockfd==-1) {
		printf("Error opening server");
		return 0;
	}
	check=connect(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
	if(check==-1) {
		printf("Error opening server");
		return 0;
	}
	printf("Enter file to read : ");
	char buff[30];
	scanf("%s",&buff);
	char buff_rec[200];

	check=write(sockfd,buff,sizeof(buff));
	
	
	check=read(sockfd,buff_rec,sizeof(buff));
	do{
		//for(int i=0;i<check;i++)
			printf("%s",buff_rec);
		check=read(sockfd,buff_rec,sizeof(buff));
	} while(check!=0);

	close(sockfd);
}
