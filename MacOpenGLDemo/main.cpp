#include <iostream>
#include <GLFW/glfw3.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    if (!glfwInit()) {
        std::cout << "glfw init failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    return 0;
}
