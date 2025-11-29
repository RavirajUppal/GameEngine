#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define API_EXPORT __declspec(dllexport)
#define API_IMPORT __declspec(dllimport)
#else
#define API_EXPORT __attribute__((visibility("default")))
#define API_IMPORT
#endif

// #ifdef REALENGINE_BUILD_DLL
// #define REALENGINE_API API_EXPORT
// #else
// #define REALENGINE_API API_IMPORT
// #endif

#ifdef REALENGINE_BUILD_DLL
#define REALENGINE_API 
#else
#define REALENGINE_API 
#endif

#ifndef NDEBUG
#define REALENGINE_ENABLE_ASSERTS
#endif

#ifdef REALENGINE_ENABLE_ASSERTS
#define REALENGINE_ASSERT(x, ...)                        \
    do                                                        \
    {                                                         \
        if (!(x))                                             \
        {                                                     \
            LOG_ERROR("Assertion Failed: " __VA_ARGS__); \
            DEBUG_BREAK;                                      \
        }                                                     \
    } while (0)
#else
#define REALENGINE_ASSERT(x, ...)
#endif

#if defined(_WIN32)
#define DEBUG_BREAK __debugbreak()
#elif defined(__APPLE__) || defined(__linux__)
#define DEBUG_BREAK __builtin_trap()
#else
#error "Unknown platform for DEBUG_BREAK"
#endif