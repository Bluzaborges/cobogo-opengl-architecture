#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D screenTexture;

void main()
{
    vec3 color = texture(screenTexture, TexCoords).rgb;

    float dist = distance(TexCoords, vec2(0.5));

    float radius   = 0.75;
    float softness = 0.45;
    float strength = 0.25;

    float vignette = clamp((radius - dist) / softness, 0.0, 1.0);

    color *= mix(1.0, vignette, strength);

    color = pow(color, vec3(1.05));

    FragColor = vec4(color, 1.0);
}
