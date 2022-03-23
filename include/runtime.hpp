#pragma once
#include <thread>
#include <queue>
#include "processor.hpp"
#include <iostream>
using namespace std::chrono_literals;
struct Runtime
{
    Runtime()
    {
        auto maxProcsStr = std::getenv("MAXPROCS");
        if (maxProcsStr != 0)
        {
            maxProcs = atoi(maxProcsStr);
        }
    }
    void PushTask(Routine *r)
    {
        std::lock_guard<std::mutex> lk(mtx);
        tasks.push(r);
        for(auto p:procs){
            p->Notify();
        }
    }
    void Run()
    {
        while (true)
        {
            std::cout << "Iterate runtime" << std::endl;
            if (!tasks.empty() && procs.size() < maxProcs)
            {
                std::lock_guard<std::mutex> lk(mtx);
                std::cout << "Creating processor" << std::endl;
                auto proc = std::make_shared<Processor>(this);
                procs.push_back(proc);
                std::thread t([proc]()
                              { proc->Run(); });
                t.detach();
                std::this_thread::sleep_for(1s);
            }
            else
            {
                std::unique_lock<std::mutex> lk(mtx);
                cnd.wait(lk, [this]()
                         { return !tasks.empty(); });
            }
            //watch proportion between tasks and processors
            // + kill or create processors
        }
    }
    Routine *GetTask();

private:
    std::queue<Routine *> tasks;
    std::condition_variable cnd;
    std::mutex mtx;
    int maxProcs = 4;
    std::vector<std::shared_ptr<Processor>> procs;
};