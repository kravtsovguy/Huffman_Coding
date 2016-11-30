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
using namespace std;

class Random_Text
{
    
public:
    
    static void generate_and_save(int type, int size, const string& filename);
    
    string get_chars(int type);
    void generate_text(int type, int size);
    void generate_text(string symbols, int size);
    void save_to_file(const string& filename);
    
    string text = "";
};

#endif /* random_text_h */
