//
//  random_text.cpp
//  Task_KDZ
//
//  Created by Matvey Kravtsov on 21.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#include "random_text.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void Random_Text::generate_text(string symbols, int size)
{
    char additional[symbols.size()];
    
    for (int i = 0; i < symbols.size(); i++)
    {
        additional[i] = '\0';
        if (symbols[i] < 0)
        {
            additional[i] = symbols[i + 1];
            symbols.erase(i + 1, 1);
            
        }
    }

    text = "";
    
    while (text.size() < size)
    {
        int index = rand() % symbols.size();
        char ch = symbols[index];
        char ch_a = additional[index];
        text += ch;
        if (ch_a != '\0')
            text += ch_a;
    }
}

string Random_Text::get_chars(int type)
{
    string ch_set;
    
    if (type >= 1)
    {
        for (char i='A'; i <= 'Z'; i++)
            ch_set += i;
        
        for (char i='a'; i <= 'z'; i++)
            ch_set += i;
        
        ch_set += ' ';
    }
    
    if (type >= 2)
    {
        string ch_alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        
        ch_set += ch_alphabet;
    }
    
    if (type >= 3)
    {
        string ch_additional = "+-*/=.,;:?!%@#$&~()[]{}<>\"";
        
        ch_set += ch_additional;
    }
    
    return ch_set;
}

void Random_Text::generate_text(int type, int size)
{
    generate_text(get_chars(type), size);
}

void Random_Text::save_to_file(const string& filename)
{
    ofstream out(filename + ".txt");
    out << text;
    out.close();
}

void Random_Text::generate_and_save(int type, int size, const string& filename)
{
    Random_Text rt;
    rt.generate_text(type, size);
    rt.save_to_file(filename);
}
