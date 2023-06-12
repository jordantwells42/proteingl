#shader vertex
#version 120

attribute vec3 position;
    
void main()
{
    gl_Position.xyz = vec3(1.0,1.0,1.0);
    gl_Position.w = 1.0;
}


#shader fragment
#version 120
    
void main()
{
    gl_FragColor = vec4(222.0f, 0.5f, 0.5f ,1.0f);
}