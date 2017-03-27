#include "big_library.h"

using namespace big_library;

const int MAX_LONG = std::numeric_limits<unsigned long>::max(); 

x_atomic * num_active_threads = new x_atomic("num_active_threads");
x_atomic * num_threads_created = new x_atomic("num_threads_created");
x_atomic * num_index_collisions = new x_atomic("num_index_collisions");
moment * current_moment = new moment();

std::deque<fragment*> fragments;


x_atomic::x_atomic(){x = 0;}
x_atomic::x_atomic(std::string debug_id)
{
    x = 0;
    this->debug_id = debug_id;
    debug_write("+x: " + debug_id);
}
x_atomic::~x_atomic()
{
    debug_write("~x: " + debug_id + " = " + std::to_string(x));
}

//moves these to api, delete in api destructor
void delete_globals()
{
    delete num_active_threads;
    delete num_threads_created;
    delete num_index_collisions;
    delete current_moment;
    for( fragment* f : fragments){delete f;}
}



/**** MODEL ****/



moment::moment()
{
    debug_write("+moment");
    this->index_index = 0; 
//    this->input_index[CURRENT_MOMENT_MAX_INDEX] = {};
//    this->inputs[CURRENT_MOMENT_MAX_INDEX][CURRENT_MOMENT_MAX_SIZE] = {};    
}
moment::~moment() 
{
    debug_write("~moment");
}

fragment::fragment(std::deque<unsigned long> init_inputs, int init_weight)
{
    this->weight = init_weight;
    this->inputs = init_inputs;
    debug_write("+frag: " + std::to_string(this->weight));
    for(unsigned long i:this->inputs)
    {
    //    debug_write("     : " + std::to_string(i));
    }
}
fragment::~fragment()
{
    debug_write("~frag: " + std::to_string(this->weight));
    for(unsigned long i:this->inputs)
    {
    //    debug_write("     : " + std::to_string(i));
    }
}


anticipator::anticipator()
{
    debug_write("+ant");
}
anticipator::~anticipator()
{
    debug_write("~ant");
}


pattern::pattern() 
{
    debug_write("+pattern");
}
pattern::~pattern()
{
    debug_write("~pattern");
}






/**** I/O ****/

output_handler::output_handler()
{
    debug_write("+out");
}
output_handler::~output_handler()
{
    debug_write("~out");
}
unsigned long output_handler::test_output()
{
    //temporary implementation
    return 123456789;
}



input_thread_factory::input_thread_factory() 
{
    debug_write("+itf");
    num_active_threads->x = 0;
    //determine accurate capacity...
    thread_capacity = 8;
}

input_thread_factory::~input_thread_factory()
{
    while(num_active_threads->x > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    delete_globals();
    debug_write("~itf");
}



int input_thread_factory::new_input(unsigned long new_input)
{
    if (thread_capacity > num_active_threads->x && input_queue.empty()) 
    {
        return new_thread(new_input);    
    } else {
        input_queue.push_back(new_input);
    }
    if (thread_capacity == num_active_threads->x)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    if (!input_queue.empty()) 
    {
        unsigned long next_in_queue = input_queue[0];
        input_queue.pop_front();
        this->new_input(next_in_queue);
    }
    return 1;
}


int input_thread_factory::new_thread(unsigned long new_input) 
{
    (num_active_threads->x)++;
    (num_threads_created->x)++;
    std::thread new_t([this,new_input] {include_input(new_input);});
    new_t.detach();
    return 1;
}


int input_thread_factory::include_input(unsigned long input)
{
    int ciii = (int)current_moment->index_index;
    int cii = (int)(current_moment->input_index[ciii]++);
    if (cii+1 < CURRENT_MOMENT_MAX_SIZE) 
    {       
        current_moment->inputs[ciii][cii]=input;
        num_active_threads->x--;
        return 1;
    } else if(cii+1 == CURRENT_MOMENT_MAX_SIZE) { 
        debug_write("switching moment arrays");
        int new_index = (ciii+1 == CURRENT_MOMENT_MAX_INDEX) ? 0 : ciii+1;
        current_moment->index_index = new_index;
        std::deque<unsigned long> copy_of_moment;
        for(int i = 0; i < CURRENT_MOMENT_MAX_SIZE-1; i++)
        {
            //putting everything into the fragments to start
            copy_of_moment.push_back((unsigned long)current_moment->inputs[ciii][i]);
            //reset inputs for collision check + etc... maybe not needed
            current_moment->inputs[ciii][i]=0;
        } 
        fragment * next_frag = new fragment(copy_of_moment,0);
        fragments.push_back(next_frag);
        current_moment->input_index[ciii] = 0;
    } else {
        num_index_collisions->x++;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return this->include_input(input);
}

