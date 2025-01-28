#include <iostream>

extern int main() {
    std::cout << "Plugin initialized" << std::endl;
    return 0;
}

extern void update() {
    std::cout << "Plugin updated" << std::endl;
}