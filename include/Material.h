#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <iostream>
#include <string>
#include <glm/glm.hpp>

static const char * DEFAULTFRAGMENTSHADER = "shaders/default.frag";
static const glm::vec4 DEFAULTCOLOR = glm::vec4(0.7f, 0.7f, 0.8f, 1.0f);

class Material {
public:
    Material();
    Material(std::string fragmentShaderPath);
    Material(const Material& other);
    ~Material();

    void init(unsigned int shaderProgram);
    void bind(unsigned int shaderProgram);

    glm::vec4 color() { return color_; }
    void setColor(glm::vec4 color) { color_ = color; }
    void setColor(float r, float g, float b, float a) { color_ = glm::vec4(r, g, b, a); }
    
    unsigned int fragmentShaderID() { return fragmentShaderID_; }
    
private:
    unsigned int fragmentShaderID_;
    std::string fragmentShaderSource_;

    unsigned int colorLocation_;

    glm::vec4 color_ = DEFAULTCOLOR;

    void compileFragmentShader(const char* source);
};

#endif // MATERIAL_H_