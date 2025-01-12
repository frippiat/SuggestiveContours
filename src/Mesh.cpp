#define _USE_MATH_DEFINES

#include "Mesh.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <exception>
#include <ios>
#include <string>
#include <memory>
#include <sstream>

Mesh::~Mesh()
{
  clear();
}

void Mesh::computeBoundingSphere(glm::vec3 &center, float &radius) const
{
  center = glm::vec3(0.0);
  radius = 0.f;
  for(const auto &p : _vertexPositions)
    center += p;
  center /= _vertexPositions.size();
  for(const auto &p : _vertexPositions)
    radius = std::max(radius, distance(center, p));
}

void Mesh::recomputePerVertexNormals(bool angleBased)
{
  _vertexNormals.clear();
  // Change the following code to compute a proper per-vertex normal
  _vertexNormals.resize(_vertexPositions.size(), glm::vec3(0.0, 0.0, 0.0));

  for(unsigned int tIt=0 ; tIt < _triangleIndices.size() ; ++tIt) {
    glm::uvec3 t = _triangleIndices[tIt];
    glm::vec3 n_t = glm::cross(
      _vertexPositions[t[1]] - _vertexPositions[t[0]],
      _vertexPositions[t[2]] - _vertexPositions[t[0]]);
    _vertexNormals[t[0]] += n_t;
    _vertexNormals[t[1]] += n_t;
    _vertexNormals[t[2]] += n_t;
  }
  for(unsigned int nIt = 0 ; nIt < _vertexNormals.size() ; ++nIt) {
    glm::normalize(_vertexNormals[nIt]);
  }
}

void Mesh::recomputePerVertexTextureCoordinates()
{
  _vertexTexCoords.clear();
  // Change the following code to compute a proper per-vertex texture coordinates
  _vertexTexCoords.resize(_vertexPositions.size(), glm::vec2(0.0, 0.0));

  float xMin = FLT_MAX, xMax = FLT_MIN;
  float yMin = FLT_MAX, yMax = FLT_MIN;
  for(glm::vec3 &p : _vertexPositions) {
    xMin = std::min(xMin, p[0]);
    xMax = std::max(xMax, p[0]);
    yMin = std::min(yMin, p[1]);
    yMax = std::max(yMax, p[1]);
  }
  for(unsigned int pIt = 0 ; pIt < _vertexTexCoords.size() ; ++pIt) {
    _vertexTexCoords[pIt] = glm::vec2(
      (_vertexPositions[pIt][0] - xMin)/(xMax-xMin),
      (_vertexPositions[pIt][1] - yMin)/(yMax-yMin));
  }
}

#ifdef SUPPORT_OPENGL_45
void Mesh::init()
{
  glCreateBuffers(1, &_posVbo); // Generate a GPU buffer to store the positions of the vertices
  size_t vertexBufferSize = sizeof(glm::vec3)*_vertexPositions.size(); // Gather the size of the buffer from the CPU-side vector
  glNamedBufferStorage(_posVbo, vertexBufferSize, _vertexPositions.data(), GL_DYNAMIC_STORAGE_BIT); // Create a data store on the GPU

  glCreateBuffers(1, &_normalVbo); // Same for normal
  glNamedBufferStorage(_normalVbo, vertexBufferSize, _vertexNormals.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &_texCoordVbo); // Same for texture coordinates
  size_t texCoordBufferSize = sizeof(glm::vec2)*_vertexTexCoords.size();
  glNamedBufferStorage(_texCoordVbo, texCoordBufferSize, _vertexTexCoords.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &_ibo); // Same for the index buffer, that stores the list of indices of the triangles forming the mesh
  size_t indexBufferSize = sizeof(glm::uvec3)*_triangleIndices.size();
  glNamedBufferStorage(_ibo, indexBufferSize, _triangleIndices.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateVertexArrays(1, &_vao); // Create a single handle that joins together attributes (vertex positions, normals) and connectivity (triangles indices)
  glBindVertexArray(_vao);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _posVbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, _normalVbo);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);

  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, _texCoordVbo);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
  glBindVertexArray(0); // Desactive the VAO just created. Will be activated at rendering time.
}
#else
void Mesh::init()
{
  //MY CODE CHOOSES WITH IF-BRANCH
  // Generate a GPU buffer to store the positions of the vertices
  size_t vertexBufferSize = sizeof(glm::vec3)*_vertexPositions.size();
  glGenBuffers(1, &_posVbo);
  glBindBuffer(GL_ARRAY_BUFFER, _posVbo);
  glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, _vertexPositions.data(), GL_DYNAMIC_READ);

  // Generate a GPU buffer to store the vertex normals of the vertices
  glGenBuffers(1, &_normalVbo);
  glBindBuffer(GL_ARRAY_BUFFER, _normalVbo);
  glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, _vertexNormals.data(), GL_DYNAMIC_READ);

  // Generate a GPU buffer to store the texture coordinates of the vertices
  size_t texCoordBufferSize = sizeof(glm::vec2)*_vertexTexCoords.size();
  glGenBuffers(1, &_texCoordVbo);
  glBindBuffer(GL_ARRAY_BUFFER, _texCoordVbo);
  glBufferData(GL_ARRAY_BUFFER, texCoordBufferSize, _vertexTexCoords.data(), GL_DYNAMIC_READ);

  // // Generate a GPU buffer to store the index buffer that stores the list of indices of the triangles forming the mesh
  size_t indexBufferSize = sizeof(glm::uvec3)*_triangleIndices.size();
  glGenBuffers(1, &_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, _triangleIndices.data(), GL_DYNAMIC_READ);

  // Create a single handle that joins together attributes (vertex positions, normals) and connectivity (triangles indices)
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  /*
  The previous snippet treating _posVbo had the following function:
  It sets up the storage for the vertex positions on the GPU and populates it with the data from the CPU. 
  It only prepares the data but does not tell OpenGL how to interpret it for rendering.

  This following snippet treating _posVbo has the following function:
  It tells OpenGL how to read and interpret the data in the buffer for the enabled vertex attribute:
    - The attribute at location 0 (likely vertex positions) is associated with _posVbo.
    - OpenGL now knows that each vertex is represented by 3 floats.
  */
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _posVbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, _normalVbo);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);

  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, _texCoordVbo);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

  glBindVertexArray(0); // Desactive the VAO just created. Will be activated at rendering time.
}
#endif

