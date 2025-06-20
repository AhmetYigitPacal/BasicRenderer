#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord; 
layout(location = 2) in vec3 aNormal; 

out vec3 normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(){
    gl_Position = proj * view * model * vec4(aPos, 1.0);

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    normal = normalize(normalMatrix * aNormal);

    TexCoord = aTexCoord;
}
