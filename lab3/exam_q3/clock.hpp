#ifndef clock_hpp
#define clock_hpp

#include <chrono>

/* A class for measuring the time between two execution points */
class Clock
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_point;
public:
    // Reset the clock to zero and start measuring
    void start()
    {
        m_start_point=std::chrono::high_resolution_clock::now();
    }

    // Stop the clock and return elapsed time in seconds
    double stop()
    {
        return std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-m_start_point).count();
    }
};

#endif
