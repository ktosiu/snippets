#include "link_list.h"

int main()
{
    struct list* test_list = list_create();

    char* str1 = "string_1";
    list_push_back(test_list, str1);

    list_clear_destroy(test_list);
    return 0;
}
