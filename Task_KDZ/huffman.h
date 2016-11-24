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
    static void delete_all(string filename);
    
    void delete_all_files();
    
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
    
    string coded_content = "";
    
    vector<bool> coded_bits;

    map<char,string> table;
    
    void clear_vars();
    
    void make_freq();
    
    void make_table(string bits, Node* n);
    
    void code();
    
    void decode();
    
    void code_content_to_bits();
    
    void decode_content_from_bits();
    
    void decode_tree();
    
};


#endif /* huffman_h */
