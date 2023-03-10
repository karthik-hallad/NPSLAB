#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

int main() {
  struct sockaddr_in listAddr;
struct ip_mreq mreq;
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0), check, opt = 1;
  listAddr.sin_family = AF_INET;
  listAddr.sin_port = htons(6664);
  listAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
   opt = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,&opt,sizeof(opt));
  check = bind(sockfd,(struct sockaddr*)&listAddr, sizeof(listAddr));

  if(check == -1) {
    printf("Bind Error\n");
    return -1;
  }

mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.69");
mreq.imr_interface.s_addr = htonl(INADDR_ANY);
check = setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));

  for(;;) {
  	char buff[100];
	int clilen = sizeof(listAddr);
  	check = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&listAddr, &clilen);	
	printf("Recieved : %s\n", buff);  
}

  close(sockfd);
  return 0;
}
