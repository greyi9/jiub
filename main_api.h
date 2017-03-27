#ifndef MAIN_API_H
#define MAIN_API_H


#include "big_library.h"
#include "debug.h"

using namespace big_library;

class main_api 
{
public:
    main_api();
    ~main_api();
    int add_data(unsigned long new_input);
    unsigned long get_data(int option); //replace with more efficient option...
private:
    input_thread_factory * itf;
    output_handler * out;
};



#endif
