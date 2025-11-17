#ifndef EXECUTION_TIME_H
#define EXECUTION_TIME_H

#include <chrono>
#include <string>

class ExecutionTime {
private:
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::string message;

public:
    ExecutionTime(const std::string& message);
    ~ExecutionTime();
};

#endif // EXECUTION_TIME_H