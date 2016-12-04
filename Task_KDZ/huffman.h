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
        unsigned char value;
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
    
    static vector<bool> string_to_bits(const string& str);
    static string bits_to_string(const vector<bool>& bits);
    
    static void read_all(const string& path, string& str);
    static void write_all(const string& path, const string& str);
    
    void clear_vars();
    
    void make_freq();
    void make_table(const string& bits, Node* n);
    
    void code();
    void code_content();
    void code_tree();
    void code_excess();
    
    void decode();
    void decode_content();
    void decode_tree();
    void decode_excess();
    
    int pos = 0;
    string filename = "";
    string content = "";
    string coded_content = "";
    vector<bool> coded_bits;
    string table[256];
    
};


#endif /* huffman_h */
