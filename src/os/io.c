#include "io.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CHUNK_SIZE 128

char *io_read_full_file_to_string(char *path) {
    FILE *input_file = fopen(path, "r");
    if (!input_file) {
        return NULL;
    }

    size_t buffer_capacity = 256;
    char *buffer = malloc(sizeof(char) * (buffer_capacity + 1));
    memset(buffer, 0, sizeof(char) * (buffer_capacity + 1));

    size_t buffer_size = 0;

    char chunk[CHUNK_SIZE];
    while (fgets(chunk, sizeof(chunk), input_file) != NULL) {
        // Increase buffer size
        buffer_size += CHUNK_SIZE;

        // Reallocate buffer if necessary
        if (buffer_size >= buffer_capacity) {
            buffer_capacity *= 2;
            buffer = realloc(buffer, sizeof(char) * (buffer_capacity + 1));
        }

        // Append chunk to buffer
        strncat(buffer, chunk, sizeof(char) * CHUNK_SIZE);
    }

    // Close the input file after we're done
    fclose(input_file);

    return buffer;
}
