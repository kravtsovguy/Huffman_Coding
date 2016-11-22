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
#include "random_text.h"
#include "timer.h"
#include "tester.h"
#include <unistd.h>

using namespace std;

int main(int argc, const char * argv[])
{
    Tester::test_all();
    /*Random_Text* rt = new Random_Text();
    string str = rt->generate_text_type2(1000);
    rt->save_to_file(str, "/Users/matvey/Documents/Projects/Xcode/Task_KDZ/rand.txt");

    string s = "/Users/matvey/Documents/Projects/Xcode/Task_KDZ/rand";

    Huffman::compress(s, s);
    cout << endl;
    
    Huffman::decompress(s, s);
    
    cout << endl;
    
    Shannon_Fano::compress(s, s);
    
    cout << endl;
    
    Shannon_Fano::decompress(s, s);
    
    cout << endl;
     */
    return 0;
}
