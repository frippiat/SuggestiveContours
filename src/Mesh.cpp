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

  // Create and populate buffer for radialCurvature (location=5)
  glGenBuffers(1, &_radialCurvatureVbo);
  glBindBuffer(GL_ARRAY_BUFFER, _radialCurvatureVbo);
  glBufferData(GL_ARRAY_BUFFER, radialCurvature.size() * sizeof(float), radialCurvature.data(), GL_DYNAMIC_READ);

  std::vector<GLint> eligibleInt(eligible_for_suggestive_contour.size());
  for (size_t i = 0; i < eligible_for_suggestive_contour.size(); i++) {
      eligibleInt[i] = eligible_for_suggestive_contour[i] ? 1 : 0;
  }
  glGenBuffers(1, &_eligibleForSuggestiveContourVbo);
  glBindBuffer(GL_ARRAY_BUFFER, _eligibleForSuggestiveContourVbo);
  glBufferData(GL_ARRAY_BUFFER, eligibleInt.size() * sizeof(GLint), eligibleInt.data(), GL_DYNAMIC_READ);

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

  glEnableVertexAttribArray(5); // Radial curvature attribute location
  glBindBuffer(GL_ARRAY_BUFFER, _radialCurvatureVbo);
  glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(float), 0);

  glEnableVertexAttribArray(6);
  glBindBuffer(GL_ARRAY_BUFFER, _eligibleForSuggestiveContourVbo);
  // Use the integer version of the attribute pointer.
  glVertexAttribIPointer(6, 1, GL_INT, sizeof(GLint), 0);

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
  if (_radialCurvatureVbo) {
    glDeleteBuffers(1, &_radialCurvatureVbo);
    _radialCurvatureVbo= 0;
    }
  
  if (_eligibleForSuggestiveContourVbo) {
    glDeleteBuffers(1, &_eligibleForSuggestiveContourVbo);
    _eligibleForSuggestiveContourVbo = 0;
  }

  if(_ibo) {
    glDeleteBuffers(1, &_ibo);
    _ibo = 0;
  }
}


/**
 * This function has been created for the suggestive contouring project.
 *
 * Computes the principal curvatures and principal directions at each vertex of the mesh.
 * Curvature information is aggregated from adjacent triangles and eigen-decomposition
 * is performed on the resulting curvature tensor to extract the minimum and maximum
 * curvatures along with their corresponding directions.
 */
void Mesh::calculatePrincipalCurvature() {
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
          // Average the curvature tensor
          curvatureTensors[v] /= vertexCounts[v];

          // Perform eigen decomposition of the curvature tensor
          Eigen::SelfAdjointEigenSolver<Eigen::Matrix2d> solver(curvatureTensors[v]);
          if (solver.info() == Eigen::Success) {
              // Eigenvalues are the principal curvatures
              principalCurvatureKappa1[v] = solver.eigenvalues()(0);  // Minimum curvature
              principalCurvatureKappa2[v] = solver.eigenvalues()(1);  // Maximum curvature

              // Eigenvectors are the principal directions in 2D (tangent plane coordinates)
              Eigen::Vector2d dir1 = solver.eigenvectors().col(0); // First principal direction
              Eigen::Vector2d dir2 = solver.eigenvectors().col(1); // Second principal direction

              // Compute tangent plane basis vectors from 3D positions of neighbors
              glm::vec3 tangentU(0.0f), tangentV(0.0f);
              for (const auto& tri : _triangleIndices) {
                  if (tri[0] == v || tri[1] == v || tri[2] == v) {
                      // Find two edges of the triangle that share vertex v
                      unsigned int v1 = (tri[0] == v) ? tri[1] : tri[0];
                      unsigned int v2 = (tri[0] == v || tri[1] == v) ? tri[2] : tri[1];

                      glm::vec3 edge1 = _vertexPositions[v1] - _vertexPositions[v];
                      glm::vec3 edge2 = _vertexPositions[v2] - _vertexPositions[v];

                      // Use these edges to compute a local tangent basis
                      tangentU += edge1;
                      tangentV += edge2;
                  }
              }

              // Normalize the tangent vectors
              tangentU = glm::normalize(tangentU);
              tangentV = glm::normalize(tangentV);

              // Map 2D eigenvectors back to 3D using the tangent basis
              glm::vec3 principalDir1 = glm::normalize(static_cast<float>(dir1[0]) * tangentU + static_cast<float>(dir1[1]) * tangentV);
              glm::vec3 principalDir2 = glm::normalize(static_cast<float>(dir2[0]) * tangentU + static_cast<float>(dir2[1]) * tangentV);

              // Store principal directions
              principalDirectionK1[v] = principalDir1;
              principalDirectionK2[v] = principalDir2;
          }
      }
    }
}


