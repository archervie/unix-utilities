#define _GNU_SOURCE
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(FILE *fp, char *term);

int main(int argc, char *argv[]) {

    int c;
    int option_index = 0;
    int status = 1;

    while (1) {
        static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                               {0, 0, 0, 0}};

        c = getopt_long(argc, argv, "h", long_options, &option_index);
        if (c == -1)
            break;

        if (c == 'h') {
            printf("Usage: avgrep [OPTION] TERM [FILE]... \n");
            printf("Print each line of FILE(s) where TERM is present.");
            printf("Options:\n");
            printf("    -h, --help    Displays help and exits.\n");
            return 0;
        }
    }

    if (argc < 2) {
        fprintf(stderr, "wgrep: [OPTION] TERM [FILE]...\n");
        return 1;
    }

    char *term = argv[1];

    if (argc == 2) {
        read_file(stdin, term);
        status = 0;
    }

    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) {
            fprintf(stderr, "avsed: %s: ", argv[i]);
            perror("");
            continue;
        }

        read_file(fp, term);
        status = 0;
        fclose(fp);
    }
    return status;
}

void read_file(FILE *fp, char *term) {
    char *line = NULL;
    size_t size = 0;
    ssize_t read;

    while ((read = getline(&line, &size, fp)) != -1) {
        if (strstr(line, term)) {
            printf("%s", line);
        }
    }

    free(line);
}
