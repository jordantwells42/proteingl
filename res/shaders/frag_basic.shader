#version 330 core
out vec4 FragColor;
  
uniform vec3 camPos;
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 UV;

float sdf_sphere(vec3 p, float r)
{
  return length(p) - r;
}
float smin( float a, float b, float k )
{
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}

vec2 smin2(vec2 a, vec2 b, float k){
  float minx = smin(a.x, b.x, k);
  float miny = mix(a.y, b.y, k);
  return vec2(minx, miny);
}

vec2 sdf(vec3 p){
  float sphere = sdf_sphere(p, 0.2);

  vec2 final = smin2(vec2(sphere, 0.5), vec2(sphere,0.5), 0.5);

  return final;
}

void main()
{
  
vec3 ray = normalize(vec3(UV - vec2(0.5, 0.5),-1));


float t = 0.;
float tMax = 10.;
float count = 0.;

for(int i = 0; i < 128; i++){
vec3 pos = camPos + t*ray;
float h = sdf(pos + vec3(0.5,0.5,0.5)).x;
if (h < 0.0001 || t > tMax) {
    break;
}
t = t + h;
count = count + 1.;
}


vec3 color = vec3(0.0, 0.0, 0.0);
vec3 red = vec3(1.,0.,0.);
vec3 blue = vec3(0.,0.,1.0);
if (t<tMax){
vec3 pos = camPos + t*ray;
color = mix(red, blue, sdf(pos).y);
color = mix(color, vec3(1., 1., 1.), count/16.);
}

FragColor = vec4(color, 1.);
} 