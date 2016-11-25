//
//  tester.hpp
//  Task_KDZ
//
//  Created by Matvey Kravtsov on 22.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#ifndef tester_h
#define tester_h

#include <string>
#include <map>
using namespace std;

class Tester
{
public:
    
    void test();
    
private:
    
    void save_info(int type);
    void save_csv(string name);
    void save_all_csv();
    long testAlgo();
    
    string text_path = "Tester/Temp/text";
    string csv_path = "Tester/CSV/";
    int sizes[8] = {20000, 40000, 60000, 80000, 100000, 1000000, 2000000, 3000000};
    map<string,string> csv;
    int huff, compr;
    int i_size, i_type;
    long ticks;

};

#endif /* tester_h */
