#version 330 core

in vec3 fragPos;
out vec4 FragColor;

void main()
{
    vec3 color = vec3(0.8);

    if (fragPos.z == 0.0 && fragPos.y == 0.0)
        color = vec3(1.0, 0.0, 0.0);

    if (fragPos.x == 0.0 && fragPos.z == 0.0)
        color = vec3(0.0, 1.0, 0.0);

    if (fragPos.x == 0.0 && fragPos.y == 0.0)
        color = vec3(0.0, 0.0, 1.0);

    FragColor = vec4(color, 1.0);
}