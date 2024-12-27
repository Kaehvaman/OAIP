#version 330

in vec2 fragTexCoord;       // Fragment input attribute: texture coordinate
in vec4 fragColor;          // Fragment input attribute: color
out vec4 finalColor;        // Fragment output: color
uniform sampler2D texture0; // Fragment input texture (always required, could be a white pixel)
uniform vec4 colDiffuse;    // Fragment input color diffuse (multiplied by texture color)

// Custom variables
uniform sampler2D texture1; // water bump map

uniform float xBlurDistance = 0.5 / 750;
uniform float xWaveWidth = 0.1;
uniform float xWaveHeight = 0.1;
uniform float seconds;

uniform vec2 iResolution;

//uniform vec4 waterColor = vec4(0.8, 0.95, 1.0, 1.0);

vec4 getAverageColor(sampler2D iTexture, vec2 uv, float power)
{
    vec4 color = vec4(0);
    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            vec2 offset = vec2(x,y) / iResolution.xy * power;
            color += texture(iTexture, uv + offset);
        }
    }
    
    color /= 9.0;
    
    return color;
}


void main()
{
	vec4 bumpColor = texture(texture1, fragTexCoord + sin(seconds / 2.0) / 20.0);
	bumpColor = (bumpColor + texture(texture1, fragTexCoord*1.5 + cos(seconds / 2.0) / 20.0)) * 0.5;

	vec2 samplePos = fragTexCoord;

	samplePos.x += (bumpColor.r - 0.5) * xWaveWidth * fragColor.r;	
	samplePos.y += (bumpColor.g - 0.5) * xWaveHeight * fragColor.g;

//	vec4 result = texture(texture0, samplePos);
//	result += texture(texture0, vec2(samplePos.x + xBlurDistance, samplePos.y));
//    result += texture(texture0, vec2(samplePos.x - xBlurDistance, samplePos.y));
//    result += texture(texture0, vec2(samplePos.x, samplePos.y - xBlurDistance));
//    result += texture(texture0, vec2(samplePos.x, samplePos.y + xBlurDistance));
//	result += texture(texture0, vec2(samplePos.x + xBlurDistance, samplePos.y + xBlurDistance));
//    result += texture(texture0, vec2(samplePos.x - xBlurDistance, samplePos.y - xBlurDistance));
//    result += texture(texture0, vec2(samplePos.x + xBlurDistance, samplePos.y - xBlurDistance));
//    result += texture(texture0, vec2(samplePos.x - xBlurDistance, samplePos.y + xBlurDistance));
//	
//    result = result / 9;

    vec4 result = getAverageColor(texture0, samplePos, 0.7);
	
	//vec4 result = texture(texture0, samplePos);

	//result.a = texture(texture0, samplePos).a;
	//result = mix(result, result * waterColor, fragColor.b);
	
    result = result*colDiffuse*fragColor;

	finalColor = result;
}
