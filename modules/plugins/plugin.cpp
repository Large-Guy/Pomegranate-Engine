#include "plugin.h"

Plugin::Plugin(const std::string& path) {
    handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        // Handle error
        Debug::Log::error("Failed to load plugin");
    }

    Debug::Log::pass("Plugin loaded");

    //Call the main function
    void (* main)() = (void (*)()) dlsym(handle, "main");
    if (!main) {
        // Handle error
        Debug::Log::error("Failed to find main function");
    }

    main();
}

Plugin::~Plugin() {
    dlclose(handle);
}