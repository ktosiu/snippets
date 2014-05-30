#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <lcthw/debug.h>

#define mu_suite_start() char *message = NULL;

#define mu_assert(test, message)            \
    if(!(test)) { log_err(message); return message;}

#define mu_run_test(test)                   \
    debug("\n------%s", " " #test);         \
    message = test(); tests_run++; if(message) return message;

#define mu_run_test_suite(name)                     \
int main(int argc, char *argv[]) {          \
    if(argc != 1) {                         \
        log_err("Argument error\n");        \
        return 1;                           \
    }                                       \
    debug("\n------ RUNNING:%s", argv[0]);  \
    printf("------\nRUNNING:%s\n", argv[0]);\
    char *result = name();                  \
    if(result != 0) {                       \
       printf("Failed: %s\n", result);      \
    }                                       \
    else {                                  \
        printf("All tests passed\n");       \
    }                                       \
    printf("Tests run: %d\n", tests_run);   \
    return(result != NULL);                 \
}

int tests_run = 0;
