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
	
	
	servaddr.sin_port = htons((*port));
	servaddr.sin_family = AF_INET;
	
	struct in_addr ip_addr;
	ip_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_addr=ip_addr;
	
	if(((bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))) == -1)){
		printf("error");
		return 1;
	}
	
	
	listen(sockfd,5);
	
	
	
	struct sockaddr new;
	int len=sizeof(new);
	while(1){
		if((connfd=(accept(sockfd,&new,&len))) == -1)
		{
			printf("error");
			return 1 ;
		}
		printf("Connection accepted\n");
		
		int pid=fork();
		
		if(pid==0){ 
			close(sockfd);
			char buf[1024];
			
			int cont = recv(connfd,buf,1024,0);
			FILE* fp = popen(buf,"r");
			if(fp==NULL)printf("error");
			
			while(fgets(buf,1024,fp)!=NULL){
				fputs(buf,stdout);
				send(connfd,buf,1024,0);
				
			}	
		}else{
			close(connfd);
		}	
		
	}
	return 1;

}


