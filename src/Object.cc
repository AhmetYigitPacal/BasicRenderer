#include "Object.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

Object::Object() {
    vertexShaderID_ = mesh_.vertexShaderID();
    fragmentShaderID_ = material_.fragmentShaderID();

    linkShaders();
}

Object::Object(Mesh mesh, Material material) : mesh_(mesh), material_(material) {
    vertexShaderID_ = mesh_.vertexShaderID();
    fragmentShaderID_ = material_.fragmentShaderID();

    linkShaders();
}

Object::~Object() {
    glDetachShader(shaderProgram_, vertexShaderID_);
    glDetachShader(shaderProgram_, fragmentShaderID_);

    glDeleteProgram(shaderProgram_);
}

void Object::init() {
    glUseProgram(shaderProgram_);

    modelLocation_ = glGetUniformLocation(shaderProgram_, "model");
    viewLocation_ = glGetUniformLocation(shaderProgram_, "view");
    projLocation_ = glGetUniformLocation(shaderProgram_, "proj");

    material_.init(shaderProgram_);

    if(modelLocation_ == -1 || viewLocation_ == -1 || projLocation_ == -1){
        std::cerr << "ERROR::SHADER::UNIFORM_NOT_FOUND\n";
    }
}

void Object::render() {
    glUseProgram(shaderProgram_);

    glUniformMatrix4fv(modelLocation_, 1, GL_FALSE, &model_[0][0]);
    glUniformMatrix4fv(viewLocation_, 1, GL_FALSE, &view_[0][0]);
    glUniformMatrix4fv(projLocation_, 1, GL_FALSE, &proj_[0][0]);

    model_ = glm::mat4(1.0f);
    view_ = glm::mat4(1.0f);
    proj_ = glm::mat4(1.0f);

    model_ = glm::translate(glm::mat4(1.0f), transform_.position());
    model_ *= glm::mat4_cast(transform_.rotation());
    model_ *= glm::scale(glm::mat4(1.0f), transform_.scale());



    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upVector    = glm::vec3(0.0f, 1.0f, 0.0f);

    view_ = glm::lookAt(cameraPos, cameraTarget, upVector);

    float fov = glm::radians(45.0f);
    float aspectRatio = 640.0f / 480.0f; // Hard Coded for now
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    proj_ = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

    material_.bind(shaderProgram_);
    mesh_.draw();
}

void Object::linkShaders() {
    glDeleteProgram(shaderProgram_);

    shaderProgram_ = glCreateProgram();
    glAttachShader(shaderProgram_, vertexShaderID_);
    glAttachShader(shaderProgram_, fragmentShaderID_);
    glLinkProgram(shaderProgram_);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram_, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
    }

    init();
}
