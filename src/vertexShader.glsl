#version 330 core            // minimal GL version support expected from the GPU

layout(location=0) in vec3 vPosition; // the 1st input attribute is the position (CPU side: glVertexAttrib 0)
layout(location=1) in vec3 vNormal;
layout(location=2) in vec2 vTexCoord;

uniform mat4 modelMat, viewMat, projMat;
uniform mat3 normMat;
uniform vec3 camPos;

out vec3 fPositionModel;
out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;
out float dotProduct;

void main() {
  fPositionModel = vPosition;
  fPosition = (modelMat*vec4(vPosition, 1.0)).xyz;
  fNormal = normMat*vNormal;
  fTexCoord = vTexCoord;

  gl_Position =  projMat*viewMat*modelMat*vec4(vPosition, 1.0); // mandatory

  vec3 v = normalize(camPos - fPosition);
  vec3 n = normalize(fNormal);
  dotProduct = dot(fNormal, v);
  //OPTION 1: Calculating the dotProduct and letting the fragmentShader define the color of the fragment
  //OPTION 2: Calculating the dotProduct and only letting the fragmentShader the given value as color. Remove the part below to deactivate option 2
  float treshold_countour=0.0005;
  if(dotProduct<0.0005)
  {
    dotProduct=0.0;
  }
  else
  {
    dotProduct=1.0;
  }
}
