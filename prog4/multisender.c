#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

int main() {
  struct sockaddr_in listAddr, sendAddr;
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0), check, opt;
  sendAddr.sin_family = AF_INET;
  //any port u listen for new things
  
  sendAddr.sin_port = htons(0);
  sendAddr.sin_addr.s_addr = htonl(INADDR_ANY);
 
  check = bind(sockfd,(struct sockaddr*)&sendAddr, sizeof(sendAddr));
  if(check == -1) {
    printf("Bind Error\n");
    return -1;
  }

  listAddr.sin_family = AF_INET;
  listAddr.sin_port = htons(6664);
  listAddr.sin_addr.s_addr = inet_addr("224.0.0.69");

char buff[100] = "Hello";
check = sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&listAddr, sizeof(listAddr));
printf("Sent : %s\n", buff);  

  close(sockfd);
  return 0;
}
