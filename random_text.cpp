//
//  random_text.cpp
//  Task_KDZ
//
//  Created by Matvey Kravtsov on 21.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#include "random_text.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
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
        //cout << symbols.size() << endl;
        additional[i] = ' ';
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
        if (ch_a != ' ')
            res += ch_a;
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
    
    string ch_additional = "+-*/=.,;:?!%@#$&~()[]{}<>„“";
    
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


void Random_Text::save_to_file(string str, string filename)
{
    
    //setlocale(LC_ALL,"");
    
    //wofstream out(filename);
    
    //wstring s(L"привет");
    
    //out.write((char*)&wstr[0], wstr.size());
    
        //system("pause");
    
    ofstream out(filename);
    
    out << str;
    
    out.close();
    
    cout << "saved!" << endl;
    /*
    std::ofstream file(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    file.exceptions(true);
    file << wstr;
    file.close();
    
    */
    /*setlocale(LC_ALL, "ru_RU.UTF-8");
    //std::locale::global( std::locale( "" ) );
    wofstream out(filename);
    out << s;
    out.close();
    */
}
