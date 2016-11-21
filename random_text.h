//
//  random_text.hpp
//  Task_KDZ
//
//  Created by Matvey Kravtsov on 21.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#ifndef random_text_h
#define random_text_h

#include <string>
#include <vector>
using namespace std;

class Random_Text
{
public:
    string generate_text(string symbols, int size);
    string generate_text_type1(int size);
    string generate_text_type2(int size);
    string generate_text_type3(int size);
    void save_to_file(string str, string filename);
    
private:
    string get_chars_type1();
    string get_chars_type2();
    string get_chars_type3();
};

#endif /* random_text_h */
