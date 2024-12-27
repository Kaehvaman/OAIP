#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// Custom variables
uniform float renderWidth;
uniform float renderHeight;
uniform float seconds;
uniform float intensity;
uniform float waves;
uniform float speedV;
uniform float speedH;

void main()
{
    vec2 texelCoord = fragTexCoord;
    vec2 pixelSize = vec2(1.0 / renderWidth, 1.0 / renderHeight);

    texelCoord.x += sin(fragTexCoord.y * waves + seconds * speedV * 2.0 * 3.14) * pixelSize.x * intensity;
    texelCoord.y += sin(fragTexCoord.x * waves + seconds * -speedH * 2.0 * 3.14) * pixelSize.y * intensity;
    
    finalColor = texture(texture0, texelCoord).rgba*colDiffuse*fragColor;
}