void Mesh::render()
{
  glBindVertexArray(_vao);      // Activate the VAO storing geometry data
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_triangleIndices.size()*3), GL_UNSIGNED_INT, 0);
  // Call for rendering: stream the current GPU geometry through the current GPU program
}

void Mesh::clear()
{
  _vertexPositions.clear();
  _vertexNormals.clear();
  _vertexTexCoords.clear();
  _triangleIndices.clear();
  if(_vao) {
    glDeleteVertexArrays(1, &_vao);
    _vao = 0;
  }
  if(_posVbo) {
    glDeleteBuffers(1, &_posVbo);
    _posVbo = 0;
  }
  if(_normalVbo) {
    glDeleteBuffers(1, &_normalVbo);
    _normalVbo = 0;
  }
  if(_texCoordVbo) {
    glDeleteBuffers(1, &_texCoordVbo);
    _texCoordVbo = 0;
  }
  if(_ibo) {
    glDeleteBuffers(1, &_ibo);
    _ibo = 0;
  }
}

void Mesh::calculateCurvature() {
    // Resize storage for curvature results
    principalCurvatureKappa1.resize(_vertexPositions.size(), 0.0f);
    principalCurvatureKappa2.resize(_vertexPositions.size(), 0.0f);
    principalDirectionK1.resize(_vertexPositions.size(), glm::vec3(0.0f));
    principalDirectionK2.resize(_vertexPositions.size(), glm::vec3(0.0f));

    // Temporary storage to accumulate curvature tensors
    std::vector<Eigen::Matrix2d> curvatureTensors(_vertexPositions.size(), Eigen::Matrix2d::Zero());
    std::vector<int> vertexCounts(_vertexPositions.size(), 0);

    // Iterate over triangles
    for (const auto& tri : _triangleIndices) {
        unsigned int i0 = tri[0], i1 = tri[1], i2 = tri[2];
        glm::vec3 p0 = _vertexPositions[i0], p1 = _vertexPositions[i1], p2 = _vertexPositions[i2];
        glm::vec3 n0 = _vertexNormals[i0], n1 = _vertexNormals[i1], n2 = _vertexNormals[i2];

        // Compute triangle edges and partial derivatives
        glm::vec3 e1 = p1 - p0, e2 = p2 - p0;
        glm::vec3 dn1 = n1 - n0, dn2 = n2 - n0;

        // Compute first fundamental form coefficients
        double E = glm::dot(e1, e1), F = glm::dot(e1, e2), G = glm::dot(e2, e2);

        // Compute second fundamental form coefficients
        double L = -glm::dot(dn1, e1), M = -glm::dot(dn1, e2), N = -glm::dot(dn2, e2);

        // Construct Weingarten matrix
        Eigen::Matrix2d W;
        W(0, 0) = (L * G - M * F) / (E * G - F * F);
        W(0, 1) = (M * E - L * F) / (E * G - F * F);
        W(1, 0) = (M * E - N * F) / (E * G - F * F);
        W(1, 1) = (N * E - M * F) / (E * G - F * F);

        // Assign curvature tensor to each vertex
        for (unsigned int v : {i0, i1, i2}) {
            curvatureTensors[v] += W;
            vertexCounts[v]++;
        }
    }

    // Average curvature tensors and compute eigenvalues/directions
    for (unsigned int v = 0; v < _vertexPositions.size(); ++v) {
        if (vertexCounts[v] > 0) {
            curvatureTensors[v] /= vertexCounts[v];

            // Eigen decomposition of curvature tensor
            Eigen::SelfAdjointEigenSolver<Eigen::Matrix2d> solver(curvatureTensors[v]);
            if (solver.info() == Eigen::Success) {
                // Eigenvalues are principal curvatures
                principalCurvatureKappa1[v] = solver.eigenvalues()(0);  // Minimum curvature
                principalCurvatureKappa2[v] = solver.eigenvalues()(1);  // Maximum curvature

                // Eigenvectors are principal directions
                Eigen::Vector2d dir1 = solver.eigenvectors().col(0);
                Eigen::Vector2d dir2 = solver.eigenvectors().col(1);

                // Map back to 3D (tangent plane basis)
                glm::vec3 tangent1 = glm::normalize(dir1[0] * (p1 - p0) + dir1[1] * (p2 - p0));
                glm::vec3 tangent2 = glm::normalize(dir2[0] * (p1 - p0) + dir2[1] * (p2 - p0));
                principalDirectionK1[v] = tangent1;
                principalDirectionK2[v] = tangent2;
            }
        }
    }
}



