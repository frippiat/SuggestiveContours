#version 330 core            // minimal GL version support expected from the GPU

layout(location=0) in vec3 vPosition; // the 1st input attribute is the position (CPU side: glVertexAttrib 0)
layout(location=1) in vec3 vNormal;
layout(location=2) in vec2 vTexCoord;
layout(location=3) in float vCurvatureKappa1; // Principal curvature 1
layout(location=4) in float vCurvatureKappa2; // Principal curvature 2
layout(location=5) in float vRadialCurvature; // Radial curvature
layout(location=6) in int vEligibleForSuggestiveContour;

uniform mat4 modelMat, viewMat, projMat;
uniform mat3 normMat;
uniform vec3 camPos;

out vec3 fPositionModel;
out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;
out float dotProduct;
out float fCurvatureKappa1;
out float fCurvatureKappa2;
out float fRadialCurvature;

void main() {
  fPositionModel = vPosition;
  fPosition = (modelMat*vec4(vPosition, 1.0)).xyz;
  fNormal = normMat*vNormal;
  fTexCoord = vTexCoord;

  gl_Position =  projMat*viewMat*modelMat*vec4(vPosition, 1.0); // mandatory

  vec3 v = normalize(camPos - fPosition);
  vec3 n = normalize(fNormal);


  //TRUE CONTOURS
  dotProduct = dot(fNormal, v);

  //CURVATURE
  fCurvatureKappa1=vCurvatureKappa1;
  fCurvatureKappa2=vCurvatureKappa2;
  fRadialCurvature=vRadialCurvature;
  if(vEligibleForSuggestiveContour==0)
  {fRadialCurvature=100;}  
}
