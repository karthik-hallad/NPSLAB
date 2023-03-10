#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
	printf("hello world");
	int* port = (int*) argv[1];
	
  
	struct sockaddr_in serverAddr, clientAddr;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0), check, cliLen;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons((*port));
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	check = bind(sockfd,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
  if(check == -1) {
    printf("Bind Error\n");
    return -1;
  }
  
  check = listen(sockfd, 5);
  if(check == -1) {
    printf("Listen Error\n");
    return -1;
  }

  for(;;) {
    cliLen = sizeof(clientAddr);
    int confd = accept(sockfd, (struct sockaddr*)&clientAddr, &cliLen);
		int pid = fork();
		if(pid==0) {
		  char buff[100],filename[100];
		  check = read(confd, filename, sizeof(filename));
		  int fd = open(filename,O_RDONLY);
			check = read(fd,buff,sizeof(buff));
			do {	
				write(confd, buff, check);
				check = read(fd,buff,sizeof(buff));		
			} while(check!=0);
			close(fd);
			close(confd);
		} else {
			close(confd);
		}
	}
  close(sockfd);
  return 0;
}
