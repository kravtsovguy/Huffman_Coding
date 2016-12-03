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
        char value;
        Node *left = nullptr, *right = nullptr;
        
        Node(int key, char value): key(key), value(value)
        {}
        
        ~Node()
        {
            delete left;
            delete right;
            left = nullptr;
            right = nullptr;
        }

        static bool greater(const Node* n1, const Node* n2 )
        {
            return n1->key > n2->key;
        }
    };
    
public:
    
    Huffman(const string& filename);
    ~Huffman();

    void compress();
    void decompress();
    
    void delete_files();
    
protected:
    
    virtual void make_tree();
    
    string ext_coded = ".huff";
    string ext_decoded = "-unz-h.txt";
    
    Node* head = nullptr;
    vector<Node*> v;
    
private:
    
    void clear_vars();
    
    void make_freq();
    void make_table(const string& bits, Node* n);
    
    void code();
    void decode();
    
    void code_content();
    void code_tree();
    void code_excess();
    
    void decode_content();
    void decode_tree();
    void decode_excess();
    
    vector<bool> string_to_bits(const string& str);
    string bits_to_string(const vector<bool>& bits);
    
    void read_all(const string& path, string& str);
    void write_all(const string& path,const string& str);

    
    int pos = 0;
    string filename = "";
    string content = "";
    string coded_content = "";
    vector<bool> coded_bits;
    map<char,string> table;
    
};


#endif /* huffman_h */
