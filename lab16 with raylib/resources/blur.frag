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

vec4 blur13(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.411764705882353) * direction;
  vec2 off2 = vec2(3.2941176470588234) * direction;
  vec2 off3 = vec2(5.176470588235294) * direction;
  color += texture2D(image, uv) * 0.1964825501511404;
  color += texture2D(image, uv + (off1 / resolution)) * 0.2969069646728344;
  color += texture2D(image, uv - (off1 / resolution)) * 0.2969069646728344;
  color += texture2D(image, uv + (off2 / resolution)) * 0.09447039785044732;
  color += texture2D(image, uv - (off2 / resolution)) * 0.09447039785044732;
  color += texture2D(image, uv + (off3 / resolution)) * 0.010381362401148057;
  color += texture2D(image, uv - (off3 / resolution)) * 0.010381362401148057;
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

    vec4 red = vec4(1.0, 0.5, 0.5, 1.0);
    vec4 blue = vec4(0.0, 0.5, 0.5, 1.0);

    //finalColor = mix(red, blue, (sin(fragTexCoord.x * 24 + seconds * 4.0) + 1.0) / 2.0);
    //vec4 xBlur = blur13(texture0, fragTexCoord, vec2(renderWidth, renderHeight), vec2(1, 0));
    //vec4 yBlur = blur13(texture0, fragTexCoord, vec2(renderWidth, renderHeight), vec2(0, 1));
    //finalColor = (xBlur + yBlur) * 0.5;
    finalColor = texelColor;
    //finalColor = vec4((sin(fragTexCoord.x * 24 + seconds * 4.0) + 1.0) / 2.0, 0.5, 0.5, 1.0);
}