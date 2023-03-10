#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, char* argv[]) {
	int* port = (int*) argv[1];
	
	  struct sockaddr_in serverAddr;
	  int sockfd = socket(AF_INET, SOCK_DGRAM, 0), check;
	  serverAddr.sin_family = AF_INET;
	  serverAddr.sin_port = htons((*port));
	  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  	
	char buff[100];
	printf("Enter message to send : ");
	scanf("%s",buff);

	printf("Sending : %s\n", buff);  
	check = sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	//writing everything to 0
	memset(&serverAddr, 0 , sizeof(serverAddr));
	
	int slen = sizeof(serverAddr);	
	check = recvfrom(sockfd, buff, check, 0, (struct sockaddr*)&serverAddr, &slen);
	
	printf("Recieved : %s\n", buff);  
	  close(sockfd);
	  return 0;
}

//172.16.18.103
