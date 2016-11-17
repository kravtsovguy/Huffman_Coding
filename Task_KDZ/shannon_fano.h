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
    
    static void compress(string inputFileName, string outputFileName);
    
    static void decompress(string inputFileName, string outputFileName);
    
    Shannon_Fano(string inputFileName) : Huffman(inputFileName)
    {
        ext = "shan";
    }
    
protected:
    Node* make_tree(int l, int r);
    void make_tree();
    
};

#endif /* shannon_fano_h */
