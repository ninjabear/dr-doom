#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

void thread_bomb(); 
void blocked_thread(std::condition_variable&, std::mutex&);

#endif