/**
 * This function has been created for the suggestive contouring project.
 *
 * Computes the one-ring neighborhood for each vertex in the mesh. For each vertex,
 * the function gathers all adjacent vertices that share a common triangle.
 *
 * @return A vector of sets, where each set contains the indices of neighboring vertices.
 */
std::vector<std::set<unsigned int>> Mesh::computeOneRingNeighbors() const {
  std::vector<std::set<unsigned int>> neighbors(_vertexPositions.size());
  for (const auto &tri : _triangleIndices) {
      neighbors[tri[0]].insert(tri[1]);
      neighbors[tri[0]].insert(tri[2]);
      neighbors[tri[1]].insert(tri[0]);
      neighbors[tri[1]].insert(tri[2]);
      neighbors[tri[2]].insert(tri[0]);
      neighbors[tri[2]].insert(tri[1]);
  }
  return neighbors;
}


/**
 * This function has been created for the suggestive contouring project.
 *
 * Computes per-triangle gradients of the radial curvature and accumulates these contributions
 * for each vertex. For each triangle, the barycentric gradients of the coordinate functions are computed
 * and weighted by the interior angles. The results are stored in gradAccum (gradient vectors) and
 * weightAccum (corresponding weights).
 *
 * @param gradAccum A reference to a vector to store the accumulated gradient vectors for each vertex.
 * @param weightAccum A reference to a vector to store the accumulated weights for each vertex.
 */
void Mesh::computeTriangleGradientAccumulators(std::vector<glm::vec3> &gradAccum,
                                                 std::vector<float> &weightAccum) const {
  // Initialize accumulators for each vertex.
  gradAccum.resize(_vertexPositions.size(), glm::vec3(0.0f));
  weightAccum.resize(_vertexPositions.size(), 0.0f);

  // Loop over triangles.
  for (const auto &tri : _triangleIndices) {
      unsigned int i = tri[0], j = tri[1], k = tri[2];
      const glm::vec3 &p_i = _vertexPositions[i];
      const glm::vec3 &p_j = _vertexPositions[j];
      const glm::vec3 &p_k = _vertexPositions[k];

      glm::vec3 e1 = p_j - p_i;
      glm::vec3 e2 = p_k - p_i;
      glm::vec3 n = glm::normalize(glm::cross(e1, e2));
      float area2 = glm::length(glm::cross(e1, e2));
      if (area2 < 1e-8f)
          continue; // Skip degenerate triangles.

      // Barycentric gradients.
      glm::vec3 gradLambda_i = glm::cross(n, p_k - p_j) / area2;
      glm::vec3 gradLambda_j = glm::cross(n, p_i - p_k) / area2;
      glm::vec3 gradLambda_k = glm::cross(n, p_j - p_i) / area2;

      // Radial curvature at vertices (previously computed) 
      float r_i = radialCurvature[i];
      float r_j = radialCurvature[j];
      float r_k = radialCurvature[k];

      // Triangle’s gradient of radial curvature.
      glm::vec3 G = r_i * gradLambda_i + r_j * gradLambda_j + r_k * gradLambda_k;

      // Compute interior angles.
      float angle_i = acos(glm::clamp(glm::dot(glm::normalize(p_j - p_i),
                                                 glm::normalize(p_k - p_i)), -1.0f, 1.0f));
      float angle_j = acos(glm::clamp(glm::dot(glm::normalize(p_i - p_j),
                                                 glm::normalize(p_k - p_j)), -1.0f, 1.0f));
      float angle_k = acos(glm::clamp(glm::dot(glm::normalize(p_i - p_k),
                                                 glm::normalize(p_j - p_k)), -1.0f, 1.0f));

      // Accumulate weighted contributions.
      gradAccum[i] += angle_i * G;
      weightAccum[i] += angle_i;
      
      gradAccum[j] += angle_j * G;
      weightAccum[j] += angle_j;
      
      gradAccum[k] += angle_k * G;
      weightAccum[k] += angle_k;
  }
}


