#include <stdio.h>

int main(void) {

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            printf("\x1b[38;5;%dm %03d \x1b[0m", i * 16 + j, i * 16 + j);
        }
        printf("\n");
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            printf("\x1b[48;5;%dm %03d \x1b[0m", i * 16 + j, i * 16 + j) 
        }
        printf("\n");
    }
}
