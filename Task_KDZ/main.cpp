//
//  main.cpp
//  Task_9
//
//  Created by Matvey Kravtsov on 16.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

// КДЗ-1 по дисциплине Алгоритмы и структуры данных
// Кравцов Матвей Евгеньевич, БПИ152, 29.11.2016
// Xcode 8.1, компилятор Clang, состав проекта:
//------------------------------------
// huffman.cpp      | huffman.h
// shannon_fano.cpp | shannon_fano.h
// timer.cpp        | timer.h
// random_text.cpp  | random_text.h
// tester.cpp       | tester.h
//------------------------------------
// Сделано всё, что написано в файле задания

#include <iostream>
#include "huffman.h"
#include "shannon_fano.h"
#include "random_text.h"
#include "timer.h"
#include "tester.h"
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void show_path_info()
{
    cerr << "please, use path without an extention\n"
    << "for native text file the extention is '.txt'\n"
    << "for compressed file the extention is '.huff' or '.shan'\n"
    << "decompressed file ends at '-unz-h.txt' or '-unz-s.txt'\n"
    << endl;
}

void show_usage()
{
    cerr << "Usage: " << "\n"
    << "Options:\n"
    << "\t--huffman\t\t Huffman algorithm\n"
    << "\t--shannon\t\t Shannon-Fano algorithm\n"
    << "\t--decompress\t Decompress file\n"
    << "next argument is a PATH to file WITHOUT AN EXTENTION\n"
    << "or the option:\n"
    << "\t--test\t\t Start testing (for testing you need some folders)\n"
    << "-------------------\n"
    << "remark:"
    << endl;
    show_path_info();
}

int main(int argc, const char * argv[])
{
    srand((unsigned int)time(0));
    
    /* Usage of code
     
    string path = "text";
    Random_Text::generate_and_save(1, 230, path);
    Huffman(path).compress();
    Huffman(path).decompress();
     
     */
    
    if (argc == 1)
    {
        show_usage();
        return 1;
    }
    if (argc == 2)
    {
        if(string(argv[1]) == "--test")
        {
            Tester().test();
        }
    }
    if (argc == 3)
    {
        if (string(argv[2]).find('.') != string::npos)
        {
            show_path_info();
            return 1;
        }
        if(string(argv[1]) == "--huffman")
        {
            Huffman(argv[2]).compress();
        }
        if(string(argv[1]) == "--shannon")
        {
            Shannon_Fano(argv[2]).compress();
        }
        if(string(argv[1]) == "--decompress")
        {
            Huffman(argv[2]).decompress();
        }
        cout << "done!" << endl;
    }
    
    return 0;
}
