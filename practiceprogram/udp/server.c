#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <fcntl.h>
#include <unistd.h>

int main(int argc,char **argv){
	int* port = (int*) argv[1];
	int sockfd,connfd;
	struct sockaddr_in cliaddr,servaddr;
	
	if((sockfd=(socket(AF_INET,SOCK_DGRAM,0))) == -1){
		printf("error");
		return;
	}
	
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons((*port));
	servaddr.sin_family = AF_INET;
	
	if(((bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))) == -1)){
		printf("error");
		return 1;
	}
	
	
	
	
	
	int size = 1024;
	char buf[size];
	int len=sizeof(servaddr);

	
	
	int pid=0;
	
	if(pid==0){ 
		recvfrom(sockfd,buf,size,0,(struct sockaddr *)&servaddr,&len);
		
		int fp=open(buf,O_RDONLY);
		printf("%d",fp);
		printf("File accepted\n");
		int temp=0;
		do{	
			//printf("reading");
			temp = read(fp,buf,size);
			printf("%d",temp);
			fputs(buf,stdout);
			sendto(sockfd,buf,temp,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
			
		}while(temp!=0);
		close(sockfd);
		exit(0);
	}else{
		close(connfd);
	}	
	
	
	return 1;

}


