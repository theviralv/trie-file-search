#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define llu unsigned long long
#define PB push_back
#define F first
#define S second
#define sz(a) ((ll)a.size())
const ll MOD = 1000000007;
const ll INF = 1000000000000000007;
#ifdef ONLINE_JUDGE
#define ck(x...)
#endif

        // Alphabet size (# of symbols) 
#define ALPHABET_SIZE (40) 
  
        // Converts key current character into index 
        // use only 'a' through 'z' and lower case 
int CHAR_TO_INDEX(char c){
    if(isalpha(c)){
        return (c - 'a');
    }
    if(c == '.')
        return 26;
    
    if(c == '-')
        return 27;

    if(c == '_')
        return 28;

    if(c == ' ')
        return 29;

    return 30+(c - '0');
}

vector < char > items = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','.','-','_',' ','0','1','2','3','4','5','6','7','8','9'};

        // 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        // trie node 
struct TrieNode 
{ 
    struct TrieNode *children[ALPHABET_SIZE]; 
  
            // isWordEnd is true if the node represents 
            // end of a word 
    bool isWordEnd; 
}; 
  
        // Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
    struct TrieNode *pNode = new TrieNode; 
    pNode->isWordEnd = false; 
  
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = NULL; 
  
    return pNode; 
} 
  
        // If not present, inserts key into trie.  If the 
        // key is prefix of trie node, just marks leaf node 
void insert(struct TrieNode *root,  const string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int level = 0; level < key.length(); level++) 
    { 
        int index = CHAR_TO_INDEX(key[level]); 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
            // mark last node as leaf 
    pCrawl->isWordEnd = true; 
} 
  
        // Returns true if key presents in trie, else false 
bool search(struct TrieNode *root, const string key) 
{ 
    int length = key.length(); 
    struct TrieNode *pCrawl = root; 
    for (int level = 0; level < length; level++) 
    { 
        int index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl != NULL && pCrawl->isWordEnd); 
} 
  
        // Returns 0 if current node has a child 
        // If all children are NULL, return 1. 
bool isLastNode(struct TrieNode* root) 
{ 
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        if (root->children[i]) 
            return 0; 
    return 1; 
} 
  
        // Recursive function to print auto-suggestions for given 
        // node. 
void suggestionsRec(struct TrieNode* root, string currPrefix) 
{ 
            // found a string in Trie with the given prefix 
    if (root->isWordEnd) 
    { 
        cout << currPrefix; 
        cout << endl; 
    } 
  
            // All children struct node pointers are NULL 
    if (isLastNode(root)) 
        return; 
  
    for (int i = 0; i < ALPHABET_SIZE; i++) 
    { 
        if (root->children[i]) 
        { 
                    // append current character to currPrefix string 
            currPrefix.push_back(items[i]); 
  
                    // recur over the rest 
            suggestionsRec(root->children[i], currPrefix); 
                    // remove last character 
            currPrefix.pop_back(); 
        } 
    } 
} 
  
        // print suggestions for given query prefix. 
int printAutoSuggestions(TrieNode* root, string query) 
{ 
    for(int i =0;i<query.size();i++){
        query[i] = tolower(query[i]);
    }
    struct TrieNode* pCrawl = root; 
  
            // Check if prefix is present and find the 
            // the node (of last level) with last character 
            // of given string. 
    int level; 
    int n = query.length(); 
    for (level = 0; level < n; level++) 
    { 
        int index = CHAR_TO_INDEX(query[level]); 
  
                // no string in the Trie has this prefix 
        if (!pCrawl->children[index]) 
            return 0; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
            // If prefix is present as a word. 
    bool isWord = (pCrawl->isWordEnd == true); 
  
            // If prefix is last node of tree (has no 
            // children) 
    bool isLast = isLastNode(pCrawl); 
  
            // If prefix is present as a word, but 
            // there is no subtree below the last 
            // matching node. 
    if (isWord && isLast) 
    { 
        cout << query << endl; 
        return -1; 
    } 
  
            // If there are are nodes below last 
            // matching character. 
    if (!isLast) 
    { 
        string prefix = query; 
        suggestionsRec(pCrawl, prefix); 
        return 1; 
    }
    return 0;
}

int main(){

	freopen("/home/theviralv/Desktop/dir.txt", "w", stdout);   //to store the current dir location into dir.txt
    
    system("pwd");  //to cout the current dir location

    ifstream loc;
    loc.open("/home/theviralv/Desktop/dir.txt");
    string dir;
    getline(loc, dir);  //store current dir location into string (dir)
    loc.close();
    
    freopen("/home/theviralv/Desktop/file_names.txt", "w", stdout); //to store all the file names in current dir location into file_names.txt

    string qq = "cd " + dir + " && ls"; //qq is the query to print all file names in current directory
    system(qq.c_str());
	
    ifstream names;
    names.open("/home/theviralv/Desktop/file_names.txt");
    string name;
	
    struct TrieNode* root = getNode();
	while(getline(names, name)){   //to store all fie names name by name into string(name)
        for(int i =0;i<name.size();i++){
            name[i] = tolower(name[i]);
        }
        insert(root, name); //to insert the name into TRIE
	}
    
    names.close();

    freopen("/dev/tty", "w", stdout);   //to redirect outputs to the bash again
    
    string query;
    while(true){
        cin>>query;
        cout<<"----\n";
        printAutoSuggestions(root, query);  //to print all the search suggestions based on the query
        cout<<"----\n\n";
    }

	return 0;
}