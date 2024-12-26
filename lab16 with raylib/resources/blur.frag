#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

// NOTE: values must be passed from code
uniform float renderWidth;
uniform float renderHeight;
uniform float seconds;

float offset[3] = float[](0.0, 1.3846153846, 3.2307692308);
float weight[3] = float[](0.2270270270, 0.3162162162, 0.0702702703);

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord).rgba*weight[0];

    for (int i = 1; i < 3; i++)
    {
        texelColor += texture(texture0, fragTexCoord + vec2(offset[i], offset[i]) / renderWidth).rgba * weight[i] / 2;
        texelColor += texture(texture0, fragTexCoord - vec2(offset[i], offset[i]) / renderWidth).rgba * weight[i] / 2;
        texelColor += texture(texture0, fragTexCoord + vec2(-offset[i], offset[i]) / renderWidth).rgba * weight[i] / 2;
        texelColor += texture(texture0, fragTexCoord - vec2(-offset[i], offset[i]) / renderWidth).rgba * weight[i] / 2;
    }

    vec4 red = vec4(1.0, 0.5, 0.5, 1.0);
    vec4 blue = vec4(0.0, 0.5, 0.5, 1.0);

    //finalColor = mix(red, blue, (sin(fragTexCoord.x * 24 + seconds * 4.0) + 1.0) / 2.0);

    finalColor = texelColor;
    //finalColor = vec4((sin(fragTexCoord.x * 24 + seconds * 4.0) + 1.0) / 2.0, 0.5, 0.5, 1.0);
}