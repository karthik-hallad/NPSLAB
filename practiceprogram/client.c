#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <fcntl.h>
#include <unistd.h>

int main(int argc,char**argv){
	int *port = (int*)argv[1];
	int sockfd,connfd;
	struct sockaddr_in cliaddr,servaddr;
	
	if((sockfd=(socket(AF_INET,SOCK_STREAM,0))) == -1){
		printf("error");
		return;
	}
	
	cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	cliaddr.sin_port = htons(*port);
	cliaddr.sin_family = AF_INET;
	
	
	if(((connect(sockfd,(struct sockaddr *)&cliaddr,sizeof(cliaddr))) == -1)){
		printf("error");
		return;
	}
	
	int size = 1024;
	char buf[size];
	int len;
	
	fgets(buf,size,stdin);
	
	send(sockfd,buf,sizeof(buf),0);
	
	do{
		len = recv(sockfd,buf,1024,0);
		fputs(buf,stdout);
	}while(len!=0);
	
	close(sockfd);
	
	return 1;

}


