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
    while ((c = getopt(argc, argv, "m:s::")) != -1) {
        char *errstr;
        switch(c) {
        case 's':
            step_by_step = TRUE;
            break;
        case 'm':
            mem_size = strtoumax(optarg, NULL, 10);
            if (mem_size == UINTMAX_MAX && errno == ERANGE) {
                fprintf(stderr, "Error: invalid number '%s'!", optarg);
                exit(1);
            }
            break;
        case ':':
            source_fp = fopen(optarg, "r");
            if (source_fp == NULL) {
                fprintf(stderr, "Error: Invalid file '%s'!", optarg);
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
    printf("mem_size: %lu\nsource_fp: %d\nstep_by_step: %d\n", mem_size, source_fp, step_by_step);
    return 0;
}
