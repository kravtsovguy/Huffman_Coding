//
//  timer.hpp
//  Task_KDZ
//
//  Created by Matvey Kravtsov on 22.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#ifndef timer_h
#define timer_h

typedef unsigned long long ull;


class Timer
{
    
public:
    
    static void start();
    static void stop();
    static ull get_last_ticks();
    static void print_last_ticks();
    
private:
    
    static ull rdtsc();
    
    static ull ticks;
    static ull ticks_temp;
};

#endif /* timer_h */
