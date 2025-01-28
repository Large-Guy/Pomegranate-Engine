#include <plugins/plugin.h>

void helloWorld() {
    std::cout << "Hello, World! From test_plugin" << std::endl;
}

int main() {
    Plugin plugin("test_plugin/cmake-build-debug/bin/libTestPlugin.dylib");

    plugin.call<void>("update");

    return 0;
}