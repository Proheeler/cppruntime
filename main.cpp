

#include <iostream>
#include <thread>
#include <queue>
#include <cstdlib>
#include "include/runtime.hpp"
#include "include/routine.hpp"

using namespace std::chrono_literals;


int main()
{
    Routine p([]()
              { std::cout << "Test" << std::endl; });
    Runtime r;
    std::thread t(&Runtime::Run, &r);

    for (;;)
    {
        r.PushTask(&p);
        std::this_thread::sleep_for(100ms);
    }
}