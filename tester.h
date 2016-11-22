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
    static void test_all();
    void test();
    ~Tester()
    {
        delete [] sizes;
    }
    
private:
    void save_info_1();
    void save_info_2();
    void save_info_3();
    void save_csv(string name);
    void save_all_csv();
    long testAlgo();
    
    string text_temp = "/Users/matvey/Documents/Projects/Xcode/Task_KDZ/Tester/Temp/text";
    string csv_path = "/Users/matvey/Documents/Projects/Xcode/Task_KDZ/Tester/CSV/";
    int* sizes = new int[8]{20000, 40000, 60000, 80000, 100000, 1000000, 2000000, 3000000};
    string csv_info;
    map<string,string> csv;
    bool is_Huffman, is_compr;
    int i_size, i_type;
    long ticks;

};

#endif /* tester_h */
