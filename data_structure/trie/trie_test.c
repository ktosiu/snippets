#include "trie.h"
#include <stdio.h>

int main()
{
    trie_t *pTrie = trie_init();
    trie_insert(pTrie, "mark", 30);
    trie_insert(pTrie, "judy", 29);

    printf("Searched value: %d\n", trie_search(pTrie, "mark"));
    printf("Searched value: %d\n", trie_search(pTrie, "judy"));
    trie_free(pTrie);
}
