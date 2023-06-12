#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
out vec2 UV;
out vec3 position;
uniform mat4 camMatrix;


void main()
{
    gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    gl_Position = camMatrix*gl_Position;
    UV = vec2(gl_Position.x, gl_Position.y);
    position = gl_Position.xyz;

}