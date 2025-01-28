#ifndef POMEGRANATEENGINE_PLUGIN_H
#define POMEGRANATEENGINE_PLUGIN_H
#ifdef __APPLE__

#include <dlfcn.h>

#endif

#include <string>
#include <core/core.h>

class Plugin {
private:
    void* handle = nullptr;
public:
    Plugin(const std::string& path);

    ~Plugin();

    template<typename T, typename...Args>
    T call(const char* functionName, Args...args) {
        T (* function)(Args...) = (T (*)(Args...)) dlsym(handle, functionName);
        if (!function) {
            // Handle error
            Debug::Log::error("Failed to find function:", functionName);
            return T();
        }
        return function(args...);
    }
};


#endif //POMEGRANATEENGINE_PLUGIN_H
