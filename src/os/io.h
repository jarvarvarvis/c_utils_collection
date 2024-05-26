#ifndef _UTILS_COLLECTION_IO_H
#define _UTILS_COLLECTION_IO_H

/*
 * Read the full file provided by path to a heap-allocated string.
 * If the file couldn't be opened, this function will return NULL and set errno.
 */
char *io_read_full_file_to_string(char *path);

#endif /* _UTILS_COLLECTION_IO_H */
