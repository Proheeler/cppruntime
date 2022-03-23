#include "../include/processor.hpp"
#include "../include/runtime.hpp"
#include <iostream>
void Processor::Run()
{
    while (true)
    {
        if (terminate)
        {
            return;
        }
        size_t queueLen = 0;
        {
            std::lock_guard<std::mutex> lk(mtx);
            queueLen = tasks.size();
            if (queueLen == 0 && runtime)
            {
                std::cout << "Get task from runtime" << std::endl;
                Routine *r = runtime->GetTask();
                if (r)
                    tasks.push(r);
            }
        }
        if (queueLen != 0)
        {
            std::cout << "Run task" << std::endl;
            Routine *task = tasks.front();
            task->Run();
            tasks.pop();
        }
        else
        {
            // std::cout << "Queue is empty" << std::endl;
            std::unique_lock<std::mutex> lk(mtx);
            cnd.wait(lk);
        }
    }
}