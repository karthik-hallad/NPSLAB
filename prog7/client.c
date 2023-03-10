#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void execute_cmd(int sockfd){
	int n;
    char buf[5000];
    while(1){
        scanf("%[^\n]s", buf);
        
        n = write(sockfd, buf, sizeof(buf));
        do {
        	n = read(sockfd, buf, sizeof(buf));
        	printf("%s",buf);
        } while(n!=0);
    }
}

int main(int argc, char const *argv[]){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    
    addr.sin_family = AF_INET;
    
    //in_addr ki specifiality it possess
    struct in_addr ip_addr;
    ip_addr.s_addr = inet_addr(argv[1]);
    
    //ip_addr.s_addr = htonl(0x7f000001);
    addr.sin_addr = ip_addr;
    addr.sin_port = htons(16001);
    connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
    execute_cmd(sockfd);
    close(sockfd);
}
