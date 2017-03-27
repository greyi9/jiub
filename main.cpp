/*
 *
 *  DON'T DO ANYTHING IN HERE THAT PYTHON, ETC COULDN'T DO
 *
 *
*/

#include "main.h"

void cycle(main_api*& api)       
{
    int i = 10000;
    while(i-- > 0)
    {
        api->add_data(api->get_data(0));
    }
    debug_write("completed 10000 cycles");
}


int main(int argc, char** argv) {
    main_api * api = new main_api();
    std::string temp_input = "initialize";
    while(true) 
    {
        getline(std::cin, temp_input);
        if (temp_input == "q") break;
        if (temp_input == "t") 
        {
            debug_write("sending 100 inputs...");
            int i = 0;
            while(i++ < 10)
            {
                int j = 0;
                while (j++ < 10)
                {
                    api->add_data((i-1)*10 + j);
                }
            } 
            continue;
        }
        if (temp_input == "c")
        {
            debug_write("starting feedback cycle...");
            int i = 100;
            unsigned long j = 0;
            while(i-- > 0)
            {
                j = api->get_data(0);
                api->add_data(j);
            }
            debug_write("completed 100 cycles");
            continue;
        }

        if (temp_input == "o") 
        {
            debug_write(std::to_string(api->get_data(0)));
            continue;
        }
        if (temp_input == "?")
        {
            debug_write("Key       Action");
            debug_write("q         quit");
            debug_write("t         send 1000 inputs");
            debug_write("c         cycle I/O 1000 times");
            debug_write("o         prints test output");
        }
        try
        {
            api->add_data((stoul(temp_input)));
        }
        catch(...)
        {
            debug_write("?         prints usage guide");
        }        
    }
    delete api;
}

