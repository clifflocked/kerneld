#ifndef _STDDEF_H
#define _STDDEF_H

#define NULL nullptr

typedef typeof(sizeof(0)) size_t;
typedef typeof((int *)nullptr - (int *)nullptr) ptrdiff_t;
typedef typeof(nullptr) nullptr_t;

typedef struct {
    long long __max_align_ll;
    long double __max_align_ld;
} max_align_t;

#endif
