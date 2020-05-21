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

// Number of buckets in hash table
const unsigned int HASHTABLE_SIZE = 65536;
//variable to count the words in the dictionary
int word_count = 0;
// Hash table with set number of buckets
node *hashtable[HASHTABLE_SIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // create char array to store copy of word
    // word is a const char* and non-read actions cannot be performed on it
    int len = strlen(word);
    char word_copy[len + 1];
    
    // convert word to lowercase and store it in word_copy
    for (int i = 0; i < len; i++)
    {
       word_copy[i] = tolower(word[i]);
    }
    
    // add null terminator to end of char array
    word_copy[len] = '\0';
    
    // get hash value (a.k.a. bucket)
    int h = hash(word_copy);
    
    // assign cursor node to the first node of the bucket
    node* cursor = hashtable[h];
    
    // check until the end of the linked list
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, word_copy) == 0)
        {
            // word is in dictionary
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

// Hashes word to a number
unsigned int hash(const char *word)
{
    //https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn
    unsigned int hash_number = 0;
    for (int i=0, n=strlen(word); i<n; i++)
        hash_number = (hash_number << 2) ^ word[i];
    return hash_number % HASHTABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
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
        printf("Dictionary won't open.\n");
        return false;
    }

    while (true)
    {
        // malloc a node for each new word
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("No space in memory.\n");
            return false;
        }
        
        // read a word from the dictionary and store it in new_node->word
        fscanf(dic_file, "%s", new_node->word);
        new_node->next = NULL;
        
        //check for end of file
        if (feof(dic_file))
        {
            free(new_node);
            fclose(dic_file);
            break;
        }

        word_count++;
        
        // hashtable[h] is a pointer to a key-value pair
        int index = hash(new_node->word);
        node* bucket = hashtable[index];
        
        // if bucket is empty, insert the first node
        if (bucket == NULL)
        {
            hashtable[index] = new_node;
        }
        // if bucket is not empty, attach node to front of list
        else
        {
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
        }
        free(new_node);
    }
    // close dictionary
    fclose(dic_file);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp;
    node *cursor;

    // repeats for every index in the table
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        if (hashtable[i] == NULL)
        {
            continue;
        }

        cursor = hashtable[i];
        tmp = cursor;

        // free the memory allocated
        while (cursor->next != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        free(cursor);
    }
    return true;
}
