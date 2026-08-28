#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error_msg();

int main(int argc, char *argv[]) {
    int c;
    int option_index = 0;
    // 0 is for substitution, 1 is for translation
    int mode = -1;

    while (1) {
        static struct option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {"mode", required_argument, 0, 'm'},
            {0, 0, 0, 0}};

        c = getopt_long(argc, argv, "m:h", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 'm':
            if (mode != -1) {
                error_msg();
            }

            else if (strcmp(optarg, "substitution") == 0) {
                mode = 0;
            } else if (strcmp(optarg, "translation") == 0) {
                mode = 1;
            } else {
                fprintf(stderr, "avsed: Unknown mode detected\nMode must be "
                                "\"substitution\" or \"translation\"\n");
                return 1;
            }

            break;

        case 'h':
            printf("Usage: avsed [OPTION] INITIAL FINAL [FILE]\n");
            printf("Substitution mode replaces a term with another term within "
                   "FILE. Translation mode replaces the characters of the "
                   "first input with the corresponding characters of the "
                   "second input in FILE.");
            printf("Options: ");
            printf("    -h, --help: Displays help and exits");
            printf("    -m, --mode: Chooses the mode.");
            printf("Potential values for -m are 'substitution' and "
                   "'translation'.");
            printf("The default value is substitution.");
            return 0;

        default:
            error_msg();
        }
    }

    if (argc - optind != 3) {
        error_msg();
    }

    if (mode == -1) {
        mode = 0;
    }

    char *initial = argv[optind];
    char *final = argv[optind + 1];
    char *file = argv[optind + 2];

    if (mode == 1) {
        if (strlen(initial) != strlen(final)) {
            printf("avsed: Translation strings not equal length\n");
            return 1;
        }
    }

    FILE *fp = fopen(file, "r");

    if (fp == NULL) {
        fprintf(stderr, "avcat: %s: ", file);
        perror("");
        return 1;
    }

    char *line = NULL;
    size_t size = 0;
    ssize_t read;

    if (mode == 0) {
        while ((read = getline(&line, &size, fp)) != -1) {

            char *current = line;
            char *match;

            while ((match = strstr(current, initial)) != NULL) {
                while (current < match) {
                    printf("%c", *current);
                    current++;
                }
                printf("%s", final);
                current += strlen(initial);
            }
            printf("%s", current);
        }
    } else {
        while ((read = getline(&line, &size, fp)) != -1) {
            for (int i = 0; i < read; i++) {

                int found = 0;

                for (int j = 0; j < strlen(initial); j++) {
                    if (line[i] == initial[j]) {
                        printf("%c", final[j]);
                        found = 1;
                        break;
                    }
                }
                if (found == 0) {
                    printf("%c", line[i]);
                }
            }
        }
    }

    free(line);
    fclose(fp);
    return 0;
}

void error_msg() {
    printf("avsed: [OPTION] INITIAL FINAL [FILE]\n");
    exit(1);
}