/**
 * This function has been created for the suggestive contouring project.
 *
 * Computes the directional derivative of the radial curvature at each vertex.
 * Using the accumulated per-vertex gradients (gradAccum) and corresponding weights (weightAccum),
 * the function averages the gradient at each vertex and projects it onto the view-projected tangent
 * direction determined from the camera position.
 *
 * @param gradAccum The per-vertex accumulated gradient vectors.
 * @param weightAccum The per-vertex accumulated weights.
 * @param cameraPosition The position of the camera.
 * @return A vector of directional derivative values for each vertex.
 */
std::vector<float> Mesh::computeDirectionalDerivatives(const std::vector<glm::vec3>& gradAccum,
                                                         const std::vector<float>& weightAccum,
                                                         const glm::vec3 &cameraPosition) const {
  std::vector<float> dirDeriv(_vertexPositions.size(), 0.0f);
  for (unsigned int v = 0; v < _vertexPositions.size(); v++) {
      glm::vec3 grad = (weightAccum[v] > 0.0f) ? (gradAccum[v] / weightAccum[v]) : glm::vec3(0.0f);
      
      glm::vec3 viewVec = glm::normalize(cameraPosition - _vertexPositions[v]);
      glm::vec3 normal = glm::normalize(_vertexNormals[v]);

      // Project viewVec onto the tangent plane to get w
      glm::vec3 w = glm::normalize(viewVec - glm::dot(viewVec, normal) * normal);
      
      // Compute directional derivative along w
      dirDeriv[v] = glm::dot(grad, w);
  }
  return dirDeriv;
}


/**
 * This function has been created for the suggestive contouring project.
 *
 * Applies derivative and view-dependent thresholds to the computed directional derivatives, and
 * then performs hysteresis filtering to enhance contour continuity. Vertices with derivatives
 * above a high threshold (t_high) are marked as strong, those between a low (t_low) and high threshold
 * as weak, and weak vertices adjacent to strong ones are upgraded.
 *
 * @param dirDeriv The vector of directional derivative values for each vertex.
 * @param neighbors The one-ring neighborhood for each vertex.
 * @param t_high The high threshold for the directional derivative.
 * @param t_low The low threshold for the directional derivative.
 * @param theta_c The view-dependent threshold angle (in radians).
 * @param cameraPosition The current position of the camera.
 * @return A vector of integers indicating the eligibility (e.g., 0 for not eligible, 2 for strong).
 */
std::vector<int> Mesh::applyThresholdsAndHysteresis(const std::vector<float> &dirDeriv,
                                                      const std::vector<std::set<unsigned int>> &neighbors,
                                                      float t_high, float t_low, float theta_c,
                                                      const glm::vec3 &cameraPosition) const {
  std::vector<int> eligibility(_vertexPositions.size(), 0);
  
  // Assign initial eligibility based on derivative and view conditions.
  for (unsigned int v = 0; v < _vertexPositions.size(); v++) {
      glm::vec3 viewVec = glm::normalize(cameraPosition - _vertexPositions[v]);
      glm::vec3 normal = glm::normalize(_vertexNormals[v]);
      bool viewCondition = (glm::dot(normal, viewVec) < cos(theta_c));
      if (!viewCondition)
          eligibility[v] = 0;
      else if (dirDeriv[v] >= t_high)
          eligibility[v] = 2; // strong
      else if (dirDeriv[v] >= t_low)
          eligibility[v] = 1; // weak
      else
          eligibility[v] = 0;
  }
  
  // Hysteresis filtering: Upgrade weak vertices adjacent to strong ones.
  bool changed = true;
  while (changed) {
      changed = false;
      for (unsigned int v = 0; v < _vertexPositions.size(); v++) {
          if (eligibility[v] == 1) { // weak vertex
              for (unsigned int nb : neighbors[v]) {
                  if (eligibility[nb] == 2) {
                      eligibility[v] = 2;
                      changed = true;
                      break;
                  }
              }
          }
      }
  }
  
  return eligibility;
}


