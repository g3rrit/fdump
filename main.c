#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 16

#define print_hex(c) \
    printf("%.2hhx", c)

#define print_char(c) \
    {                               \
        if(c >= 32 && c <= 126) {   \
            printf("%c", c);        \
        } else {                    \
            printf(".");            \
        }                           \
    }

int main(int argc, char **argv) {

    if(argc < 2) {
        fprintf(stderr, "usage: prog <file>\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "rb");
    if(!file) {
        printf("unable to open file [%s]\n", argv[1]);
        return 0;
    }


    int c = 0;
    int count = 0;
    char line[LINE_LENGTH] = { 0 };
    for(;;) {
        c = fgetc(file);
        if(feof(file)) {
            break;
        }
        line[count] = (char)c;

        if(count == LINE_LENGTH - 1) {
            for(int i = 0; i < LINE_LENGTH; i++) {
                print_hex(line[i]);
            }
            printf(" - ");
            for(int i = 0; i < LINE_LENGTH; i++) {
                print_char(line[i]);
            } 
            printf("\n");
            count = 0;
        }
        count++;
        if(count>=LINE_LENGTH) {
            count = 0;
        }
    }

    fclose(file);

    return 0;
}
