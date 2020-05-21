// Implements a dictionary's functionality

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

#define HASHTABLE_SIZE 65536

// create array of pointer-to-nodes of size HASHTABLE_SIZE
node* hashtable[HASHTABLE_SIZE];

// global variables - dictionary size AND loaded dictionary
unsigned int word_count = 0;
bool loaded = false;

// https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn
int get_hash(char* word)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(word); i<n; i++)
        hash = (hash << 2) ^ word[i];
    return hash % HASHTABLE_SIZE;
}

// check if word is in the dictionary
bool check(const char* word)
{
    // create char array to store copy of word
    int len = strlen(word);
    char word_copy[len + 1];
    
    // convert word to lowercase
    for (int i = 0; i < len; i++)
    {
       word_copy[i] = tolower(word[i]);
    }
    
    // add null terminator
    word_copy[len] = '\0';
    
    // get hash value 
    int h = get_hash(word_copy);
    
    // assign cursor node to  the bucket
    node* cursor = hashtable[h];
    
    // check until the end of the linked list
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, word_copy) == 0)
        {
            return true;
        }
        else
        {
            // check next node
            cursor = cursor->next;
        }
    }
    return false;
}

// load dictionary into hash table
bool load(const char* dictionary)
{
    // make all hash table elements NULL
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
    }
    
    // open dictionary
    FILE* dic_file = fopen(dictionary, "r");
    if (dic_file == NULL)
    {
        printf("Error opening dictionary.\n");
        return false;
    }

    while (true)
    {
        // get a space of memory for a new node
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Not enough memory for new node.");
            return false;
        }
        
        // read a word from the dictionary and store it in new_node->word
        fscanf(dic_file, "%s", new_node->word);
        new_node->next = NULL;
        
        //when end of file is reached
        if (feof(dic_file))
        {
            free(new_node);
            break;
        }

        word_count++;
        int h = get_hash(new_node->word);
        node* bucket = hashtable[h];
        
        // if bucket is empty, insert the first node
        if (bucket == NULL)
        {
            hashtable[h] = new_node;
        }
        // if bucket is not empty, attach node to front of list
        else
        {
            new_node->next = hashtable[h];
            hashtable[h] = new_node;
        }
    }
    loaded = true;
    // close dictionary
    fclose(dic_file);
    return loaded;
}

//return number of words in dic
unsigned int size(void)
{
return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node* cursor = hashtable[i];
        while (cursor != NULL)
        {
            // maintain connection to linked list using temp
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    loaded = false;
    return true;
}