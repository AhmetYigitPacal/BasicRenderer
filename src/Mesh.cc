#include "Mesh.h"
#include "Reader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::Mesh(){
    vertexShaderSource_ = Reader::readFileAsString(DEFAULTVERTEXSHADER);
    compileVertexShader(vertexShaderSource_.c_str());
    setupMesh();
}

Mesh::Mesh(std::vector<float> vertices, std::vector<int> indices) : vertices_(vertices_), indices_(indices_){
    vertexShaderSource_ = Reader::readFileAsString(DEFAULTVERTEXSHADER);
    compileVertexShader(vertexShaderSource_.c_str());
    setupMesh();
}

Mesh::Mesh(std::string objPath){
    vertexShaderSource_ = Reader::readFileAsString(DEFAULTVERTEXSHADER);
    compileVertexShader(vertexShaderSource_.c_str());
    objToMesh(objPath);
    setupMesh();
}

Mesh::Mesh(const Mesh &other) : vertices_(other.vertices_), indices_(other.indices_), vertexShaderSource_(other.vertexShaderSource_){
    compileVertexShader(vertexShaderSource_.c_str());
    setupMesh();
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);

    glDeleteShader(vertexShaderID_);
}

void Mesh::setupMesh(){
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(int), indices_.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::draw(){
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, GLsizei(indices_.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::compileVertexShader(const char* source){
    vertexShaderID_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID_, 1, &source, nullptr);
    glCompileShader(vertexShaderID_);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShaderID_, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShaderID_, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
    }
}

void Mesh::objToMesh(std::string objPath){
    std::vector<std::vector<std::string>> vertexTokens;
    std::vector<std::vector<std::string>> normalTokens;
    std::vector<std::vector<std::string>> texCoordTokens;

    int c = 0;

    std::vector<std::string> lines = Reader::readFileAsLines(objPath);
    if (lines.empty()) {
        std::cerr << "Error: OBJ file is empty or could not be read: " << objPath << "\n";
        return;
    }

    for(std::string line : lines){
        std::vector<std::string> tokens = Reader::split(line, ' ');
        if(tokens[0] == "v"){
            vertexTokens.push_back(tokens);
        }

        if(tokens[0] == "vn"){
            normalTokens.push_back(tokens);
        }

        if(tokens[0] == "vt"){
            texCoordTokens.push_back(tokens);
        }

        if (tokens[0] == "f") {
            int faceVertexCount = int(tokens.size()) - 1;
            if(faceVertexCount < 3) {
                std::cerr << "Warning: Skipping malformed face line: " << line << "\n";
                continue;
            }

            std::vector<int> faceVertexIndices;
            std::vector<int> faceNormalIndices;

            for (int i = 1; i <= faceVertexCount; i++) {
                std::vector<std::string> faceTokens = Reader::split(tokens[i], '/');
                int vertexIndex, texCoordIndex, normalIndex;
                try {
                    if (faceTokens.size() >= 1 && !faceTokens[0].empty())
                        vertexIndex = std::stoi(faceTokens[0]) - 1;
                    if (faceTokens.size() >= 2 && !faceTokens[1].empty())
                        texCoordIndex = std::stoi(faceTokens[1]) - 1;
                    if (faceTokens.size() >= 3 && !faceTokens[2].empty())
                        normalIndex = std::stoi(faceTokens[2]) - 1;
                } catch (const std::exception& e) {
                    std::cerr << "Error parsing face: " << e.what() << " in line: " << line << "\n";
                    continue;
                }

                if (vertexIndex < 0 || vertexIndex >= int(vertexTokens.size())) {
                    std::cerr << "Error: Vertex index out of range in line: " << line << "\n";
                    continue;
                }

                faceVertexIndices.push_back(vertexIndex);
                faceNormalIndices.push_back(normalIndex);

                vertices_.push_back(std::stof(vertexTokens[vertexIndex][1]));
                vertices_.push_back(std::stof(vertexTokens[vertexIndex][2]));
                vertices_.push_back(std::stof(vertexTokens[vertexIndex][3]));
                vertices_.push_back(std::stof(texCoordTokens[texCoordIndex][1]));
                vertices_.push_back(std::stof(texCoordTokens[texCoordIndex][2]));
                vertices_.push_back(std::stof(normalTokens[normalIndex][1]));
                vertices_.push_back(std::stof(normalTokens[normalIndex][2]));
                vertices_.push_back(std::stof(normalTokens[normalIndex][3]));
            }

            for (int i = 1; i < faceVertexCount - 1; i++) {
                indices_.push_back(c + 0);
                indices_.push_back(c + i);
                indices_.push_back(c + i + 1); 
            }

            c += faceVertexCount;
        }
    }
}
