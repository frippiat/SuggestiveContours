#version 330 core            // minimal GL version support expected from the GPU

struct LightSource {
  vec3 position;
  vec3 color;
  float intensity;
  int isActive;
};

int numberOfLights = 3;
uniform LightSource lightSources[3];

struct Material {
  vec3 albedo;
};

uniform Material material;

uniform vec3 camPos;
uniform int u_contourMode;

in vec3 fPositionModel;
in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoord;
in float dotProduct;
in float fRadialCurvature;

out vec4 colorOut; // shader output: the color response attached to this fragment

float pi = 3.1415927;


void main() {
  if(u_contourMode==0)
  {
    vec3 n = normalize(fNormal);
    vec3 wo = normalize(camPos - fPosition); // unit vector pointing to the camera

    vec3 radiance = vec3(0, 0, 0);
    for(int i=0; i<numberOfLights; ++i) {
      LightSource a_light = lightSources[i];
      if(a_light.isActive == 1) { // consider active lights only
        vec3 wi = normalize(a_light.position - fPosition); // unit vector pointing to the light
        vec3 Li = a_light.color*a_light.intensity;
        vec3 albedo = material.albedo;

        radiance += Li*albedo*max(dot(n, wi), 0);
      }
    }
    colorOut = vec4(radiance, 1.0); // build an RGBA value from an RGB one
  }
  else
  {
    colorOut = vec4(0.8,0.8,0.8,1.0); 
    if ((abs(dotProduct)<0.001) && (u_contourMode==1))
    {
      //Reminder: the better the quality of the mesh, the better the quality of the contours
      colorOut = vec4(0.1,0.1,0.6, 1.0);
    }

    if  ((abs(fRadialCurvature)<0.003) && (u_contourMode==2))
    {
      //Reminder: the better the quality of the mesh, the better the quality of the contours
      colorOut = vec4(0.6,0.1,0.1, 1.0);
    }
  } 
}
