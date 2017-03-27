#include "debug.h"

/***************
*
*     temporary debug functions declared here
*
****************/


//temporary debug cout code
void debug_write(std::string to_write)
{
    std::cout << to_write << std::endl << std::flush;
}

//temporary sleep code
void debug_sleep(int how_long)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(how_long));
}


