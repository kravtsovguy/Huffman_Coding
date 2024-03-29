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
#include <stdexcept>
using namespace std;

void Huffman::read_all(const string &path, string &str)
{
    ifstream in(path, ios::binary);
    
    if (!in.is_open())
        throw logic_error("File doesn't exist");
    
    in.seekg (0, in.end);
    size_t length = in.tellg();
    in.seekg (0, in.beg);
    
    str = string(length,0);
    in.read (&str[0],length);
    
    in.close();
}

void Huffman::write_all(const string &path, const string &str)
{
    ofstream out(path, ios::binary);
    
    if (!out.is_open())
        throw logic_error("Error");

    out.write(str.c_str(), str.length());
    
    out.close();
}

vector<bool> Huffman::string_to_bits(const string& str)
{
    vector<bool> bits;
    
    for (int i = 0; i < str.size(); i++)
    {
        for (int i_bit = 0; i_bit < 8; i_bit++)
        {
            int bit = str[i] & (1 << (7 - i_bit));
            bits.push_back(bit);
        }
    }
    return bits;
}

string Huffman::bits_to_string(const vector<bool>& bits)
{
    string str;
    
    char currbyte = 0;
    int i_bit = 0;
    
    for (int i = 0; i < bits.size(); i++)
    {
        if (bits[i])
            currbyte |= 1 << (7 - i_bit);
        
        i_bit++;
        
        if (i_bit == 8 || i + 1 == bits.size())
        {
            str += currbyte;
            i_bit = 0;
            currbyte = 0;
        }
    }
    
    return str;
}

Huffman::Huffman(const string& filename)
{
    this->filename = filename;
}

Huffman::~Huffman()
{
    delete head;
    head = nullptr;
}

void Huffman::clear_vars()
{
    content = "";
    coded_content = "";
    v.clear();
    coded_bits.clear();
    fill(table, table+256, 0);
    
    delete head;
    head = nullptr;
}

void Huffman::code()
{
    code_tree();
    
    code_content();
    
    code_excess();
    
    coded_content =  bits_to_string(coded_bits);
}

void Huffman::compress()
{
    clear_vars();
    
    read_all(filename + ".txt", content);
    
    Timer::start();
    
    code();
    
    Timer::stop();
    
    write_all(filename + ext_coded, coded_content);
}

void Huffman::decode()
{
    coded_bits = string_to_bits(coded_content);
    
    decode_excess();

    decode_tree();

    decode_content();
}

void Huffman::decompress()
{
    clear_vars();
    
    read_all(filename + ext_coded, coded_content);
    
    Timer::start();
    
    decode();
    
    Timer::stop();
    
    write_all(filename+ext_decoded, content);
}

void Huffman::make_freq()
{
    int freq[256] = { 0 };
    
    for (int i = 0; i < content.size(); i++)
        freq[(unsigned char)content[i]]++;
    
    for(int i = 0; i < 256; i++)
    {
        if (freq[i])
            v.push_back(new Node(freq[i], i));
    }
}

void Huffman::make_tree()
{
    while (v.size() > 1)
    {
        sort(v.begin(), v.end(), Node::greater);
        Node* n1 = v.back();
        v.pop_back();
        Node* n2 = v.back();
        v.pop_back();
        Node* n = new Node(n1->key + n2->key, -1);
        n->left = n2;
        n->right = n1;
        v.push_back(n);
    }

    head = v.size() ? v[0] : nullptr;
}

void Huffman::make_table(const string& bits, Node* n)
{
    if (!n->left && !n->left)
    {
        coded_bits.push_back(true);
        
        vector<bool> b = string_to_bits(string(1,n->value));
        coded_bits.insert(coded_bits.end(), b.begin(), b.end());
        
        table[n->value] = bits;
        
        if (head == n)
            table[n->value] = "0";
        
        return;
    }
    
    make_table(bits + "0", n->left);
    make_table(bits + "1", n->right);
    coded_bits.push_back(false);
}

void Huffman::code_tree()
{
    make_freq();
    make_tree();
    
    if (head)
    {
        make_table("", head);
        coded_bits.push_back(false);
    }
}

void Huffman::decode_tree()
{
    for (; pos < coded_bits.size(); pos++)
    {
        if(coded_bits[pos])
        {
            vector<bool> b(&coded_bits[pos + 1], &coded_bits[pos + 1 + 8]);
            v.push_back(new Node(-1, bits_to_string(b)[0]));
            
            pos += 8;
            continue;
        }
        
        if (v.size() == 1)
        {
            pos++;
            break;
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
    
    head = v.size() ? v[0] : nullptr;
}

void Huffman::code_content()
{
    for (int i = 0; i < content.size(); i++)
    {
        string bits = table[(unsigned char)content[i]];
        for (int j = 0; j < bits.size(); j++)
            coded_bits.push_back(bits[j] == '1');
    }
}

void Huffman::decode_content()
{
    Node* n = head;
    
    for (; pos < coded_bits.size(); pos++)
    {
        if(n->left && n->right)
        {
            n = coded_bits[pos] ? n->right : n->left;
        }
    
        if (!n->left && !n->left)
        {
            content += string(1,n->value);
            n = head;
        }
    }
}

void Huffman::code_excess()
{
    char coded_excess = (8 - coded_bits.size() % 8) % 8;
    
    vector<bool> b(coded_excess);
    coded_bits.insert(coded_bits.begin(), b.begin(), b.end());
}

void Huffman::decode_excess()
{
    for (; pos < coded_bits.size(); pos++)
    {
        if(coded_bits[pos])
            break;
    }
}

void Huffman::delete_files()
{
    remove((filename+ext_coded).c_str());
    remove((filename+ext_decoded).c_str());
}
