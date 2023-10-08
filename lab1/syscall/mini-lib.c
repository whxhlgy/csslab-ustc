#include "mini-lib.h"
#include <stdarg.h>

// see:
//https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

// syscall number for x86-64, in rax
#define SYS_WRITE 1
#define SYS_SLEEP 35
#define SYS_ALARM 37
#define SYS_EXIT 60

// arguments: rdi, rsi, rdx, r10, r8, r9


#define CALL2(n) "movq $"#n", %%rax\n"
#define CALL(n) CALL2(n)

int strlen(char *s){
    int n = 0;
    while(*s++)
        n++;
    return n;
}

int printf(char *s, ...){
    va_list ap;
    int length = 0; // represent how many characters been printed
    va_start(ap, s);
    while (*s != '\0') {
        if (*s == '%') {
            s++;
            if (*s == 's') { // for string
                char *out = va_arg(ap, char*);
                length += strlen(out);
                puts(out);
            } else {
                puts("not implemented yet!\n");
                exit(1);
            }
        } else {
            putchar(*s);
            length++;
        }
        s++;
    }
    return length;
}

// put a single char to stdout
int putchar(char c) {
    char s[2];
    s[0] = c;
    s[1] = '\0';
    long r;
    asm(CALL(SYS_WRITE)
       "movq $1, %%rdi\n"
       "movq %1, %%rsi\n"
       "movq $1, %%rdx\n"
       "syscall\n"
       "movq %%rax, %0\n"
       : "=r"(r)
       : "r"(s)
       : "%rax", "%rdi", "%rsi", "%rdx");
    return (int)r;
}

int puts(char *s) {
    long n = strlen(s);
    long r;
    asm(CALL(SYS_WRITE)
       "movq $1, %%rdi\n"
       "movq %1, %%rsi\n"
       "movq %2, %%rdx\n"
       "syscall\n"
       "movq %%rax, %0\n"
       : "=r"(r)
       : "r"(s), "r"(n)
       : "%rax", "%rdi", "%rsi", "%rdx");
    return (int)r;
}


void exit(int status){
    asm volatile(
        CALL(SYS_EXIT)
        "movl %0, %%edi\n"
        "syscall\n"
        :
        : "r"(status)
        : "%rdi");
}

int alarm(unsigned int seconds){
    long r;
    asm volatile(
        CALL(SYS_ALARM)
        "movl %1, %%edi\n"
        "syscall\n"
        "movq %%rax, %0\n"
        : "=r"(r)
        : "r"(seconds)
        : "%rax", "%rdi");
    return (int) r;
}


int sleep(struct timespec *ts, struct timespec *rem){
    long r;
    asm volatile(
        CALL(SYS_SLEEP)
        "movq %1, %%rdi\n"
        "movq %2, %%rsi\n"
        "syscall\n"
        "movq %%rax, %0\n"
        : "=r"(r)
        : "r"(ts), "r"(rem)
        : "%rax", "%rdi", "%rsi");
    return (int) r;
}



