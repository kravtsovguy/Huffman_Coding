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
    
    Shannon_Fano(const string& filename) : Huffman(filename)
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