/**
 * This function has been created for the suggestive contouring project.
 *
 * Determines which vertices in the mesh are eligible for suggestive contours.
 * It integrates the following steps: computes per-triangle gradient accumulators, builds the one-ring
 * connectivity, computes per-vertex directional derivatives, and applies both derivative and view-dependent
 * thresholds along with hysteresis filtering. The final eligibility information is stored internally for rendering.
 *
 * @param cameraPosition The current position of the camera.
 */
void Mesh::verify_which_vertex_is_eligible_for_in_a_suggestive_contour(const glm::vec3 &cameraPosition) {
    
    // Define thresholds
    const float t_high = 0.005f;            // Strong derivative threshold
    const float t_low  = 0.002f;            // Weak derivative threshold
    const float theta_c = glm::radians(20.0f); // Minimum view angle in radians

    // Step 1: Compute triangle–wise gradient accumulators.
    std::vector<glm::vec3> gradAccum;
    std::vector<float> weightAccum;
    computeTriangleGradientAccumulators(gradAccum, weightAccum);

    // Step 2: Build one–ring neighbor connectivity.
    std::vector<std::set<unsigned int>> neighbors = computeOneRingNeighbors();

    // Step 3: Compute per–vertex directional derivatives.
    std::vector<float> dirDeriv = computeDirectionalDerivatives(gradAccum, weightAccum, cameraPosition);

    // Step 4: Apply thresholds and hysteresis filtering using the helper function.
    std::vector<int> eligibility = applyThresholdsAndHysteresis(dirDeriv, neighbors, t_high, t_low, theta_c, cameraPosition);
    
    // Final: Mark vertex eligible only if classified as strong (i.e., eligibility == 2).
    eligible_for_suggestive_contour.resize(_vertexPositions.size(), false);
    for (unsigned int v = 0; v < _vertexPositions.size(); v++) {
        eligible_for_suggestive_contour[v] = (eligibility[v] == 2);
    }
}


/**
 * This function has been created for the suggestive contouring project.
 *
 * Computes the radial curvature at each vertex of the mesh using Euler's formula.
 * This view-dependent curvature is updated based on the current camera position and is critical for the
 * extraction of suggestive contours.
 *
 * @param cameraPosition The current position of the camera.
 */
void Mesh::calculateRadialCurvature(const glm::vec3& cameraPosition) {
    // Resize the storage for radial curvature
    radialCurvature.resize(_vertexPositions.size(), 0.0f);

    for (unsigned int v = 0; v < _vertexPositions.size(); ++v) {
        if (principalCurvatureKappa1[v] == 0.0f && principalCurvatureKappa2[v] == 0.0f) {
            // Skip vertices without valid principal curvatures
            continue;
        }

        // Compute the direction vector from the vertex to the camera
        glm::vec3 w = glm::normalize(cameraPosition - _vertexPositions[v]);

        // Compute the angles between `w` and the principal directions
        float cosPhi = glm::dot(w, glm::normalize(principalDirectionK1[v]));
        float sinPhi = glm::sqrt(1.0f - cosPhi * cosPhi); // sin²(φ) + cos²(φ) = 1

        // Compute radial curvature using the Euler formula
        radialCurvature[v] = principalCurvatureKappa1[v] * cosPhi * cosPhi +
                             principalCurvatureKappa2[v] * sinPhi * sinPhi;
    }

    verify_which_vertex_is_eligible_for_in_a_suggestive_contour(cameraPosition);
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

