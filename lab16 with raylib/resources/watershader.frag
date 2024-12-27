#version 330

in vec2 fragTexCoord;       // Fragment input attribute: texture coordinate
in vec4 fragColor;          // Fragment input attribute: color
out vec4 finalColor;        // Fragment output: color
uniform sampler2D texture0; // Fragment input texture (always required, could be a white pixel)
uniform vec4 colDiffuse;    // Fragment input color diffuse (multiplied by texture color)

// Custom variables
uniform sampler2D texture1; // water bump map
uniform float xWaveWidth = 0.1;
uniform float xWaveHeight = 0.1;
uniform float seconds;
uniform vec2 iResolution;

vec4 blur13(sampler2D image, vec2 uv, vec2 resolution, vec2 direction)
{
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
	vec4 bumpColor = texture(texture1, fragTexCoord + sin(seconds / 2.0) / 20.0);
	bumpColor = (bumpColor + texture(texture1, fragTexCoord*1.5 + cos(seconds / 2.0) / 20.0)) * 0.5;

	vec2 samplePos = fragTexCoord;
	samplePos.x += (bumpColor.r - 0.5) * xWaveWidth * fragColor.r;	
	samplePos.y += (bumpColor.g - 0.5) * xWaveHeight * fragColor.g;

	vec4 xBlur = blur13(texture0, samplePos, iResolution, vec2(0.5, 0));
	vec4 yBlur = blur13(texture0, samplePos, iResolution, vec2(0, 0.5));
	vec4 result = (xBlur + yBlur) * 0.5;

	result = result*colDiffuse*fragColor;

	finalColor = result;
}
