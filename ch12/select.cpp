#include <cstdio>
#include <iostream>

#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#include <fmt/format.h>

constexpr int BUF_SIZE = 30;

int main(int argc, char* argv[]) {
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;
    FD_ZERO(&reads);
    FD_SET(0, &reads);

    /*
    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;
    */

    while (1) {
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        result = select(1, &temps, 0, 0, &timeout);
        if (result == -1) {
            fmt::println("select() error");
            break;
        } else if (result == 0) {
            fmt::println("Time-out!");
        } else {
            if (FD_ISSET(0, &temps)) {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                fmt::println("message from console: {}", buf);
            }
        }
    }
}