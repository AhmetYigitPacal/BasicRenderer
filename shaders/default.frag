#version 330 core

in vec3 normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec4 uColor;
uniform vec3 lightPos;
uniform float shininess;

uniform vec3 viewDir;

void main(){
    float minLight = -1.;
    vec3 lightSource = vec3(0., 1., .5);
    float diff = max(
        (dot(normalize(normal), lightSource)),
        minLight
    );

    diff = clamp(diff, 0., 1.);
    diff = 1. / 3. + step(.1, diff) / 3. + step(.5, diff) / 3.;

    vec3 shine = reflect(-lightSource, normalize(normal));
    float spec = max(dot(viewDir, shine), 0.0);
    spec = pow(spec, 128.);
    spec = step(.95, spec);
    vec4 shineColor = (uColor * .6 + vec4(1., 1., 1., 1.) * .4) * spec;

    vec4 color = uColor * diff + shineColor * shininess;

    FragColor = vec4(color);
}
