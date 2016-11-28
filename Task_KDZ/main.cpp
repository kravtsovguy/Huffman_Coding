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

int main(int argc, const char * argv[])
{
    Tester().test();

    return 0;
}
