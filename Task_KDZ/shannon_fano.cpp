//
//  shannon_fano.cpp
//  Task_9
//
//  Created by Matvey Kravtsov on 17.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#include "shannon_fano.h"


void Shannon_Fano::decompress(string inputFileName, string outputFileName)
{
    Shannon_Fano(inputFileName).save_decoded(outputFileName);
}


void Shannon_Fano::compress(string inputFileName, string outputFileName)
{
    Shannon_Fano(inputFileName).save_coded(outputFileName);
}

Shannon_Fano::Node* Shannon_Fano::make_tree(int l, int r)
{
    if(l == r)
        return nullptr;
    
    if (l + 1 == r)
        return v[l];
    
    Node* n = new Node(-1,-1);
    
    int freq = 0;
    for (int i=l; i<r; i++)
        freq += v[i]->key;
    
    int freq_current = 0;
    for (int i=l; i<=r; i++)
    {
        if (freq_current * 2 >= freq)
        {
            n->left = make_tree(l, i);
            n->right = make_tree(i, r);
            break;
        }
        if (i<r)
            freq_current += v[i]->key;
    }
    return n;
}

void Shannon_Fano::make_tree()
{
    head = make_tree(0, (int)v.size());
}