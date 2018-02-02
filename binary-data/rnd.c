#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char * gen_rdm_bytestream(size_t num_bytes) {
    unsigned char *stream = malloc (num_bytes);
    size_t i;
    for (i = 0; i < num_bytes; i++) {
        stream[i] = rand();
    }
    return stream;
}

char * gen_rdm_bytestream2(size_t num_bytes) {
    char *stream = malloc (num_bytes);
    size_t i;
    for (i = 0; i < num_bytes; i++) {
        unsigned char rdm = rand();
        stream[i] = rdm;
    }
    return stream;
}

int main(int argc, char **argv) {
    srand((unsigned int)time(NULL));

    unsigned char *buffer = gen_rdm_bytestream(1);
    printf("%d\n", buffer[0]);  // unsigned char value is always promoted to int.
    free(buffer);

    char *buffer2 = gen_rdm_bytestream2(1);
    printf("%d\n", buffer[0]);  // unsigned char value is always promoted to int.
    free(buffer2);
    
    return EXIT_SUCCESS;
}

// gcc -Wall rnd.c -o rnd.out && ./rnd.out