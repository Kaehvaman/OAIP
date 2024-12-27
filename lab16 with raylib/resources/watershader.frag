#version 330

in vec2 fragTexCoord;       // Fragment input attribute: texture coordinate
in vec4 fragColor;          // Fragment input attribute: color
out vec4 finalColor;        // Fragment output: color
uniform sampler2D texture0; // Fragment input texture (always required, could be a white pixel)
uniform vec4 colDiffuse;    // Fragment input color diffuse (multiplied by texture color)

// Custom variables
uniform sampler2D texture1; // water bump map
//uniform vec2 xBumpPos;
//uniform vec2 xBumpScale;
//uniform vec2 xUvOffset;

uniform float xBlurDistance = 0.6 / 750;
uniform float xWaveWidth = 0.1;
uniform float xWaveHeight = 0.1;
uniform float seconds;

uniform vec4 waterColor = vec4(180.0 / 255.0, 230.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0);

void main()
{
	//vec4 bumpColor = texture(xWaterBumpMap, xUvOffset + xBumpPos * xBumpScale);
	//bumpColor = (bumpColor + texture(xWaterBumpMap, xUvOffset + xBumpPos*2 * xBumpScale)) * 0.5;
	vec4 bumpColor = texture(texture1, fragTexCoord + sin(seconds / 2.0) / 20.0);
	bumpColor = (bumpColor + texture(texture1, fragTexCoord*2 + cos(seconds / 2.0) / 20.0)) * 0.5;

	vec2 samplePos = fragTexCoord;

	samplePos.x += (bumpColor.r - 0.5) * xWaveWidth * fragColor.r;	
	samplePos.y += (bumpColor.g - 0.5) * xWaveHeight * fragColor.g;

	vec4 result;
	result = texture(texture0, vec2(samplePos.x + xBlurDistance, samplePos.y + xBlurDistance));
    result += texture(texture0, vec2(samplePos.x - xBlurDistance, samplePos.y - xBlurDistance));
    result += texture(texture0, vec2(samplePos.x + xBlurDistance, samplePos.y - xBlurDistance));
    result += texture(texture0, vec2(samplePos.x - xBlurDistance, samplePos.y + xBlurDistance));
	
    result = result * 0.25;
	
	//vec4 result = texture(texture0, samplePos);

	result.a = fragColor.a;
	result = mix(result, result * waterColor, fragColor.b);

	finalColor = result;
}
