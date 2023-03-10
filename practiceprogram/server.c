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
	
	if((sockfd=(socket(AF_INET,SOCK_STREAM,0))) == -1){
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
	
	
	listen(sockfd,5);
	
	
	int size = 1024;
	char buf[size];
	int len=sizeof(servaddr);
	while(1){
		if((connfd=(accept(sockfd,(struct sockaddr *)&servaddr,&len))) == -1)
		{
			printf("error");
			return 1 ;
		}
		printf("Connection accepted\n");
		
		int pid=0;
		
		if(pid==0){ 
			recv(connfd,buf,size,0);
			
			FILE* fp=popen(buf,"r");
			printf("%d",fp);
			printf("File accepted\n");
			char* temp=0;
			do{	
				printf("reading");
				temp = fgets(buf,size,fp);
				printf("%d",temp);
				fputs(buf,stdout);
				send(connfd,buf,sizeof(buf),0);
				
			}while(temp!=NULL);
			close(sockfd);
			exit(0);
		}else{
			close(connfd);
		}	
		
	}
	return 1;

}


