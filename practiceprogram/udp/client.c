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
	
	if((sockfd=(socket(AF_INET,SOCK_DGRAM,0))) == -1){
		printf("error");
		return;
	}
	
	cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	cliaddr.sin_port = htons(*port);
	cliaddr.sin_family = AF_INET;
	
	
	
	int size = 1024;
	char buf[size];
	int len=sizeof(cliaddr	);
	
	printf("Enter the file to read");
	scanf("%[^\n]s",buf);
	
	sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
	
	
		len=recvfrom(sockfd,buf,size,0,(struct sockaddr *)&cliaddr,&len);
		fputs(buf,stdout);
		
	
	close(sockfd);
	
	return 1;

}


