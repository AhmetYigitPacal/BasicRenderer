#include "Material.h"
#include "Reader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Material::Material(){
    fragmentShaderSource_ = Reader::readFileAsString(DEFAULTFRAGMENTSHADER);
    compileFragmentShader(fragmentShaderSource_.c_str());
}

Material::Material(std::string fragmentShaderPath){
    fragmentShaderSource_ = Reader::readFileAsString(fragmentShaderPath);
    compileFragmentShader(fragmentShaderSource_.c_str());
}

Material::Material(const Material& other){
    fragmentShaderSource_ = other.fragmentShaderSource_;
    color_ = other.color_;

    compileFragmentShader(fragmentShaderSource_.c_str());
}

Material::~Material(){
    glDeleteShader(fragmentShaderID_);
}

void Material::init(unsigned int shaderProgram){
    glUseProgram(shaderProgram);

    colorLocation_ = glGetUniformLocation(shaderProgram, "uColor");

    if(colorLocation_ == -1){
        std::cerr << "ERROR::SHADER::UNIFORM_NOT_FOUND\n";
    }
}

void Material::bind(unsigned int shaderProgram){
    glUseProgram(shaderProgram);
    glUniform4f(colorLocation_, color_.r, color_.g, color_.b, color_.a);
}

void Material::compileFragmentShader(const char* source){
    fragmentShaderID_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID_, 1, &source, nullptr);
    glCompileShader(fragmentShaderID_);

    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShaderID_, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShaderID_, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
    }
}
