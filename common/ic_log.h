#pragma once

#ifdef __cplusplus
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <functional>

#define COUT(V) std::cout << __LINE__ << " ----  " << V << std::endl;

extern bool isPrintLog;

static void setPrintLog(bool isPrint)
{
    isPrintLog = isPrint;
}

static int64_t IC_TIMESTAMP()
{
    return 1;
}

#define  IC_LOG_INFO(...) if(isPrintLog) {printf(__VA_ARGS__);printf("\n");}
#define  IC_LOG_WARNING(...) IC_LOG_INFO(__VA_ARGS__);
#define  IC_LOG_DEBUG(...) IC_LOG_INFO(__VA_ARGS__);
#define  IC_LOG_ERROR(...) IC_LOG_INFO(__VA_ARGS__);

// template <typename T0, typename... T>
// void IC_LOG_INFO(T0 t0, T... t)
// {
//     std::cout << t0 << " ";
//     if constexpr (sizeof...(t) > 0)
//         IC_LOG_INFO(t...);
//     else
//         std::cout << std::endl;
// }

// template <typename T0, typename... T>
// void IC_LOG_WARNING(T0 t0, T... t)
// {
//     IC_LOG_INFO(t0, t...);
// }

// template <typename T0, typename... T>
// void IC_LOG_DEBUG(T0 t0, T... t)
// {
//     IC_LOG_INFO(t0, t...);
// }

// template <typename T0, typename... T>
// void IC_LOG_ERROR(T0 t0, T... t)
// {
//     IC_LOG_INFO(t0, t...);
// }

template <typename T>
void COUTI(T c)
{
    std::cout << __LINE__ << " ----  ";
    for (auto i : c)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

template <typename T, typename U>
void COUTMAP(std::map<T, U> c)
{
    std::cout << __LINE__ << " ----  ";
    for (auto i : c)
    {
        std::cout << i.first << " ";
    }
    std::cout << "\n";
}

static void printHex(const uint8_t *data, uint8_t len)
{
    char buff[512] = {0};
    for (int i = 0; i < len; i++)
    {
        sprintf(buff + i*3, "%02x ", data[i]);
    }
    printf("%s\n", buff);
}
// vector<string> v = split(s, ",*"); //可按多个字符来分隔;
#else
    #include <stddef.h>
#endif