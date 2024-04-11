#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

struct AhoTrieNode
{
    unordered_map<char, int> children; // Links to the children of the node
    int parent;                        // Link to parent
    int failure_link;                  // Failure link of current node
    int end_word_link;                 // Link to a node that contains the end of a word (template) that can be built from the current prefix
    int word_ID;                       // ID, label, template from the set
    char parent_char;                  // The character used to get from the parent to the current node
    bool word_end;                     // Flag indicating if a template from the set ends in this node
    AhoTrieNode();
};

AhoTrieNode::AhoTrieNode()
{
    parent = -1;
    failure_link = -1;
    end_word_link = -1;
    word_ID = -1;
    word_end = false;
}

struct AhoTrie
{
    vector<AhoTrieNode> trie;
    vector<int> words_length;
    int size;
    int root;
    int wordID; // The ID of the last word inserted

    AhoTrie();

    void insert(string);
    void buildTree();
    int search(string);
    void calcFailureLink(int);
};

AhoTrie::AhoTrie() : size(0), root(0), wordID(0)
{
    // build tree with single node (root)
    trie.push_back(AhoTrieNode());
    size++;
}

void AhoTrie::insert(string s)
{
    int current = root;
    // loop through each character in the word s
    for (int i = 0; i < s.length(); i++)
    {
        // check if there is already a node with this edge
        if (trie[current].children.find(s[i]) == trie[current].children.end())
        {
            // move to the next node in the tree
            trie.push_back(AhoTrieNode());
            trie[current].children[s[i]] = size;
            trie[size].parent = current;
            trie[size].parent_char = s[i];
            size++;
        }
        current = trie[current].children[s[i]];
    }
    // labels the node where the word ends (stores the ID)
    trie[current].word_end = true;
    trie[current].word_ID = wordID++;
    words_length.push_back(s.length());
}

void AhoTrie::buildTree()
{
    queue<int> nodesQueue;
    nodesQueue.push(root);

    while (!nodesQueue.empty())
    {
        int currentNode = nodesQueue.front();
        nodesQueue.pop();

        calcFailureLink(currentNode);

        for (auto child : trie[currentNode].children)
        {
            nodesQueue.push(child.second);
        }
    }
}

void AhoTrie::calcFailureLink(int node)
{
    if (node == root || trie[node].parent == root)
    {
        trie[node].failure_link = root;
        trie[node].end_word_link = root;
    }
    else
    {
        int fail = trie[trie[node].parent].failure_link;
        char nodeChar = trie[node].parent_char;

        while (fail != root && trie[fail].children.find(nodeChar) == trie[fail].children.end())
        {
            fail = trie[fail].failure_link;
        }

        if (trie[fail].children.find(nodeChar) != trie[fail].children.end())
        {
            fail = trie[fail].children[nodeChar];
        }

        trie[node].failure_link = fail;

        trie[node].end_word_link = (trie[fail].word_end) ? fail : trie[fail].end_word_link;
    }
}

int AhoTrie::search(string text)
{
    int currentState = root;

    int result = 0;

    for (int j = 0; j < text.size(); j++)
    {
        cout << text << endl;
        for (int p = 0; p <= j; p++)
            cout << "-";
        cout << endl;

        while (true)
        {
            if (trie[currentState].children.find(text[j]) != trie[currentState].children.end())
            {
                currentState = trie[currentState].children[text[j]];
                break;
            }

            if (currentState == root)
                break;

            currentState = trie[currentState].failure_link;
        }

        int checkState = currentState;
        while (checkState != root)
        {
            if (trie[checkState].word_end)
            {
                result++;
                int indexOfMatch = j + 1 - words_length[trie[checkState].word_ID];
                string w = text.substr(indexOfMatch, words_length[trie[checkState].word_ID]);
                cout << "The template '" << w << "' appears in the text from the position " << indexOfMatch << endl;
            }

            checkState = trie[checkState].failure_link;
        }
    }

    return result;
}
