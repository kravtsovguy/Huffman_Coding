//
//  huffman.cpp
//  Task_9
//
//  Created by Matvey Kravtsov on 16.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#include "huffman.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <streambuf>
#include <cerrno>
#include <iostream>
#include <map>
#include <bitset>
using namespace std;


vector<bool> string_to_bits(string s)
{
    vector<bool> v;
    for (int i = 0; i < s.size(); i++) {
        cout << (int)(unsigned char)s[i] << " ";
        //bitset<8> b(s[i]);
        int c = (int)(unsigned char)s[i];
        for (int j = 0; j < 8; j++)
        {
            int bit = (c >> (7 - j)) & 1;
            v.push_back(bit == 1);
        }
    }
    cout << endl;
    return v;
}

string bits_to_string(vector<bool> bits)
{
    while (bits.size() % 8 != 0)
        bits.push_back(false);
    
    string res = "";
    
    unsigned char currbyte = 0;
    int bitcount = 0;
    
    for (int i=0; i < bits.size(); i++) {
        //int bit = bits[i] ? 1 : 0;
        currbyte = currbyte << 1 | bits[i];
        bitcount++;
        if (bitcount == 8)
        {
            cout << (int)currbyte << " ";
            res += currbyte;
            bitcount = 0;
            currbyte = 0;
        }
    }
    cout << endl;
    return res;
}

string get_file_contents(string filename)
{
    cout << filename << endl;
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if(in)
        return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
    throw(errno);

}

Huffman::Huffman(string inputFileName)
{
    fileName = inputFileName;
}

Huffman::~Huffman()
{
    delete head;
    head = nullptr;
    table.clear();
}

void Huffman::code_init()
{
    content = get_file_contents(fileName+".txt");
    cout << content << endl;
    make_freq();
    make_tree();
    make_table("",head);
}

void Huffman::decode_init()
{
    ifstream in(fileName + "."+ext);
    string coded_tree, coded_content, temp;
    int coded_length;
    char c1,c2;
    while (true) {
        in.get(c1);
        c2 = in.peek();
        if (c1 == '\n' && c2== '\n')
            break;
        
        coded_tree += c1;
    }
    in >> coded_length;
    in.get();
    while (in.get(c1))
        coded_content += c1;
    
    cout << endl << coded_content.size() << endl;
    //coded_content = string(istreambuf_iterator<char>(in), istreambuf_iterator<char>());
    /*getline(in, coded_tree);
     getline(in, temp);
     getline(in, coded_content);
     coded_length = atoi(temp.c_str());*/
    decode_tree(coded_tree);
    vector<bool> bits = string_to_bits(coded_content);
    while (bits.size() > coded_length)
        bits.pop_back();
    content = decode(bits);
    cout << content << endl;
}

void Huffman::save_coded(string outputFileName)
{
    code_init();
    
    vector<bool> bits = code(content);
    string s = bits_to_string(bits);

    ofstream out(outputFileName+"."+ext, std::ios::out | std::ios::binary);

    out << codedTree << "\n";
    out << "\n";
    out << bits.size() << "\n";
    out << s;
    out.close();
}

void Huffman::save_decoded(string outputFileName)
{
    decode_init();
    
    ofstream out(outputFileName+"-unz-h.txt", std::ios::out | std::ios::binary);
    out << content;
    out.close();
}

void Huffman::decompress(string inputFileName, string outputFileName)
{
    Huffman(inputFileName).save_decoded(outputFileName);
}


void Huffman::compress(string inputFileName, string outputFileName)
{
    Huffman(inputFileName).save_coded(outputFileName);
}

void Huffman::make_table(string bits, Node* n)
{
    if (!n->left && !n->left)
    {
        codedTree +="1"+string(1,n->value);
        table[n->value] = bits;
        
        if (head == n)
            table[n->value] = "0";
        
        return;
    }
    
    make_table(bits+"0", n->left);
    make_table(bits+"1", n->right);
    codedTree += "0";
}

void Huffman::decode_tree(string str)
{
    vector<Node*> v;
    for (int i=0; i<str.size(); i++)
    {
        if(str[i] == '1')
        {
            i++;
            v.push_back(new Node(-1, str[i]));
            continue;
        }
        Node* n1 = v.back();
        v.pop_back();
        Node* n2 = v.back();
        v.pop_back();
        Node* n = new Node(-1,-1);
        n->left = n2;
        n->right = n1;
        v.push_back(n);
    }
    
    head = v[0];
}

void Huffman::make_freq()
{
    int bsize = 256;
    int freq[bsize];
    
    for (int i = 0; i < bsize; i++)
        freq[i] = 0;
    
    for (int i = 0; i < content.size(); i++)
        freq[content[i]]++;
    
    for (int i = 0; i < bsize; i++)
    {
        if (freq[i] == 0) continue;
        Node* n = new Node(freq[i], i);
        v.push_back(n);
    }
    
    sort(v.begin(), v.end(), Node::greater);
}

void Huffman::make_tree()
{
    while (v.size() > 1)
    {
        Node* n1 = v.back();
        v.pop_back();
        Node* n2 = v.back();
        v.pop_back();
        Node* n = new Node(n1->key + n2->key, -1);
        n->left = n1;
        n->right = n2;
        v.push_back(n);
        sort(v.begin(), v.end(), Node::greater);
    }
    
    head = v[0];
}

vector<bool> Huffman::code(string symbols)
{
    vector<bool> v;
    for (int i=0; i<symbols.size(); i++)
    {
        string bits = table[symbols[i]];
        for (int j=0; j<bits.size(); j++)
            v.push_back(bits[j] == '1');
    }
    return v;
}

string Huffman::decode(vector<bool> bits)
{
    string s = "";
    Node* n = head;
    for (int i = 0; i < bits.size(); i++)
    {
        if(n->left && n->right)
        {
            n = bits[i] ? n->right : n->left;
        }
    
        if (!n->left && !n->left)
        {
            s+=string(1,n->value);
            n = head;
        }
    }
    return s;
}
