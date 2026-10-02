#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform bool darkMode;

void main() {
    float t = TexCoords.y;

    vec3 topColor;
    vec3 bottomColor;

    if (darkMode) {
        topColor = vec3(0.30, 0.30, 0.30);
		bottomColor = vec3(0.40, 0.40, 0.40);
    } else {
        topColor = vec3(0.05, 0.2, 0.6);
        bottomColor = vec3(0.6, 0.8, 1.0);
    }

    vec3 color = mix(bottomColor, topColor, t);
    FragColor = vec4(color, 1.0);
}
