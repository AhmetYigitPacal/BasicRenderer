#ifndef MESH_H_
#define MESH_H_

#include <iostream>
#include <glm/glm.hpp>

static const char* DEFAULTVERTEXSHADER = "shaders/default.vert";

class Mesh{
public:
    Mesh();
    Mesh(std::vector<float> vertices, std::vector<int> indices);
    Mesh(std::string objPath);
    Mesh(const Mesh &other);
    ~Mesh();

    void setupMesh();
    void draw();

    unsigned int vertexShaderID() { return vertexShaderID_; }

protected:
    std::vector<float> vertices_;
    std::vector<int> indices_;

    unsigned int VAO_, VBO_, EBO_;
    unsigned int vertexShaderID_;

    std::string vertexShaderSource_;

    void compileVertexShader(const char* source);

    void objToMesh(std::string objPath);
    
};

#endif // MESH_H_