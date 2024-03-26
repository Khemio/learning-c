// #include <minwindef.h>
// #include <psdk_inc/_ip_types.h>
// #include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>

int main(void) {
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = 0;
    addr.sin_port = htons(8080);

    bind(s, &addr, sizeof(addr));

    listen(s, 10);

    while (1) {
        SOCKET client = accept(s, 0, 0);

        char request[256] = {0};
        recv(client, request, 256, 0);

        // GET / ...
        if (memcmp(request, "GET / ", 6) == 0) {
            char buffer[1024] = {0};
            char *temp_ptr = buffer;

            int num_chars =  sprintf(temp_ptr, "HTTP/1.0 200 OK\r\n");
            temp_ptr += num_chars;

            num_chars = sprintf(temp_ptr, "Content-Type: text/html\r\n");
            temp_ptr += num_chars;

            FILE* f = fopen("index.html", "r");
            char html_body[512];
            // char html_body[] = "<html><head></head><body>Hello World!</body></html>\r\n";

            fread(html_body, 1, 512, f);

            num_chars = sprintf(temp_ptr, "%s", html_body);
            temp_ptr += num_chars;

            int total_message_length = temp_ptr - buffer;

            // printf("%s", buffer);
            send(client, buffer, total_message_length, 0);

            fclose(f);
            // closesocket(client);
        }

        // GET /about ...
        if (memcmp(request, "GET /about ", 10) == 0) {
            char buffer[1024] = {0};
            char *temp_ptr = buffer;

            int num_chars =  sprintf(temp_ptr, "HTTP/1.0 200 OK\r\n");
            temp_ptr += num_chars;

            num_chars = sprintf(temp_ptr, "Content-Type: text/html\r\n\r\n");
            temp_ptr += num_chars;

            FILE* f = fopen("about.html", "r");
            char html_body[512];
            // char html_body[] = "<html><head></head><body>Hello World!</body></html>\r\n";

            fread(html_body, 1, 512, f);

            printf("%s", html_body);

            num_chars = sprintf(temp_ptr, "%s", html_body);
            temp_ptr += num_chars;

            int total_message_length = temp_ptr - buffer;

            // printf("%s", buffer);
            send(client, buffer, total_message_length, 0);

            fclose(f);
            // closesocket(client);
        }

    }

    return 0;
}