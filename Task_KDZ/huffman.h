//
//  huffman.hpp
//  Task_9
//
//  Created by Matvey Kravtsov on 16.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#ifndef huffman_h
#define huffman_h

#include <string>
#include <vector>
#include <map>
using namespace std;

class Huffman
{
    
protected:
    
    class Node
    {
    public:
        int key;
        int value;
        Node *left = nullptr, *right = nullptr;
        
        Node(int key, int value): key(key), value(value)
        {}
        
        ~Node()
        {
            delete left;
            delete right;
            left = nullptr;
            right = nullptr;
        }

        static bool greater( Node* n1, Node* n2 )
        {
            return n1->key > n2->key;
        }
    };
    
public:
    
    static void compress(string filename);
    
    static void decompress(string filename);
    
    Huffman(string filename);
    
    void save_coded();
    
    void save_decoded();
    
    ~Huffman();
    
protected:
    
    string ext_coded = ".huff";
    
    string ext_decoded = "-unz-h.txt";
    
    Node* head = nullptr;
    
    vector<Node*> v;
    
    virtual void make_tree();
    
private:
    
    string filename = "";
    
    string content = "";
    
    string coded_tree = "";

    map<char,string> table;
    
    void make_freq();
    
    void make_table(string bits, Node* n);
    
    void code_init();
    
    void decode_init();
    
    vector<bool> code(string symbols);
    
    string decode(vector<bool> bits);
    
    void decode_tree();
    

};


#endif /* huffman_h */
