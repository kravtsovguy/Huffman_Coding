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


using namespace std;

void show_usage()
{
    cerr << "Usage: " << "\n"
    << "Options:\n"
    << "\t--huffman\t\t Huffman algorithm\n"
    << "\t--shannon\t\t Shannon-Fano algorithm\n"
    << "\t--decompress\t Decompress file\n"
    << "next argument is PATH to file\n"
    << "or:\n"
    << "\t--test\t\t Start testing (for testing you need some folders)\n"
    << endl;
}

int main(int argc, const char * argv[])
{
    srand((unsigned int)time(0));
    
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
