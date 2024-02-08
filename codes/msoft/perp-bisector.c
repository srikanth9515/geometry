#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <math.h>

#include "libs/matfun.h"

#define BUFFER_SIZE 2048

// HTML template
char *html_template = "<!DOCTYPE html>\n"
                      "<html lang=\"en\">\n"
                      "<head>\n"
                      "<meta charset=\"UTF-8\">\n"
                      "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                      "<title>Bisector</title>\n"
                      "</head>\n"
                      "<body>\n"
                      "<style>"
                      "html {font-family: Times New Roman; display: inline-block; text-align: center;}"
                      "h2 {font-size: 2.0rem; color: blue;}"
                      "</style>"
                      "<h2>Perpendicular Bisectors</h2>\n"
                      "<form method=\"post\">\n"
			    "    <label for=\"x1\">Vertex A (x1 y1):</label><br>\n"
                            "    <input type=\"text\" id=\"x1\" name=\"x1\" value=\"%.2f\"  required>\n"
                            "    <input type=\"text\" id=\"y1\" name=\"y1\" value=\"%.2f\" required><br><br>\n"
			    "    <label for=\"x1\">Vertex B (x2 y2):</label><br>\n"
                            "    <input type=\"text\" id=\"x2\" name=\"x2\" value=\"%.2f\" required>\n"
                            "    <input type=\"text\" id=\"y2\" name=\"y2\" value=\"%.2f\" required><br><br>\n"
			    "    <label for=\"x1\">Vertex C (x3 y3):</label><br>\n"
                            "    <input type=\"text\" id=\"x3\" name=\"x3\" value=\"%.2f\" required>\n"
                            "    <input type=\"text\" id=\"y3\" name=\"y3\" value=\"%.2f\" required><br><br>\n"
                      "    <button type=\"submit\">Calculate</button>\n"
                      "</form>\n"
                      "<h3>Results</h3>\n"
                      "<p>Bisector AB: Slope=%.2f, Midpoint=(%.2f, %.2f)</p>\n"
                      "<p>Bisector BC: Slope=%.2f, Midpoint=(%.2f, %.2f)</p>\n"
                      "<p>Bisector CA: Slope=%.2f, Midpoint=(%.2f, %.2f)</p>\n"
                      "</body>\n"
                      "</html>\n";

// Function to send HTML form with results
void sendHTMLForm(int client_fd, double x1, double y1, double x2, double y2, double x3, double y3) {
    char response[BUFFER_SIZE];
    double bisectorABSlope, bisectorABMidpointX, bisectorABMidpointY;
    double bisectorBCSlope, bisectorBCMidpointX, bisectorBCMidpointY;
    double bisectorCASlope, bisectorCAMidpointX, bisectorCAMidpointY;

    calculatePerpendicularBisector(x1, y1, x2, y2, &bisectorABSlope, &bisectorABMidpointX, &bisectorABMidpointY);
    calculatePerpendicularBisector(x2, y2, x3, y3, &bisectorBCSlope, &bisectorBCMidpointX, &bisectorBCMidpointY);
    calculatePerpendicularBisector(x3, y3, x1, y1, &bisectorCASlope, &bisectorCAMidpointX, &bisectorCAMidpointY);

    sprintf(response, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    snprintf(response + strlen(response), BUFFER_SIZE - strlen(response), html_template,
    	     x1,y1,x2,y2,x3,y3,
             bisectorABSlope, bisectorABMidpointX, bisectorABMidpointY,
             bisectorBCSlope, bisectorBCMidpointX, bisectorBCMidpointY,
             bisectorCASlope, bisectorCAMidpointX, bisectorCAMidpointY);

    send(client_fd, response, strlen(response), 0);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8787);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 8787\n");

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

            double x1, y1, x2, y2, x3, y3;
            sscanf(body_start, "x1=%lf&y1=%lf&x2=%lf&y2=%lf&x3=%lf&y3=%lf", &x1, &y1, &x2, &y2, &x3, &y3);

            sendHTMLForm(client_fd, x1, y1, x2, y2, x3, y3);
            printf("Results sent to the client\n");
        }

        close(client_fd);
    }

    return 0;
}

