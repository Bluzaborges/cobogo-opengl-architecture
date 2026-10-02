#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture;
uniform vec3 baseColor;
uniform vec3 lightDir;

void main()
{
    vec3 n = normalize(Normal);
    vec3 light = normalize(lightDir);

    float diff = max(dot(n, light), 0.0);

    float ambient = 0.85;
    float lighting = ambient + 0.2 * diff;

    vec3 base = useTexture ? texture(texture1, TexCoord).rgb : baseColor;

    vec3 finalColor = base * lighting;
    FragColor = vec4(finalColor, 1.0);
}
