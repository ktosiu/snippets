#include "link_list.h"
#include <string.h>

int main()
{
    struct list* test_list = list_create();

    char* str1 = "string_1";
    list_push_front(test_list, str1);

    char* str2 = "string_2";
    list_push_front(test_list, str2);

    char* str3 = "string_3";
    list_push_front(test_list, str3);

    list_push_front(test_list, "string_4");

    /*list_bubble_sort(test_list, (list_compare)strcmp);*/

    list_reverse(test_list);

    /*list_remove(test_list, test_list->first);*/

    list_print(test_list);

    /*list_clear(test_list);*/
    return 0;
}
