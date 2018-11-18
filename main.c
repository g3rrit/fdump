#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define LINE_LENGTH 16

#define print_hex(c) \
    fprintf(out, "%.2hhx", c)

#define print_char(c) \
    {                               \
        if(c >= 32 && c <= 126) {   \
            fprintf(out, "%c", c);  \
        } else {                    \
            fprintf(out, ".");      \
        }                           \
    }

int main(int argc, char **argv) {

    // command line options
    int out_f = 0;
    char *out_n = 0;
    char *in_n = 0;

    int a;
    while((a = getopt(argc, argv, "o:")) != -1) {
        switch(a) {
            case 'o':
                out_n = optarg;
                out_f = 1;
            case '?':
                if(optopt == 'o') {
                    fprintf(stderr, "option -%c requires an argument\n", optopt);
                    return -1;
                }
        }
    }

    FILE *out = 0;
    if(out_f) {
        out = fopen(out_n, "wb");
        if(!out) {
            fprintf(stderr, "unable to open output file %s\n", out_n);
            return -1;
        }
    } else {
        out = stdout;
    }

    if(optind >= argc) {
        fprintf(stderr, "no input file specified\n");
        return -1;
    }

    FILE *file = fopen(argv[optind], "rb");
    if(!file) {
        printf("unable to open file [%s]\n", argv[1]);
        return 0;
    }

    uint32_t pos = 0;

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
            fprintf(out, "| [%08x] ", pos);
            for(int i = 0; i < LINE_LENGTH; i++) {
                print_hex(line[i]);
            }
            fprintf(out, " - ");
            for(int i = 0; i < LINE_LENGTH; i++) {
                print_char(line[i]);
            } 
            fprintf(out, " |\n");
            count = 0;
            pos += LINE_LENGTH;
        }
        count++;
        if(count>=LINE_LENGTH) {
            count = 0;
        }
    }

    fclose(file);

    return 0;
}
