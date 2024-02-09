#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include"libs/matfun.h"

#define BUFFER_SIZE 2048

void sendHTMLForm(int client_fd, double Ex, double Ey, double Fx, double Fy) {
    char *html_template = "<!DOCTYPE html>\n"
                          "<html lang=\"en\">\n"
                          "<head>\n"
                          "<meta charset=\"UTF-8\">\n"
                          "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                          "<title>TANGENTS</title>\n"
                          "<!--<style>body{text-align: center;}</style>-->"
                          "</head>\n"
                          "<body>\n"
                          "<h2>To find the tangents </h2>\n"
                          "<h3>Enter the coordinates of the triangle A, B, C</h3>\n"
                          "<form method=\"post\">\n"
                          "    <label for=\"x1\">Vertex A:(x1,y1)</label><br>"
                          "    <input type=\"text\" id=\"x1\" name=\"x1\" step=\"any\" required value=\"1\">"
                          "    <input type=\"text\" id=\"y1\" name=\"y1\" step=\"any\" required value=\"-1\"><br><br>"
                          "    <label for=\"x2\">Vertex B:(x2,y2)</label><br>"
                          "    <input type=\"text\" id=\"x2\" name=\"x2\" step=\"any\" required value=\"-4\">"
                          "    <input type=\"text\" id=\"y2\" name=\"y2\" step=\"any\" required value=\"6\"><br><br>"
                          "    <label for=\"x3\">Vertex C:(x3,y3)</label><br>"
                          "    <input type=\"text\" id=\"x3\" name=\"x3\" step=\"any\" required value=\"-3\">"
                          "    <input type=\"text\" id=\"y3\" name=\"y3\" step=\"any\" required value=\"-5\"><br><br>"
                          "    <button type=\"submit\">Calculate</button>\n"
                          "</form>\n"
                          "<h3>Result</h3>\n"
                          "<p>Result D: %lf, %lf</p>"
                          "<p>Result E: %lf, %lf</p>"
                          "</body>\n"
                          "</html>\n";

    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    snprintf(response + strlen(response), BUFFER_SIZE - strlen(response),
             html_template, Ex, Ey, Fx, Fy);

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
    address.sin_port = htons(5500);

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
    printf("Server is listening on port 5500\n");

    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("New connection accepted\n");

        char buffer[BUFFER_SIZE] = {0};
        read(client_fd, buffer, BUFFER_SIZE);
        printf("Received data from client: %s\n", buffer);

        char *body_start = strstr(buffer, "\r\n\r\n");

        if (body_start) {

            body_start += 4;

            double **A,**B,**C,**sol,**sides;
            int m=2,n=1, x1, y1, x2, y2, x3, y3;;
            sscanf(body_start, "x1=%d&y1=%d&x2=%d&y2=%d&x3=%d&y3=%d", &x1, &y1, &x2, &y2, &x3, &y3);
            A = createMat(m,n);
            B = createMat(m,n);
            C = createMat(m,n);
            sides = createMat(3,1);
            A[0][0] = x1;
            A[1][0] = y1;
            B[0][0] = x2;
            B[1][0] = y2;
            C[0][0] = x3;
            C[1][0] = y3;
            sides = tri_sides(A, B, C, sides);
            sol=calculate(A,B,C,sides);
            sendHTMLForm(client_fd, sol[0][0], sol[0][1], sol[1][0], sol[1][1]);
            printf("Results sent to client\n");
            freeMat(A,2);
            freeMat(B,2);
            freeMat(C,2);
            freeMat(sol,2);
            freeMat(sides,2);
        }

        close(client_fd);
    }

    return 0;
}
