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

    string s = "/Users/matvey/Documents/Projects/Xcode/Task_KDZ/Tests/test";
    Huffman::compress(s, s);
    
    cout << endl;
    
    Huffman::decompress(s, s);
    
    cout << endl;
    
    Shannon_Fano::compress(s, s);
    
    cout << endl;
    
    Shannon_Fano::decompress(s, s);
    
    cout << endl;
     
    return 0;
}
