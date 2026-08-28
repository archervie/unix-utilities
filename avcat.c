#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

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
            printf("Usage: avcat [OPTION] [FILE]... \n");
            printf("Print contents of FILE(s) to standard output.");
            printf("Options:\n");
            printf("    -h, --help    Displays help and exits.\n");
            return 0;
        }
    }

    if (argc < 2) {
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) {
            fprintf(stderr, "avcat: %s: ", argv[i]);
            perror("");
            continue;
        }

        char buffer[512];

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        status = 0;

        fclose(fp);
    }
    return status;
}
