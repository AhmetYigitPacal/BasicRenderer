#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

class Object {
public:
    Object();
    Object(Mesh mesh, Material material);
    ~Object();

    void init();
    void render();

    Mesh& mesh() { return mesh_; }
    // void setMesh(Mesh mesh) { mesh_ = mesh;}

    Material& material() { return material_; }
    // void setMaterial(Material material) { material_ = material; }

    Transform& transform() { return transform_; }

private:
    Mesh mesh_;
    Material material_;
    Transform transform_;

    unsigned int shaderProgram_;
    unsigned int vertexShaderID_;
    unsigned int fragmentShaderID_;

    unsigned int modelLocation_;
    unsigned int viewLocation_;
    unsigned int projLocation_;

    glm::mat4 model_;
    glm::mat4 view_;
    glm::mat4 proj_;

    void linkShaders();
};

#endif // RENDERER_H_
