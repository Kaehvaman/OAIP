#version 330

in vec2 fragTexCoord;       // Fragment input attribute: texture coordinate
in vec4 fragColor;          // Fragment input attribute: color
out vec4 finalColor;        // Fragment output: color
uniform sampler2D texture0; // Fragment input texture (always required, could be a white pixel)
uniform vec4 colDiffuse;    // Fragment input color diffuse (multiplied by texture color)

uniform vec2 resolution;
uniform vec2 direction;

void main()
{
	vec4 color = vec4(0.0);
	vec2 off1 = vec2(1.411764705882353) * direction;
	vec2 off2 = vec2(3.2941176470588234) * direction;
	vec2 off3 = vec2(5.176470588235294) * direction;
	
	color += texture(texture0, fragTexCoord) * 0.1964825501511404;
	color += texture(texture0, fragTexCoord + (off1 / resolution)) * 0.2969069646728344;
	color += texture(texture0, fragTexCoord - (off1 / resolution)) * 0.2969069646728344;
	color += texture(texture0, fragTexCoord + (off2 / resolution)) * 0.09447039785044732;
	color += texture(texture0, fragTexCoord - (off2 / resolution)) * 0.09447039785044732;
	color += texture(texture0, fragTexCoord + (off3 / resolution)) * 0.010381362401148057;
	color += texture(texture0, fragTexCoord - (off3 / resolution)) * 0.010381362401148057;
	
	finalColor = color*colDiffuse*fragColor;
}

//vec4 blur13(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
//  vec4 color = vec4(0.0);
//  vec2 off1 = vec2(1.411764705882353) * direction;
//  vec2 off2 = vec2(3.2941176470588234) * direction;
//  vec2 off3 = vec2(5.176470588235294) * direction;
//  color += texture(image, uv) * 0.1964825501511404;
//  color += texture(image, uv + (off1 / resolution)) * 0.2969069646728344;
//  color += texture(image, uv - (off1 / resolution)) * 0.2969069646728344;
//  color += texture(image, uv + (off2 / resolution)) * 0.09447039785044732;
//  color += texture(image, uv - (off2 / resolution)) * 0.09447039785044732;
//  color += texture(image, uv + (off3 / resolution)) * 0.010381362401148057;
//  color += texture(image, uv - (off3 / resolution)) * 0.010381362401148057;
//  return color;
//}

//const float pi = 3.1415926;
//const int samples = 15;
//const float sigma = float(samples) * 0.25;
//const float s = 2 * sigma * sigma;
//vec2 pixelSize = vec2(1.0) / iResolution;
//
//float gauss(vec2 i)
//{
//    return exp(-(i.x * i.x + i.y * i.y) / s) / (pi * s);
//}
//
//vec4 gaussianBlur(sampler2D image, vec2 uv, vec2 scale)
//{
//    vec4 color = vec4(0.0);
//    float weightSum = 0.0;
//    float weight;
//    vec2 offset;
//
//    for(int i = -samples / 2; i < samples / 2; i++)
//    {
//        for(int j = -samples / 2; j < samples / 2; j++)
//        {
//            offset = vec2(i, j);
//            weight = gauss(offset);
//            color += texture(image, uv + scale * offset) * weight;
//            weightSum += weight;
//        }
//    }
//    return color / weightSum;
//}