//
//  timer.cpp
//  Task_KDZ
//
//  Created by Matvey Kravtsov on 22.11.16.
//  Copyright © 2016 Matvey Kravtsov. All rights reserved.
//

#include "timer.h"
#include <iostream>

ull Timer::ticks = 0;
ull Timer::ticks_temp = 0;

/*
 long long rdtsc()
 {
 long long x;
 asm volatile("rdtsc\n"
 "shl $32, %%rdx\n"
 "or %%rdx, %%rax" : "=a" (x));
 return x;
 }
 */

inline ull Timer::rdtsc()
{
    unsigned int lo, hi;
    asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );
    return ((ull)hi << 32) | lo;
}

void Timer::start()
{
    ticks_temp = rdtsc();
}

void Timer::stop()
{
    ticks = rdtsc() - ticks_temp;
    //print_last_ticks();
}

ull Timer::get_last_ticks()
{
    return ticks;
}

void Timer::print_last_ticks()
{
    std::cout <<"ticks: " << ticks << std::endl;
}
