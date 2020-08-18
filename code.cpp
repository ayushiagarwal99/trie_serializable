//author : Ayushi Agarwal
#include<bits/stdc++.h>
using namespace std;

//This structure is used to represent a node of the trie.
struct Node{
    //character representing the node
    char data;
    
    //represent all child nodes of this node.
    unordered_map<char, Node*> children;
    
    //indicates if the word ending here is a valid word.
    bool terminal;
    
    //number of words have the prefix that is represented by this node.
    int wordsWithPrefix;
    
    Node(char val){
        data = val;
        terminal = false;
        wordsWithPrefix = 0;
    }
};

//This class represents a generic trie data structure
class Trie
{
    private:
        Node *root;
        int totalWords;
    
        //helper function that traverse the trie and finds all word present in trie.
        void treeDepthTraversal(Node *temp, vector<string>& trieToString, string prefix)
        {
            if(temp->terminal)
            {
                trieToString.push_back(prefix);
            }
            for(auto p : temp->children)
            {
                prefix.push_back(p.first);
                treeDepthTraversal(p.second, trieToString, prefix);
                prefix.pop_back();
            }
        }
    
        //helper function
       void buildSerialTrie(Node *root, string &serialTrie)
       {
           if(root->terminal)
              serialTrie.push_back(']');
           
           for(auto child : root->children)
           {
               serialTrie.push_back(child.first);
               buildSerialTrie(child.second, serialTrie);
           }
           serialTrie.push_back('>');
       }
    
        //helper function
       int stringToTrie(Node *temp, string &serialTrie, int &ind)
       {
            int wordSeen = 0;
            if(serialTrie[ind] == ']')
            {
               temp->terminal = true;
               wordSeen++;
               ind++;
            }
            else temp->terminal = false;

            while(serialTrie[ind] != '>')
            {
                char ch = serialTrie[ind++];
                temp->children[ch] = new Node(ch);
                wordSeen += stringToTrie(temp->children[ch], serialTrie, ind);
            }
           
            ind++;
            temp->wordsWithPrefix = wordSeen;
            return wordSeen;
       }

    
    
    public:
    
        //used to construct an empty trie.
        Trie()
        {
            root = new Node('\0');
            totalWords = 0;
        }
    
        //Used to construct a trie initialized with a list of words.
        Trie(vector<string>& input)
        {
            root = new Node('\0');
            totalWords = 0;
            for(string word : input)
            {
                insertWord(word);
            }
        }
    
        //Used to construct a trie using an existing trie given in serial format.
        Trie(string serialTrie)
        {
            root = new Node('\0');
            int ind = 0;
            totalWords = stringToTrie(root, serialTrie, ind);
        }
    
    
        //used to insert a word in the trie.
        void insertWord(string word)
        {
           Node *temp = root;
           
           for(int i=0; i<word.length(); i++)
           {
               temp->wordsWithPrefix++;
               char ch = word[i];
               
               if(temp->children.find(ch) == temp->children.end())
               {
                   Node *n = new Node(ch);
                   temp->children[ch] = n;
                   temp = n;
               }
               else
               {
                   temp = temp->children[ch];
               }
           }
           temp->wordsWithPrefix++;
           temp->terminal = true;
           totalWords++;
        }
    
        //gives the total number of words currently present in the trie.
       int numberOfWordsInTrie()
       {
           return totalWords;
       }
    
        //Used to convert the trie to a list of words(serialization).
        vector<string> trieToList()
        {
            vector<string> trieToString;
   	        treeDepthTraversal(root, trieToString, "");
   	        return trieToString;
        }
    
        //check to see if a word is present in the trie.
        bool findWord(string word)
        {
            int countOfWord = wordsWithThePrefix(word,0);
            if(countOfWord > 0)
                return true;
            else return false;
        }
    
        //Number of words in the trie the have a given prefix.
        int wordsWithThePrefix(string prefix, int calledBy = 1)
        {
            if(root==NULL)
                return 0;
            
            Node *temp = root;
            for(int i = 0; i < prefix.length(); i++)
            {
                char ch = prefix[i];
                
                if(temp->children.find(ch) == temp->children.end())
                    return 0;
                else
                    temp = temp->children[ch];
            }
            
            if(calledBy || temp->terminal)
                return temp->wordsWithPrefix;
            else 
                return 0;
        }
    
        //serializing the trie
        string trieToString()
        {
            string serializedTrie;
            buildSerialTrie(root, serializedTrie);
            return serializedTrie;
        }
};

int main() {
    /*
     *THIS PROGRAM USES THE TEST DATA
     *TO BUILD A TRIE FOR THE GIVEN DATA
     *THEN IT CONVERTS THE TRIE INTO ITS
     *SERIALIZED FORM AND WRITES IT TO A FILE
     */
    
    freopen("TEST_DATA.txt","r",stdin);
    freopen("SERIAL_FORM.txt","w",stdout);
    
    //take input from user
    vector<string> input;
    string word;
    cin>>word;
    
    while(word != "#END#")
    {
        input.push_back(word);
        cin>>word;
    }
    
    //built a trie using the user input
    Trie *myTrie = new Trie(input);
    
    //serializing the trie
    cout<<myTrie->trieToString();
    return 0;
}
