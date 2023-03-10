#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

void execute_cmd(int clientsockfd){
    char buf[100];
    read(clientsockfd, buf, sizeof(buf));
    FILE *fp;
    char path[5000];
    //command open
    //not O_RDONLY use r
    fp = popen(buf, "r");
    
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
//    fgets(buffer,bufsize,source) - necessary to get from a file pointer
    while (fgets(path, sizeof(path), fp)!=NULL) {
        write(clientsockfd, path, sizeof(path));
        memset(path,0,sizeof(path));
    }
    pclose(fp);
}

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    
    //in_addr ip_addr
    struct in_addr ip_addr;
    ip_addr.s_addr = inet_addr("127.0.0.1");
    
    addr.sin_addr = ip_addr;
    addr.sin_port = htons(16001);
    
    bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, 10);
    
    
    //have to pass sockaddr to the accept command
    struct sockaddr clientaddr;
    int clientsocklen;
    
    while(1){
        int clientsockfd = accept(sockfd, &clientaddr, &clientsocklen);
        
        printf("Accepted a client\n");
        pid_t pid = fork();
        
        if(pid==0){
            //closing server sockfd and communicationg through only clientsockfd
            close(sockfd);
            execute_cmd(clientsockfd);
            close(clientsockfd);
            break;
        }
        else
            close(clientsockfd);
    }
}
