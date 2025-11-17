#include "ExecutionTime.h"
#include <iostream>

ExecutionTime::ExecutionTime(const std::string& message) 
    : message(message) 
{
    start = std::chrono::steady_clock::now();  // Use steady_clock here too
}

ExecutionTime::~ExecutionTime()
{
    end = std::chrono::steady_clock::now();  // And here
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << message << ": " << duration.count() << " microseconds";
    std::cout << " (" << duration.count() / 1000.0 << " ms)" << std::endl;
}