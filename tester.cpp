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
    int size = sizeof(sizes);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 1; j <=3; j++)
        {
            long arr[2][2] = {0};
            
            int times_to_generate = 3;
            for (int k = 0; k < times_to_generate; k++)
            {
                cout << i << " " << j << " " << k << endl;
                Random_Text::generate_and_save(j, sizes[i], text_temp + ".txt");

                i_size = i;
                i_type = j;
                
                for (huff = 1; huff >= 0; huff-- )
                    for (compr = 1; compr >= 0; compr--)
                        arr[huff][compr] += testAlgo();
                
            }
            
            for (huff = 1; huff >= 0; huff-- )
            {
                for (compr = 1; compr >= 0; compr--)
                {
                    ticks = arr[huff][compr]/times_to_generate;
                    save_info_1();
                    save_info_2();
                    save_info_3();
                }
            }
        }
    }
    
    save_all_csv();
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
        res << "bytes / type" << "," << 1 << "," << 2 << "," << 3;
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
        res << "bytes / algo" << "," << "Huffman" << "," << "Shannon";
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
    
    if (i_size != 4)
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

long Tester::testAlgo()
{
    long ticks = 0;
    int times = 1;
    for (int i = 0; i < times; i++)
    {
        if (huff)
        {
            if (compr)
                Huffman::compress(text_temp, text_temp);
            else
                Huffman::decompress(text_temp, text_temp);
        }else
        {
            if (compr)
                Shannon_Fano::compress(text_temp, text_temp);
            else
                Shannon_Fano::decompress(text_temp, text_temp);
        }
        
        ticks += Timer::get_last_ticks();
    }
    ticks /= times;
    
    return ticks;
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
    
    csv_info = "";
    
}
