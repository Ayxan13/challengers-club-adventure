// https://www.hackerrank.com/challenges/morgan-and-a-string/problem
#pragma GCC optimize("O3")
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

/* Aborts if fails */
void *xmalloc(size_t sz) {
    void* p = malloc(sz);
    if (!p) abort();
    return p;
}

/* Aborts if fails */
void* xrealloc(void* p, size_t sz) {
    p = realloc(p, sz);
    if (!p) abort();
    return p;
}

typedef ptrdiff_t Index;

/* Returns dynamiclly allocated memory */
char* morganAndString(char const* stra, char const* strb) {
    /*
    * We add 'Z' + 1 to the end of these strings so 
    * that shorter strings are not always smaller than
    * longer ones. O(n+m)
    */
    Index const alen = strlen(stra);
    Index const blen = strlen(strb);
    Index const reslen = alen + blen;
    
    int const sentinel = 'Z' + 1;
    char* a = xmalloc(alen + 2); /* +2 for 'Z'+1 and '\0' */
    char* b = xmalloc(blen + 2); 
    char* result = xmalloc(reslen + 1); /* +1 for '\0' */
    
    memcpy(a, stra, alen);
    memcpy(b, strb, blen);
    
    a[alen] = b[blen] = sentinel; /* this is in range bc of reallocation */
    a[alen + 1] = b[blen + 1] = result[reslen] = 0; 
    
    char *pr = result, *pa = a, *pb = b; /* iterators we can move around */
    while (*pa != sentinel && *pb != sentinel)
        if (strcmp(pa, pb) < 0) *pr++ = *pa++;
        else *pr++ = *pb++;
    
    if (*pa != sentinel)
        memcpy(pr, pa, alen - (pa - a));
    else
        memcpy(pr, pb, blen - (pb - b));
    free(a);
    free(b);
    
    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* t_endptr;
    char* t_str = readline();
    int t = strtol(t_str, &t_endptr, 10);

    if (t_endptr == t_str || *t_endptr != '\0') { exit(EXIT_FAILURE); }
    free(t_str);

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char* a = readline();

        char* b = readline();

        char* result = morganAndString(a, b);
        fprintf(fptr, "%s\n", result);
        free(result);
        free(a);
        free(b);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = xmalloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        
        data = xrealloc(data, new_length);

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = xrealloc(data, data_length);

    return data;
}
