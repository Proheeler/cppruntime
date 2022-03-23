#pragma once
#include <thread>
#include <queue>
#include "routine.hpp"
struct Runtime;
struct Processor
{
    explicit Processor(Runtime *r) : runtime(r) {}
    void Run();
    void Terminate()
    {
        terminate = true;
    }
    void Notify(){
        cnd.notify_one();
    }

private:
    std::queue<Routine *> tasks;
    std::condition_variable cnd;
    std::mutex mtx;
    Runtime *runtime = nullptr;
    bool terminate = false;
};