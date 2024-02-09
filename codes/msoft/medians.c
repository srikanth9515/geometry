#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "libs/matfun.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8788
#define BUFFER_SIZE 2048

void sendHTMLForm(int client_fd, double side_a,double side_b,double side_c,double median1,double median2,double median3) {
    char *html_template = "<!DOCTYPE html>\n"
                          "<html lang=\"en\">\n"
                          "<head>\n"
                          "<meta charset=\"UTF-8\">\n"
                          "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                          "<title> SOFTWARE SOLUTION FOR MEDIAN</title>\n"
                          "</head>\n"
                          "<body>\n"
"<style>"
    "html {font-family: Times New Roman; display: inline-block; text-align: center;}"
    "h2 {font-size: 2.0rem; color: blue;}"
  "</style>"
                          "<h2>MEDIAN OF A TRIANGLE </h2>\n"
                          "<form method=\"post\">\n"
                          "    <label for=\"side_a\">Side A:</label><br>\n"
                          "    <input type=\"text\" id=\"side_a\" name=\"side_a\" value=\"%lf\" step=\"any\" required><br><br>"
			  "    <label for=\"side_b\">Side B:</label><br>\n"
                          "    <input type=\"text\" id=\"side_b\" name=\"side_b\" value=\"%lf\" step=\"any\" required><br><br>"   
                          "    <label for=\"side_c\">Side C:</label><br>\n"
                          "    <input type=\"text\" id=\"side_c\" name=\"side_c\" value=\"%lf\" step=\"any\" required><br><br>"  
                        
                          "    <button type=\"submit\">Calculate</button>\n"
                          "</form>\n"
                          "<h3>Result</h3>\n"
                          "<p>Result Median1 of Triangle: %.2lf</p>\n"
                          "<p>Result Median2 of Triangle: %.2lf</p>\n"
                          "<p>Result Median3 of Triangle: %.2lf</p>\n"                                             
                          "</body>\n"
                          "</html>\n";

    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    snprintf(response + strlen(response), BUFFER_SIZE - strlen(response), html_template, side_a,side_b,side_c,median1,median2,median3);

    send(client_fd, response, strlen(response), 0);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Print server address
    printf("Server is listening on port 878\n");

    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("New connection accepted\n");
        
        char buffer[BUFFER_SIZE] ={0};
        read(client_fd, buffer, BUFFER_SIZE);
        printf("Received data from client: %s\n", buffer);
        
        char *body_start = strstr(buffer,"\r\n\r\n");
        
        if(body_start){
        
            body_start +=4;
        
            double side_a,side_b,side_c;
            sscanf(body_start,"side_a=%lf&side_b=%lf&side_c=%lf", &side_a,&side_b,&side_c);
            
            double median1 =calculateMedian(&side_a, &side_b, &side_c);
	    double median2 =calculateMedian(&side_b, &side_c, &side_a);
            double median3 =calculateMedian(&side_c, &side_a, &side_b);
            
            sendHTMLForm(client_fd, side_a,side_b,side_c,median1,median2,median3);
            printf("Results sent to client\n");
        }
        
        close(client_fd);
    }

    return 0;
}

