#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, char* argv[]) {
	int* port = (int*) argv[1];
	char* ip = (char*) argv[2];
  struct sockaddr_in serverAddr, clientAddr;
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0), check;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons((*port));
  serverAddr.sin_addr.s_addr = inet_addr(ip);
  
  check = bind(sockfd,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
  if(check == -1) {
    printf("Bind Error\n");
    return -1;
  }
  	
  for(;;) {
  	char buff[100];
		memset(&clientAddr, 0 , sizeof(clientAddr));
		int clilen = sizeof(clientAddr);
  	check = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientAddr, &clilen);
		check = sendto(sockfd, buff, check, 0, (struct sockaddr*)&clientAddr, clilen);
		printf("Recieved & Echoed : %s\n", buff);  
	}

  close(sockfd);
  return 0;
}
