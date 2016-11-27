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

void Tester::test()
{
    int size = sizeof(sizes)/sizeof(*sizes);
    //size = 2;
    for (i_size = 0; i_size < size; i_size++)
    {
        for (i_type = 1; i_type <= 3; i_type++)
        {
            long arr[2][2] = {0};
            
            int times = 3;
            
            for (int i_times = 0; i_times < times; i_times++)
            {
                cout << i_size << " " << i_type << " " << i_times + 1 << endl;

                stringstream name;
                name << "text_";
                name << sizes[i_size]/1000 << "kB" << "_" << "type" << i_type << "_" << i_times + 1;
                text_name = name.str();
                
                Random_Text::generate_and_save(i_type, sizes[i_size], text_path + text_name);
                
                for (huff = 1; huff >= 0; huff-- )
                    for (compr = 1; compr >= 0; compr--)
                        arr[huff][compr] += testAlgo();
                
                Huffman(text_path + text_name).delete_files();
                Shannon_Fano(text_path + text_name).delete_files();
            }
            
            for (huff = 1; huff >= 0; huff-- )
            {
                for (compr = 1; compr >= 0; compr--)
                {
                    ticks = arr[huff][compr] / (times * 1000000);
                    save_info(1);
                    save_info(2);
                    save_info(3);
                }
            }
        }
    }
    
    save_all_csv();
    
    cout << "done!" << endl;
}

long Tester::testAlgo()
{
    long ticks = 0;
    int times = 5;
    for (int i = 0; i < times; i++)
    {
        if (huff)
        {
            Huffman huff(text_path + text_name);
            if (compr)
                huff.compress();
            else
                huff.decompress();
        }else
        {
            Shannon_Fano shan(text_path + text_name);
            if (compr)
                shan.compress();
            else
                shan.decompress();
        }
        
        ticks += Timer::get_last_ticks();
    }
    ticks /= times;
    
    return ticks;
}

void Tester::save_info(int type)
{
    
    stringstream name;
    stringstream res;
    
    if (type == 1)
    {
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
            res << "\n" << sizes[i_size] / 1000;
        }
    }
    
    if (type == 2)
    {
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
            res << "\n" << sizes[i_size] / 1000;
        }
    }
    
    if (type == 3)
    {
        if (i_size != 7)
            return;
        
        name << "/3/";
        name << (compr ? "compression_" : "decompression_");
        name << sizes[i_size] / 1000 << "kB" ;
        
        if (i_type == 1 && huff)
        {
            res << "type / algo" << "," << "Huffman" << "," << "Shannon";
        }
        if (huff)
        {
            res << "\n" << i_type;
        }
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
