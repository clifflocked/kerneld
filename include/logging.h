#ifndef _LOGGING_H
#define _LOGGING_H

#include <stdint.h>

typedef uint64_t time64_t;

#define klog(msg) klog_service(msg, __FILE__)
#define klogf(msg, ...) klogf_service(msg, __FILE__, __VA_ARGS__)

void logging_init();
void klog_service(char *msg, char *service);
void klogf_service(char *msg, char *service, ...);

#endif
