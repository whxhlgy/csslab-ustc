#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>


void sendFile(int client_sock, FILE *file);

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUF_SIZE 1024

void serve_client(int client_sock, const char* web_root){
    char request[BUF_SIZE];
    ssize_t bytes_received = read(client_sock, request, sizeof(request) - 1);
    if(bytes_received < 0){
        perror("read");
        return;
    }
    request[bytes_received] = '\0';

    // Parse the HTTP request, extract the requested file path, and handle the request.
    printf("Received request:\n%s\n", request);

    char method[16], path[128];
    int scanResult = sscanf(request, "%s %s", method, path);
    if(scanResult != 2){
        char response[] = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
        write(client_sock, response, strlen(response));
        close(client_sock);
        return;  
    }

    char fullpath[256];
    // hard code the file path
    strcpy(fullpath, "/home/amazjj/mywebsite/index.html");
    snprintf(fullpath, sizeof(fullpath), "%s%s", web_root, path);  

    // Handle GET requests for serving files.
    if(strcasecmp(method, "GET") == 0){

        // Exercise 5.
        // Add your code here:
        FILE *file = fopen(fullpath, "rb");
        if (file == NULL) {
            char response[] = "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";
            send(client_sock, response, strlen(response), 0);
        } else {
            sendFile(client_sock, file);
        }
    }
    // Handle DELETE requests for deleting files.
    
    else if(strcasecmp(method, "DELETE") == 0){
        // Exercise 6: Implement DELETE here
        // Add your code here:
        if (remove(fullpath) != 0) {
            char response[] = "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";
            send(client_sock, response, strlen(response), 0);
        } else {
            char response[] = "HTTP/1.1 200 OK\r\n"
                              "Date: Wed, 21 Oct 2015 07:28:00 GMT\r\n"
                              "\r\n"
                              "<html>\n"
                              "  <body>\n"
                              "    <h1>File deleted.</h1>\n"
                              "  </body>\n"
                              "</html>";
            send(client_sock, response, strlen(response), 0);
        }

    }else{
        char response[] = "HTTP/1.1 405 Method Not Allowed\r\nContent-Length: 0\r\n\r\n";
        write(client_sock, response, strlen(response));
    }

    close(client_sock);
}

int main(){
    char web_root[256];
    strcpy(web_root, getenv("HOME"));
    strcat(web_root, "/mywebsite");

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int reuseaddr = 1;
    if(setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(int)) == -1){
        perror("Setsockopt error");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if(listen(server_sock, 5) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", SERVER_PORT);

    while(1){
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sock < 0) {
            perror("accept");
            continue;
        }

        
        serve_client(client_sock, web_root);

        // Challenge: multiple process
        // Add your code here:
//        TODO();

    }

    close(server_sock);
    return 0;
}

// send a file and a respond header to socket
void sendFile(int client_sock, FILE *file) {
    char response[1024] = {0};
    // get the size of file
    fseek(file, 0 , SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0 , SEEK_SET);
    // send the respond
    snprintf(response, 1024, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: text/html\r\n\r\n", fileSize);
    send(client_sock, response, strlen(response), 0);
    // creat a buffer
    char buffer[BUF_SIZE];
    unsigned long cnt = 0;
    unsigned long readBytes;
    while (cnt < fileSize) {
        readBytes = fread(buffer, 1, BUF_SIZE, file);
        send(client_sock, buffer, strlen(buffer), 0);
        cnt += readBytes;
    }
}
