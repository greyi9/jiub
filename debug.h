#ifndef DEBUG_TMP_H
#define DEBUG_TMP_H


#include <iostream>
#include <string>
#include <deque>
#include <mutex>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <limits>

//temporary debug cout code
void debug_write(std::string to_write);

//temporary sleep code
void debug_sleep(int how_long);


#endif
