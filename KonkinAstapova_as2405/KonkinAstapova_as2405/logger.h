#pragma once
#include <iostream>
#include <string>
#include <fstream>

static bool REPLAY_MODE = false;

#define INPUT_LINE(in, str) \
    if (!REPLAY_MODE) { \
        getline(in >> std::ws, str); \
        std::cerr << str << std::endl; \
    } else { \
        getline(in >> std::ws, str); \
    }

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((std::cin >> x).fail()      
        || std::cin.peek() != '\n'   
        || x < min || x > max)        
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        if (!REPLAY_MODE) {  
            std::cout << "Type number (" << min << "-" << max << "): ";
        }
    }
    std::cin.ignore(10000, '\n');  
    if (!REPLAY_MODE) {  
        std::cerr << x << std::endl;
    }
    return x;
}

inline bool GetCorrectBool() {
    int x = GetCorrectNumber<int>(0, 1);
    return static_cast<bool>(x);
}

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
    redirect_output_wrapper(std::ostream& src)
        : old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }

    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};