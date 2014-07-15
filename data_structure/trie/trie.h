#include <stdlib.h>
#include <string.h>

typedef struct trie_node trie_node_t;
struct trie_node
{
    int value;
    struct trie_node *children[26];
};

typedef struct trie trie_t;
struct trie
{
    trie_node_t *root;
    int count;
};

trie_node_t *get_trie_node()
{
    trie_node_t *trie_node = (trie_node_t *)malloc(sizeof(trie_node_t));
    trie_node->value = 0;
    memset(trie_node->children, 0, sizeof(trie_node->children));
    return trie_node;
}

trie_t *trie_init()
{
    trie_t *pTrie = (trie_t*)malloc(sizeof(trie_t));

    pTrie->root = get_trie_node();
    pTrie->count = 0;

    return pTrie;
}

void trie_free(trie_t* pTrie)
{
    /*TODO: Free the children recursively*/
    free(pTrie);
}

void trie_insert(trie_t *pTrie, const char *key, int value)
{
    trie_node_t *pTrieNode = pTrie->root;
    int key_length = strlen(key);
    pTrie->count++;
    for(int i = 0; i < key_length; i++)
    {
        int index = key[i] - 'a';
        if(!pTrieNode->children[index])
        {
            pTrieNode->children[index] = get_trie_node();
        }
        pTrieNode = pTrieNode->children[index];
    }
    pTrieNode->value = value;
}

int trie_search(trie_t *pTrie, const char *key)
{
    trie_node_t *pTrieNode = pTrie->root;
    int key_length = strlen(key);
    for(int i = 0; i < key_length; i++)
    {
        int index = key[i] - 'a';
        if(!pTrieNode->children[index])
        {
            /*Not found*/
            return 0;
        }
        pTrieNode = pTrieNode->children[index];
    }
    return pTrieNode->value;
}
