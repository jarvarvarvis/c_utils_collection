#ifndef _UTILS_COLLECTION_CONCAT_H
#define _UTILS_COLLECTION_CONCAT_H

// Use extra level of indirection to properly paste the tokens
// Source: https://stackoverflow.com/questions/1597007/creating-c-macro-with-and-line-token-concatenation-with-positioning-macr
#define TOKEN_CONCAT_(x, y) x ## y

/*
 * Concatenate two tokens
 */
#define TOKEN_CONCAT(x, y) TOKEN_CONCAT_(x, y)

#endif /* _UTILS_COLLECTION_CONCAT_H */
