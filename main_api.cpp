#include "main_api.h"



main_api::main_api()
{
    debug_write("+main_api");
    itf = new input_thread_factory();
    out = new output_handler();
}

main_api::~main_api()
{   
    delete itf;
    delete out;
    debug_write("~main_api");
}


int main_api::add_data(unsigned long new_input)
{
     itf->new_input(new_input);
}

unsigned long main_api::get_data(int option)
{
    //debug method only
    return out->test_output();
    
}
