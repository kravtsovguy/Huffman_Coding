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

string Random_Text::generate_text(string symbols, int size)
{
    string res = "";
    
    srand(unsigned(time(0)));
    
    char additional[symbols.size()];
    
    for (int i = 0; i < symbols.size(); i++)
    {
        //cout << i << " " << symbols.size() << " ||" << symbols[i] << endl;
        additional[i] = '\0';
        if (symbols[i] < 0)
        {
            //cout << symbols[i] << symbols[i+1] << endl;
            additional[i] = symbols[i + 1];
            symbols.erase(i + 1, 1);
            
        }
    }

    while (res.size() < size)
    {
        int index = rand() % symbols.size();
        char ch = symbols[index];
        char ch_a = additional[index];
        res += ch;
        if (ch_a != '\0')
            res += ch_a;
        //cout << res.size() << endl;
    }
    
    return res;
}

string Random_Text::get_chars_type1()
{
    string ch_set;
    
    for (char i='A'; i <= 'Z'; i++)
        ch_set += i;
    
    for (char i='a'; i <= 'z'; i++)
        ch_set += i;
    
    ch_set += ' ';
    
    return ch_set;
}

string Random_Text::get_chars_type2()
{
    string ch_set = get_chars_type1();
    
    string alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    
    ch_set += alphabet;
    
    return ch_set;
}

string Random_Text::get_chars_type3()
{
    string ch_set = get_chars_type2();
    
    string ch_additional = "+-*/=.,;:?!%@#$&~()[]{}<>\"";
    
    ch_set += ch_additional;
    
    return ch_set;
}

string Random_Text::generate_text_type1(int size)
{
    return generate_text(get_chars_type1(), size);
}

string Random_Text::generate_text_type2(int size)
{
    return generate_text(get_chars_type2(), size);
}

string Random_Text::generate_text_type3(int size)
{
    return generate_text(get_chars_type3(), size);
}

string Random_Text::get_chars(int type)
{
    string ch_set;
    if (type == 1)
        ch_set = get_chars_type1();
    
    if (type == 2)
        ch_set = get_chars_type2();
    
    if (type == 3)
        ch_set = get_chars_type3();
    
    return ch_set;
}

string Random_Text::generate_text(int type, int size)
{
    return generate_text(get_chars(type), size);
}

void Random_Text::save_to_file(string str, string filename)
{
    ofstream out(filename);
    
    out << str;
    
    out.close();
    
    cout << "saved!" << endl;
}

void Random_Text::generate_and_save(int type, int size, string filename)
{
    Random_Text* rt = new Random_Text();
    
    rt->save_to_file(rt->generate_text(type, size), filename);
}
