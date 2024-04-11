#include <iostream>
#include <string>

using namespace std;

#if !defined(ALFABET_DIM)
#define ALFABET_DIM 26
#endif

struct TrieNode
{
    TrieNode *children[ALFABET_DIM]; // the edges for each letter in the alphabet

    bool word_end; // indicate if the node is the end of a template from the set

    TrieNode();
};

TrieNode::TrieNode()
{
    this->word_end = false;
    for (int i = 0; i < ALFABET_DIM; i++)
    {
        this->children[i] = NULL;
    }
}

struct Trie
{
    TrieNode *root;

    Trie();

    void insert(string);
    bool search(string);
    void print(TrieNode *, char[], int);
};

Trie::Trie()
{
    root = new TrieNode();
}
/**
 * Function that inserts a key template
 * in the tree
 */

void Trie::insert(string key)
{
    TrieNode *x = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!x->children[index])
        {
            x->children[index] = new TrieNode();
        }
        x = x->children[index];
    }
    x->word_end = true;
}

/**
 * Function that searches for a key template
 * in the tree
 */

bool Trie::search(string key)
{
    TrieNode *x = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!x->children[index])
        {
            return false;
        }
        x = x->children[index];
    }

    return x != NULL && x->word_end;
}

void Trie::print(TrieNode *root, char str[], int level)
{
    // If the node is labeled, indicate the end of the template and
    // then the terminal character is added and the string is displayed
    if (root->word_end)
    {
        str[level] = '\0';
        cout << str << endl;
    }

    for (int i = 0; i < ALFABET_DIM; i++)
    {
        // if it finds a non-NULL child
        // add the parent's key to str si
        // call the function recursively on the son
        if (root->children[i])
        {
            str[level] = i + 'a';
            print(root->children[i], str, level + 1);
        }
    }
}