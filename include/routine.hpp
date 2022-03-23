#pragma once
#include <thread>

using routineFunc = void (*)();
struct Routine
{
    explicit Routine(routineFunc f) : cmd(f)
    {
    }
    void Run()
    {
        cmd();
    }

private:
    routineFunc cmd;
    std::condition_variable cnd;
    std::mutex mtx;
};
