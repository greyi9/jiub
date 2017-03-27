#ifndef BIG_LIBRARY_H
#define BIG_LIBRARY_H

#include <atomic>
#include <thread>
#include <string>
#include <deque>
#include "debug.h"


/******* to-do notes *******
*
*   -> replace data storage classes with structs...
*
*   -> move classes into separate declaration files...
*
*   -> optimize types (const, private, static, etc)...
*
*   -> add input method for array of inputs... 
*
*   -> add input method for memory retrieval...
*
*   -> add file I/O...
*
*   -> add temporary input weight system...
*
*   -> complete temorary model...
*
*   -> remove excessive write collision checks...
*
*   -> move globals into main_api, pass by ref 
*
***************************/

//temporary namespace prior to moving these into individual files
namespace big_library{


class x_atomic
{
public:
    x_atomic();
    x_atomic(std::string debug_id);
    ~x_atomic();
    std::atomic<int> x;
    std::string debug_id = "default";
};



/**** MODEL ****/

const int CURRENT_MOMENT_MAX_SIZE = 100;
const int CURRENT_MOMENT_MAX_INDEX = 4;

class moment
{
public:
    moment();
    ~moment();
    std::atomic<int> index_index;
    std::atomic<int> input_index[CURRENT_MOMENT_MAX_INDEX] = {};
    unsigned long inputs[CURRENT_MOMENT_MAX_INDEX][CURRENT_MOMENT_MAX_SIZE] = {};
};


class fragment
{
public:
    fragment(std::deque<unsigned long> init_inputs, int init_weight);
    ~fragment();
    std::atomic<int> weight;
    std::deque<unsigned long> inputs;
};



class anticipator
{
public:
    anticipator();
    ~anticipator();
    //how many of these?
    //creates patterns from unexpected high priority events
    //reinforces patterns that expected high priority events
    //requests actions with variable confidence
    //lowest average confidence instances are deleted, highest produce more
};


class pattern
{
public:
    pattern();
    ~pattern();
    //from:
    //    -> current moment
    //    -> current fragments
    //    -> current patterns
    //    -> current actions
    //provide:
    //    -> rules to explain event
};



/**** I/O ****/


class output_handler
{
public:
    output_handler();
    ~output_handler();
    unsigned long test_output();
};

class input_thread_factory
{
public:
    input_thread_factory();
    ~input_thread_factory();
    int thread_capacity;
    std::deque<unsigned long> input_queue;
    int process_queue();
    int new_input(unsigned long new_input);
    int new_thread(unsigned long new_input);
    int include_input(unsigned long input);
};


}
#endif
