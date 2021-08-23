// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int word_count = 0;
bool is_loaded = false;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word3)
{
    // TODO
    
    char word2[LENGTH+1];
    int h = 0;
    while(isalpha(word3[h]) || (word3[h] == '\'' && h > 0))
    {
        word2[h] = tolower(word3[h]);
        h++;
    }
    word2[h] = '\0';
    
    // printf("The check function is now checking the word %s\n", word2);
    
    int code = hash(word2);
    
    // printf("The hash code of the word %s is %i\n", word2, code);
    
    if(table[code] != NULL)
    {
        node *tmp = table[code];
        // bool shrt = false;
        while(tmp != NULL)
        {
            // int len = 0;
            // int cntr = 0;
            
            // while(tmp -> word[cntr] != '\0')
            // {
            //     cntr++;
            // }
            
            // len = cntr+1;
            
            int w = 0;
            while( (isalpha(word2[w]) || (word2[w] == '\'' && w > 0)) )
            {
                // printf("Comparing the character %c from %s and %c from reference\n", 
                // word2[w], word2, tmp->word[w]);
                // if(tmp -> word[w] == '\0')
                // {
                //     shrt = true;
                //     break;
                // }
                
                if(word2[w] != tmp -> word[w])
                {
                    // printf("Character %c from %s and %c from reference\n are not the same\n", 
                    // word2[w], word2, tmp->word[w]);
                    break;
                }
                
                w++;
            }
            
            if(word2[w] == '\0' && tmp -> word[w] == '\0')
            {
                // printf("The current word and reference have the same ending and are the same\n");
                return true;
            } 
            
            // if(!shrt)
            // {
                // if(word2[w] == '\0' && tmp -> word[w] == '\0')
                // {
                //     // printf("The current word and reference have the same ending and are the same\n");
                //     return true;
                // } 
            // }
            // printf("Switching to the next reference word\n");
            tmp = tmp ->next;
        }
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // printf("The hashing function is now active\n");
    
    
    // printf("The current word is %s\n", word);
    char wordl[LENGTH+1];
    int l = 0;
    while(isalpha(word[l]) || (word[l] == '\'' && l > 0))
    {
        wordl[l] = tolower(word[l]);
        l++;
    }
    wordl[l] = '\0';
    
    // printf("This word in lower case is %s\n", wordl);
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    
    // int counter = -1;
    
    for(int i = 0; i < 26; i++)
    {
        // for(int j = 0; j < 26; j++)
        // {
        //     for(int k = 0; k < 26; k++)
        //     {
        //         counter++;
                if(wordl[0] == alphabet[i])
                {
                    // printf("This word's first letter is %c\n", alphabet[i]);
                    return i;
                }
        //     }
        // }
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // printf("The load function is now active\n");
    
    for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    char word1[LENGTH + 1];
    
    int index = 0;
    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        // Allow only alphabetical characters and apostrophes
        // printf("The current character of %ith dictionary's word is %c\n", word_count, c);
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word1[index] = c;
            index++;
        }
        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word1[index] = '\0';
            
            // printf("The full %ith dictionary's word is ", word_count);
            // int u = 0;
            // while(word1[u] != '\0')
            // {
            //     printf("%c", word1[u]);
            //     u++;
            // }
            // printf("\n");
            
            int code = hash(word1);
            
            // printf("The hash code for the %ith word is %i\n", index, code);
            
            node *new_node = malloc(sizeof(node));
            // strcpy(new_node -> word, word1);
            
            int p = 0;
            
            for(int g = 0; g < (LENGTH+1); g++)
            {
                new_node -> word[g] = '\0';
            }
            
            while(word1[p] != '\0')
            {
                new_node -> word[p] = word1[p];
                p++;
            }
            new_node -> word[p+1] = '\0';
            
            // printf("The word assigned to the new node is ");
            
            // int q = 0;
            // while(new_node ->word[q] != '\0')
            // {
            //     printf("%c", new_node -> word[q]);
            //     q++;
            // }
            // printf("\n");
            
            new_node -> next = NULL;
            
            if(table[code] == NULL)
            {
                // printf("Nothing at the hash table's position %i yet\n", code);
                table[code] = new_node;
                // free(new_node);
            }
            else
            {
                // printf("Something at the hash table's position %i\n", code);
                node *tmp = table[code];
                // int s = 0;
                
                // printf("The %ith node in the chain at the table's position %i is ", s, code);
                // int m = 0;
                // while(tmp ->word[m] != '\0')
                // {
                //     printf("%c", new_node -> word[m]);
                //     m++;
                // }
                // printf("\n");
                
                // s++;
                
                
                while(tmp->next != NULL)
                {
                    // printf("The %ith node in the chain at the table's position %i is ", s, code);
                    // int n = 0;
                    // while(tmp ->word[n] != '\0')
                    // {
                    //     printf("%c", new_node -> word[n]);
                    //     n++;
                    // }
                    // printf("\n");
                    tmp = tmp ->next;
                    // s++;
                }
                
                tmp -> next = new_node;
                
                // free(new_node);
                
            }

            // Update counter
            word_count++;
            // printf("The current word count is %i\n", word_count);
            
            index = 0;
        }
    }
    
    is_loaded = true;
    fclose(file);
    return true;
    
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(is_loaded)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *tmp1 = table[i];
        if(table[i] != NULL)
        {
            while(tmp1 != NULL)
            {
                node *tmp = tmp1 -> next;
                free(tmp1);
                tmp1 = tmp;
            }
        }
    }
    
    return true;
}
