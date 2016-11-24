//
//  huffman.cpp
//  Task_9
//
//  Created by Matvey Kravtsov on 16.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#include "huffman.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include "timer.h"
#include <cstdio>
using namespace std;

void Huffman::delete_all(string filename)
{
    Huffman(filename).delete_all_files();
}

void Huffman::decompress(string filename)
{
    Huffman(filename).save_decoded();
}

void Huffman::compress(string filename)
{
    Huffman(filename).save_coded();
}

vector<bool> string_to_bits(string s)
{
    vector<bool> v;
    for (int i = 0; i < s.size(); i++) {
        //cout << (int)(unsigned char)s[i] << " ";
        char c = s[i];
        for (int j = 0; j < 8; j++)
        {
            int bit = (c >> (7 - j)) & 1;
            v.push_back(bit == 1);
        }
    }
    //cout << endl;
    return v;
}

string bits_to_string(vector<bool> bits)
{
    while (bits.size() % 8 != 0)
        bits.push_back(false);
    
    string res = "";
    
    char currbyte = 0;
    int bitcount = 0;
    
    for (int i=0; i < bits.size(); i++) {
        currbyte = currbyte << 1 | bits[i];
        bitcount++;
        if (bitcount == 8)
        {
            //cout << (int)(unsigned char)currbyte << " ";
            res += currbyte;
            bitcount = 0;
            currbyte = 0;
        }
    }
    //cout << endl;
    return res;
}

Huffman::Huffman(string filename)
{
    this->filename = filename;
    //cout << fileName << endl;
}

Huffman::~Huffman()
{
    clear_vars();
}

void Huffman::clear_vars()
{
    content = "";
    coded_tree = "";
    coded_content = "";
    v.clear();
    table.clear();
    coded_bits.clear();

    delete head;
    head = nullptr;
}

void Huffman::code()
{
    clear_vars();
    
    ifstream in(filename+".txt");

    char c;
    while (in.get(c))
        content += c;
    
    //cout << content << endl;
    make_freq();
    make_tree();
    
    if (head)
        make_table("",head);
    
    code_content_to_bits();
    coded_content = bits_to_string(coded_bits);
}

void Huffman::save_coded()
{
    Timer::start();
    
    code();
    
    Timer::stop();
    
    ofstream out(filename + ext_coded);
    
    out << coded_tree << "\n";
    out << "\n";
    out << coded_bits.size() << "\n";
    out << coded_content;
    out.close();
}

void Huffman::decode()
{
    clear_vars();
    
    ifstream in(filename + ext_coded);
    
    int coded_length;
    char c1,c2;
    
    while (true)
    {
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
    
    decode_tree();
    
    coded_bits = string_to_bits(coded_content);
    
    while (coded_bits.size() > coded_length)
        coded_bits.pop_back();
    
    decode_content_from_bits();
    //cout << content << endl;
}

void Huffman::save_decoded()
{
    Timer::start();
    
    decode();
    
    Timer::stop();
    
    ofstream out(filename+ext_decoded);
    out << content;
    out.close();
}

void Huffman::make_table(string bits, Node* n)
{
    if (!n->left && !n->left)
    {
        coded_tree +="1"+string(1,n->value);
        table[n->value] = bits;
        
        if (head == n)
            table[n->value] = "0";
        
        return;
    }
    
    make_table(bits+"0", n->left);
    make_table(bits+"1", n->right);
    coded_tree += "0";
}

void Huffman::decode_tree()
{
    v.clear();
    
    for (int i=0; i<coded_tree.size(); i++)
    {
        if(coded_tree[i] == '1')
        {
            i++;
            v.push_back(new Node(-1, coded_tree[i]));
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
    
    if (v.size() == 0)
        return;
    
    head = v[0];
}

void Huffman::make_freq()
{
    v.clear();
    
    map<char,int> freq;
    
    for (int i = 0; i < content.size(); i++)
        freq[content[i]]++;
    
    while (freq.size())
    {
        Node* n = new Node(freq.begin()->second, freq.begin()->first);
        v.push_back(n);
        freq.erase(freq.begin());
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
    
    if (v.size() == 0)
        return;
    
    head = v[0];
}

void Huffman::code_content_to_bits()
{
    for (int i=0; i<content.size(); i++)
    {
        string bits = table[content[i]];
        for (int j=0; j<bits.size(); j++)
            coded_bits.push_back(bits[j] == '1');
    }
}

void Huffman::decode_content_from_bits()
{
    Node* n = head;
    
    for (int i = 0; i < coded_bits.size(); i++)
    {
        if(n->left && n->right)
        {
            n = coded_bits[i] ? n->right : n->left;
        }
    
        if (!n->left && !n->left)
        {
            content+=string(1,n->value);
            n = head;
        }
    }
}

void Huffman::delete_all_files()
{
    remove((filename+".txt").c_str());
    remove((filename+ext_coded).c_str());
    remove((filename+ext_decoded).c_str());
}
