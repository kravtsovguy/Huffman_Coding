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
using namespace std;

class Tester
{
public:
    static void test_all();
    
    void test();

    
private:
    void save_info_1();
    void save_info_2();
    void save_info_3();
    void save_csv(string name);
    void save_all_csv();
    long testAlgo();
};

#endif /* tester_h */
