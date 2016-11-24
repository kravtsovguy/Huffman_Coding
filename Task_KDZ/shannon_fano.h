//
//  shannon_fano.hpp
//  Task_9
//
//  Created by Matvey Kravtsov on 17.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#ifndef shannon_fano_h
#define shannon_fano_h

#include "huffman.h"

class Shannon_Fano : public Huffman
{
    
public:
    
    static void delete_all(string filename);
    
    static void compress(string filename);
    
    static void decompress(string filename);
    
    Shannon_Fano(string filename) : Huffman(filename)
    {
        ext_coded = ".shan";
        
        ext_decoded = "-unz-s.txt";
    }
    
private:
    Node* make_tree(int l, int r);
    
protected:
    void make_tree();
    
};

#endif /* shannon_fano_h */
