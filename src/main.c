#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FALSE 1
#define TRUE 0

size_t mem_size = 30000;
FILE *source_fp = NULL;
int step_by_step = FALSE;

int main(int argc, char **argv) {
    int c;
    while ((c = getopt(argc, argv, "sm:")) != -1) {
        char *errstr;
        switch(c) {
        case 's':
            step_by_step = TRUE;
            break;
        case 'm':
            mem_size = strtoumax(optarg, NULL, 10);
            if (mem_size == UINTMAX_MAX && errno == ERANGE || mem_size < 1) {
                fprintf(stderr, "Error: invalid number '%s'!\n", optarg);
                exit(1);
            }
            break;
        case '?':
                fprintf(stderr,"Unrecognized option: -%c\n", optopt);
            break;
        default:
            break;
        }
    }

    if (optind >= argc) {
        source_fp = stdin;
    } else {
        source_fp = fopen(argv[optind], "r");
        if (source_fp == NULL) {
            fprintf(stderr, "Error: Invalid file '%s'!\n", argv[optind]);
            exit(1); 
        }
    }

    printf("mem_size: %lu\nsource_fp: %lu\nstep_by_step: %d\n", mem_size, source_fp, step_by_step);
    return 0;
}
