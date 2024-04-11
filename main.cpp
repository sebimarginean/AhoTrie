#include <iostream>
#include <string>

#include "Trie.h"
#include "AhoCorasick.h"

using namespace std;

int main()
{
    string P[] = {"ana", "are", "mare", "ananas", "arc", "arena"}; // Template
    string T = "xmarenananas"; // text

    // TRIE --------------------------------------
    Trie t;
    for(int i = 0; i < 6; i++)
        t.insert(P[i]);
    
    char print[20];
    t.print(t.root, print, 0);
    cout<< "-------------------------------------------"<<endl;

    // AHO-CORASICK ------------------------------
    AhoTrie at;
    
    for(int i = 0; i < 6; i++)
        at.insert(P[i]);
    
    at.buildTree();
    
    int potriviri = at.search(T);
    cout << "Nr. total de potriviri: " << potriviri << endl;

    return 0;
}
