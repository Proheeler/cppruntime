#include "../include/runtime.hpp"

   Routine *Runtime::GetTask()
    {
        Routine *ret = nullptr;
        size_t queueLen = 0;
        {
            std::lock_guard<std::mutex> lk(mtx);
            queueLen = tasks.size();
        }
        if (queueLen != 0)
        {
            std::lock_guard<std::mutex> lk(mtx);
            ret = tasks.front();
            tasks.pop();
        }
        return ret;
    }