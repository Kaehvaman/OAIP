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

float offset[3] = float[](0.0, 1.3846153846, 3.2307692308);
float weight[3] = float[](0.2270270270, 0.3162162162, 0.0702702703);

vec4 getAverageColor(sampler2D iTexture, vec2 resolution, vec2 uv, float power)
{
	vec4 color = vec4(0);
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			vec2 offset = vec2(x,y) / resolution.xy * power;
			color += texture(iTexture, uv + offset);
		}
	}
	
	color /= 9.0;
	
	return color;
}

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord).rgba*weight[0];

    for (int i = 1; i < 3; i++)
    {
        texelColor += texture(texture0, fragTexCoord + vec2(offset[i], 0.0) / renderWidth).rgba * weight[i] / 2;
        texelColor += texture(texture0, fragTexCoord + vec2(-offset[i], 0.0) / renderWidth).rgba * weight[i] / 2;
        texelColor += texture(texture0, fragTexCoord + vec2(0.0, offset[i]) / renderWidth).rgba * weight[i] / 2;
        texelColor += texture(texture0, fragTexCoord + vec2(0.0, -offset[i]) / renderWidth).rgba * weight[i] / 2;
    }

    finalColor = texelColor;
}