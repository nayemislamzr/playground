#include <iostream>

/*
    ---------------
    | pseudo code |
    ---------------

    let trie a structure :
        endpoint
        pointer of trie of size 26 (total small letter alphabets)
    
    insert(str) :
        for i:=1 to str.length :
            id:= str[i] - 'a'
            if curr->next[id] == NULL :
                allocate memory for curr->next[id]
            curr = curr->next[id]
        curr->endpoint = true

    search(str) :
        for i:=1 to str.length :
            id:= str[i] - 'a'
            if curr->next[id] == NULL
                return false
            curr = curr->next[id]
        return curr->endpoint 
*/

struct trie
{
    bool endpoint;
    trie* next[26];
    trie()
    {
        endpoint = false;
        for(int i = 0 ; i < 26 ; i++)
        {
            next[i] = NULL ;
        }
    }
};

trie* root = new trie();

void insert(const std::string& str)
{
    trie* curr = root;
    for(int i = 0 ; i < str.length(); i++)
    {
        int id = str[i] - 'a';
        if(curr->next[id] == NULL)
        {
            curr->next[id] = new trie();
        }
        curr = curr->next[id];
    }
    curr->endpoint = true;
}

bool search(const std::string& str)
{
    trie* curr = root;
    for(int i = 0 ; i < str.length(); i++)
    {
        int id = str[i] - 'a';
        if(curr->next[id] == NULL)
            return false;
        curr = curr->next[id];
    }
    return curr->endpoint;
}

int main()
{
    insert("hello");
    insert("hell");
    insert("hel");
    std::cout << search("hello") << " " << search("he");
}