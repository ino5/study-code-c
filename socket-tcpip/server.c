#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char* argv[])
{
    int serv_sock;
    int clint_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clint_addr;
    socklen_t clnt_addr_size;

    /* 포트번호 입력 안하면 종료 */
    if(argc != 2)  
    {
        printf("%s <port>\n", argv[0]);
        exit(1);
    }

    /* socket */
    serv_sock = socket(PF_INET, SOCK_STREAM,0);
    if(serv_sock == -1) printf("socket error\n");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    /* bind */
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) printf("bind error\n");

    printf("after bind: clint_addr.sin_addr: %u\n", clint_addr.sin_addr.s_addr);

    /* listen */
    if(listen(serv_sock, 5)==-1) printf("listen error\n");
    
    printf("after listen: clint_addr.sin_addr: %u\n", clint_addr.sin_addr.s_addr);

    /* accept */
    clnt_addr_size = sizeof(clint_addr);
    printf("before accept: clint_addr.sin_addr: %u\n", clint_addr.sin_addr.s_addr);
    clint_sock = accept(serv_sock, (struct sockaddr*) &clint_addr, &clnt_addr_size);
    printf("after accept: clint_addr.sin_addr: %u\n", clint_addr.sin_addr.s_addr);
    if(clint_sock == -1) printf("accept error\n");

    /* write */
    char message[] = "it is server message.";
    write(clint_sock, message, sizeof(message));
    close(serv_sock);
    close(clint_sock);
    return 0;
}