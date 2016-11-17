//
//  main.cpp
//  Task_9
//
//  Created by Matvey Kravtsov on 16.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#include <iostream>
#include "huffman.h"
#include "shannon_fano.h"
using namespace std;

int main(int argc, const char * argv[]) {

    string s = "/Users/matvey/Documents/Projects/Xcode/Task_KDZ/";
    Huffman::compress(s+"input", s+"output");
    
    Huffman::decompress(s+"output", s+"input");
    
    Shannon_Fano::compress(s+"input", s+"output");
    
    Shannon_Fano::decompress(s+"output", s+"input");
    return 0;
}