// Loads an OFF mesh file. See https://en.wikipedia.org/wiki/OFF_(file_format)
void loadOFF(const std::string &filename, std::shared_ptr<Mesh> meshPtr)
{
  std::cout << " > Start loading mesh <" << filename << ">" << std::endl;
  meshPtr->clear();
  std::ifstream in(filename.c_str());
  if(!in)
    throw std::ios_base::failure("[Mesh Loader][loadOFF] Cannot open " + filename);
  std::string offString;
  unsigned int sizeV, sizeT, tmp;
  in >> offString >> sizeV >> sizeT >> tmp;
  auto &P = meshPtr->vertexPositions();
  auto &T = meshPtr->triangleIndices();
  P.resize(sizeV);
  T.resize(sizeT);
  size_t tracker = (sizeV + sizeT)/20;
  std::cout << " > [" << std::flush;
  for(unsigned int i=0; i<sizeV; ++i) {
    if(i % tracker == 0)
      std::cout << "-" << std::flush;
    in >> P[i][0] >> P[i][1] >> P[i][2];
  }
  int s;
  for(unsigned int i=0; i<sizeT; ++i) {
    if((sizeV + i) % tracker == 0)
      std::cout << "-" << std::flush;
    in >> s;
    for(unsigned int j=0; j<3; ++j)
      in >> T[i][j];
  }
  std::cout << "]" << std::endl;
  in.close();
  meshPtr->vertexNormals().resize(P.size(), glm::vec3(0.f, 0.f, 1.f));
  meshPtr->vertexTexCoords().resize(P.size(), glm::vec2(0.f, 0.f));
  meshPtr->recomputePerVertexNormals();
  meshPtr->recomputePerVertexTextureCoordinates();
  std::cout << " > Mesh <" << filename << "> loaded" <<  std::endl;
}

// Loads an OBJ mesh file. See https://en.wikipedia.org/wiki/Wavefront_.obj_file
void loadOBJ(const std::string &filename, std::shared_ptr<Mesh> meshPtr)
{
  std::cout << " > Start loading OBJ mesh <" << filename << ">" << std::endl;
  meshPtr->clear();
  
  std::ifstream in(filename.c_str());
  if (!in)
    throw std::ios_base::failure("[Mesh Loader][loadOBJ] Cannot open " + filename);
  
  std::string line;
  auto &P = meshPtr->vertexPositions();
  auto &T = meshPtr->triangleIndices();
  
  std::vector<glm::vec3> tempPositions;
  std::vector<glm::uvec3> tempIndices;

  while (std::getline(in, line)) {
    std::istringstream ss(line);
    std::string prefix;
    ss >> prefix;
    
    if (prefix == "v") { // Vertex position
      glm::vec3 position;
      ss >> position.x >> position.y >> position.z;
      tempPositions.push_back(position);
    } 
    else if (prefix == "f") { // Face
      glm::uvec3 face;
      for (int i = 0; i < 3; ++i) {
        std::string vertex;
        ss >> vertex;
        size_t pos = vertex.find('/');
        face[i] = static_cast<unsigned int>(std::stoi(vertex.substr(0, pos))) - 1; // Convert to 0-based index
      }
      tempIndices.push_back(face);
    }
  }

  P = tempPositions;
  T = tempIndices;

  std::cout << " > OBJ Mesh <" << filename << "> loaded with " 
            << P.size() << " vertices and " 
            << T.size() << " triangles" << std::endl;
  
  in.close();

  meshPtr->vertexNormals().resize(P.size(), glm::vec3(0.f, 0.f, 1.f));
  meshPtr->vertexTexCoords().resize(P.size(), glm::vec2(0.f, 0.f));
  meshPtr->recomputePerVertexNormals();
  meshPtr->recomputePerVertexTextureCoordinates();
}

