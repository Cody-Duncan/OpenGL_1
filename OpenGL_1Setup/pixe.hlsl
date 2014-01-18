#version 330

in vec3 colorV;
 
out vec4 colorOut;
 
void main() {
	colorOut = vec4(colorV, 0.0);   
}