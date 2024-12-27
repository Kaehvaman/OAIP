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