#ifndef _LOGGING_H
#define _LOGGING_H

#include <stdint.h>

typedef uint64_t time64_t;

void logging_init();
void klog(char *msg, char *service);

#endif
