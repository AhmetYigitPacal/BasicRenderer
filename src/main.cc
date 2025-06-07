#include "Object.h"
#include "Mesh.h"
#include "Material.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "Not enough arguments!" << std::endl;
        return 1;
    } 

    if(argc > 2) {
        std::cerr << "More than 1 argument!" << std::endl;
        return 1;
    }

    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "Basic Renderer", NULL, NULL);
    if (!window) return -1;
    glfwMakeContextCurrent(window);
    
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

    Mesh mesh(argv[1]);
    Material material;
    Object object(mesh, material);
    object.init();

    double xlast, ylast;
    double sens = 0.4f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.2f, 0.3f, 1.0f);
        
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int mousebutton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (mousebutton == GLFW_PRESS) {
            float dx = float(xpos - xlast);
            float dy = float(ypos - ylast);

            if (dx != 0)
                object.transform().rotate(dx * sens, glm::vec3(0, 1, 0));
            if (dy != 0)
                object.transform().rotate(dy * sens, glm::vec3(1, 0, 0));
        }

        xlast = xpos, ylast = ypos;

        object.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
