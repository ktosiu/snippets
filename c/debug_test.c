#include "debug.h"
#include "stdlib.h"

void test_debug()
{
    debug("I have brown hair");

    debug("I am %d years old", 30);
}

void test_log_err()
{
    log_err("I believe everythin is broken");
    log_err("There are %d problems in %s", 20, "space");
}

void test_log_warn()
{
    log_warn("You can safely ignore this");
    log_warn("Maybe consider looking at: %s", "/etc/passwd");
}

void test_log_info()
{
    log_info("This is just an info");
    log_info("It happened %f times today.", 1.8f);
}

int test_check(char* file_name)
{
    FILE *file = NULL;
    char *block = NULL;

    block = malloc(100);
    check_mem(block);

    file = fopen(file_name, "r");
    check(file, "Failed to open %s.", file_name);

    free(block);
    fclose(file);
    return 0;

error:
    if(block) free(block);
    if(file) fclose(file);
    return -1;
}

int main(int argc, char* argv[])
{
    check(argc == 2, "Need one argument");
    test_debug();
    test_check(argv[1]);
    test_log_info();
    test_log_warn();
    test_log_err();
error:
    return -1;
}
