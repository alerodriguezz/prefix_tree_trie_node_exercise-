#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;

//set up nodes
struct TrieNode {
    bool leaf;
    vector<TrieNode *> alpha;
    public:
    TrieNode() {
        leaf = false;
        alpha = vector<TrieNode *>(26,NULL);
    }
    
};


//set up Tree
class Trie {
    TrieNode *root;
    
  public:
      Trie() {
          root = new TrieNode();
      }
    
      
    void insert(string str);
    bool lookup(string str);
    void alphabetical();
    void alphaHelp(TrieNode* curr,string str);
    void remove(string str);
    void removeHelper(TrieNode* curr, string str, int iter);
    bool childrenCheck(TrieNode* curr);
    void count();
    int countHelp(TrieNode* curr, int cnt);
    void autocomplete(string prefix);
    void autoHelper(TrieNode* curr,string prefix);

  };

  void Trie:: insert(string str){
      TrieNode* curr= root;
      //traverse through word contents 
      for (int i=0;i<str.length();i++)
      {
          //if new node does not already exist 
          if(curr->alpha[str[i]-'a']==NULL)
          {      
              curr->alpha[str[i]-'a'] = new TrieNode();
          }
          
          //otherwise move on to next pointer 
          curr= curr->alpha[str[i]-'a'];
      }
      
      //current node becomes leaf
      curr->leaf=true;
}

//helper functions 
  void Trie:: alphabetical(){
      
      alphaHelp(root,"");
  }

  void Trie:: alphaHelp(TrieNode* curr, string str)
  {
      //if we reached end of the word...
      if(curr->leaf==true)
      {
          cout<< str<< endl;
      }
      
      //traverse through the alphabet 
      for(int i=0;i< curr->alpha.size();i++)
      {   //if node exists
          if(curr->alpha[i]!=NULL)
          { //cout << "test" ;
              //add to string in function call 
              alphaHelp(curr->alpha[i], str+(char)('a'+i));
          }
          
      }
  } 

//check for children, true-- if no children false-- yes children
  bool children(TrieNode* curr)
  {
    for(int i=0;i<26;i++)
    {
      //looks through entire alphabet to check for any existing nodes
      if (curr->alpha[i])
      {
        return false;
      }
    }

  return true;
  }

void Trie:: count()
{
  cout <<endl<< countHelp(root,0);
}


  int Trie:: countHelp(TrieNode* curr,int cnt)
    { 
    cnt=0;

    //every leaf indicates a word so keep track of that...
    if(curr->leaf==true)
    {
         cnt++;
    }

    //recurse into any nodes that have leaves
    for(int i=0;i<curr->alpha.size();i++)
    {
      if(curr->alpha[i])
      {
        cnt+=countHelp(curr->alpha[i],cnt);
      }

    }
    
    return cnt;
  }
bool Trie:: lookup(string find)
{
    TrieNode* curr= root;
    //traverse through word contents 
    for (int i=0;i<find.length();i++)
    {
        //if i-th letter does not exist
        if(curr->alpha[find[i]-'a']==NULL)
        {      
            return false;
        }
        
        //if letter matches... move on to next 
        curr= curr->alpha[find[i]-'a'];
    }
        
    //if false its probably the prefix of another word
    if(curr->leaf==false)
    {
        cout <<  "0" << endl;
        return false;
    }
    //otherwise we have found our letter!!
    else 
    {
      cout << "1" << endl;
    return true;
    }
}

//remove
  void Trie:: remove(string str) {
      removeHelper(root,str, 0);
  }

  void Trie:: removeHelper(TrieNode *curr,string str, int iter)
  {
      //if tree is empty 
      if(curr==NULL){return;}

    //traverse through word contents 
    for (int i=0;i<str.length();i++)
    {
        //if i-th letter does not exist
        if(curr->alpha[str[i]-'a']==NULL)
        {      
            cout << str[i]-'a' << " does not exist." << endl;
            return;
        }
        
        //if letter matches... move on to next 
        curr= curr->alpha[str[i]-'a'];
    }
        
    //if false its probably the prefix of another word
    if(curr->leaf==false)
    {
        return;
    }
    //otherwise we have found our letter!!
    else 
    {
      //remove leaf 
      curr->leaf=false;
      cout << "deleted " << str << endl;
    return;
    }
  }

  // Returns 0 if current node has a child 
// If all children are NULL, return 1. 
bool isLastNode(TrieNode* curr) 
{ 
    for (int i = 0; i < curr->alpha.size(); i++) 
        if (curr->alpha[i]) 
            return 0; 
    return 1; 
} 



//autocomplete
  void Trie:: autocomplete(string prefix)
  {
  autoHelper(root,prefix);
  }

  void Trie:: autoHelper(TrieNode* curr, string prefix){

    //every leaf indicates a word so keep track of that...
    if(!curr->leaf)
    { 
       cout << prefix << endl;
    }

    /*cout << curr->alpha[9] << endl;
     cout << prefix[0]-'a'  << endl;
    cout << str+(char)('a'+9) << endl;*/

    //breaking point
    if(isLastNode(curr))
    {
      return;
    }


          
    for(int i=0;i<curr->alpha.size();++i)
    {
      //if node exists
      if(curr->alpha[i]!=NULL)
      {
        prefix.push_back((char)('a'+i));

        autoHelper(curr->alpha[i], prefix);
      }

    }
    



    /*if(curr->alpha[prefix[0]-'a']!=NULL&&!prefix.empty())
      {
        autoHelper(curr->alpha[prefix[0]-'a'],str+(char)('a'+j),prefix.substr(0,prefix.length()));
      }
      */
  
  

    

  }



int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    Trie* root = new Trie();
    
     
     root->insert("emma");
     root->insert("bob");
     root->insert("jane");
     root->insert("janet");
     root->insert("janetta");
     root->insert("carl");
     /*root->lookup("carl");
     root->remove("carl");
     root->lookup("carl");*/
    
    root->alphabetical();
    root->count();
     cout << endl;
    root->remove("bob");
    root->alphabetical();

    root->count();

    root->autocomplete("ja");
    
    return 0;
}