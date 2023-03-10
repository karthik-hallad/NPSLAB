#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {

     
   int* port = (int*) argv[1];
   printf("%d",*port);
   fflush(stdout);
	//accept - &clilen .. clilen
	//sockfd,(struct sockaddr *)&addr,sizeof(addr)
	//listen(sockfd,4)
	//addr.sin_family/port/addr.s_addr
	
  struct sockaddr_in serverAddr, clientAddr;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0), check, cliLen;
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons((*port));
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  check = bind(sockfd,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
  if(check == -1) {
    printf("Bind Error\n");
    fflush(stdout);
    return -1;
  }
  printf("bind successfull\n");
  check = listen(sockfd, 5);
  if(check == -1) {
    printf("Listen Error\n");
    return -1;
  }
  printf("listen successfull\n");
  
  //read(connfd,sourcem,maxsize)
  //write(connfd,source,towritesize)
  //write(
  for(;;) {
    cliLen = sizeof(clientAddr);
    int confd = accept(sockfd, (struct sockaddr*)&clientAddr, &cliLen);
    char buff[100],filename[100];
    //check - no of char
    check = read(confd, filename, sizeof(filename));
    int fd = open(filename,O_RDONLY);
	check = read(fd,buff,sizeof(buff));
	do {	
		write(confd, buff, check);
		check = read(fd,buff,sizeof(buff));		
	} while(check!=0);
	close(fd);
	  close(confd);
	}
  close(sockfd);
  return 0;
}
