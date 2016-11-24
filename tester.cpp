//
//  tester.cpp
//  Task_KDZ
//
//  Created by Matvey Kravtsov on 22.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#include "tester.h"
#include "huffman.h"
#include "shannon_fano.h"
#include "timer.h"
#include "random_text.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
void Tester::test_all()
{
    Tester* t = new Tester();
    
    t->test();
}

void Tester::test()
{
    int size = sizeof(sizes)/sizeof(*sizes);
    //size = 3;
    for (i_size = 0; i_size < size; i_size++)
    {
        for (i_type = 1; i_type <= 3; i_type++)
        {
            long arr[2][2] = {0};
            
            int times = 3;
            
            for (int i_times = 0; i_times < times; i_times++)
            {
                cout << i_size << " " << i_type << " " << i_times << endl;
                Random_Text::generate_and_save(i_type, sizes[i_size], text_path + ".txt");

                for (huff = 1; huff >= 0; huff-- )
                    for (compr = 1; compr >= 0; compr--)
                        arr[huff][compr] += testAlgo();
                
            }
            
            for (huff = 1; huff >= 0; huff-- )
            {
                for (compr = 1; compr >= 0; compr--)
                {
                    ticks = arr[huff][compr]/times;
                    ticks /= 1000000;
                    save_info_1();
                    save_info_2();
                    save_info_3();
                }
            }
        }
    }
    
    save_all_csv();
}

long Tester::testAlgo()
{
    long ticks = 0;
    int times = 5;
    for (int i = 0; i < times; i++)
    {
        if (huff)
        {
            if (compr)
                Huffman::compress(text_path);
            else
                Huffman::decompress(text_path);
        }else
        {
            if (compr)
                Shannon_Fano::compress(text_path);
            else
                Shannon_Fano::decompress(text_path);
        }
        
        ticks += Timer::get_last_ticks();
    }
    ticks /= times;
    
    return ticks;
}

void Tester::save_info_1()
{
    
    stringstream name;
    stringstream res;
    
    name << "/1/";
    name << (huff ? "Huffman_" : "Shannon_");
    name << (compr ? "compression_" : "decompression_");
    name << (i_size < 5 ? "small" : "big");
    if ((i_size == 0 || i_size == 5) && i_type == 1)
    {
        res << "kB / type" << "," << "набор 1" << "," << "набор 2" << "," << "набор 3";
    }
    if (i_type == 1)
    {
        res << "\n" << sizes[i_size]/1000;
    }
    res << "," << ticks;
    csv[name.str()] += res.str();
}

void Tester::save_info_2()
{
    stringstream name;
    stringstream res;
    
    name << "/2/";
    name << "type" << i_type << "_";
    name << (compr ? "compression_" : "decompression_");
    name << (i_size < 5 ? "small" : "big");
    if ((i_size == 0 || i_size == 5) && huff)
    {
        res << "kB / algo" << "," << "Huffman" << "," << "Shannon";
    }
    if (huff)
    {
        res << "\n" << sizes[i_size]/1000;
    }
    res << "," << ticks;
    csv[name.str()] += res.str();
}

void Tester::save_info_3()
{
    
    stringstream name;
    stringstream res;
    
    if (i_size != 7)
        return;
    
    name << "/3/";
    name << (compr ? "compression_" : "decompression_");
    name << sizes[i_size]/1000 << "kB" ;
    
    
    if (i_type == 1 && huff)
    {
        res << "type / algo" << "," << "Huffman" << "," << "Shannon";
    }
    if (huff)
    {
        res << "\n" << i_type;
    }
    res << "," << ticks;
    csv[name.str()] += res.str();
}

void Tester::save_all_csv()
{
    while (csv.size() > 0)
    {
        save_csv(csv.begin()->first);
        csv.erase(csv.begin());
    }
}

void Tester::save_csv(string name)
{
    ofstream out(csv_path + name + ".csv");
    
    out << csv[name];
    
    out.close();
}
