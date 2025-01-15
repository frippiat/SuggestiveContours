Implementing the positive differential

std::vector<float> radialCurvatureDerivative(_vertexPositions.size(), 0.0f);


for (unsigned int v = 0; v < _vertexPositions.size(); ++v) {
    glm::vec3 v_t = glm::normalize(cameraPosition - _vertexPositions[v]);
    float derivative = 0.0f;
    int neighborCount = 0;

    for (unsigned int u : getNeighbors(v)) { // Function to find neighbors of v
        glm::vec3 diff = _vertexPositions[u] - _vertexPositions[v];
        float proj = glm::dot(diff, v_t);
        if (proj != 0.0f) {
            derivative += (radialCurvature[u] - radialCurvature[v]) * proj / glm::length2(diff);
            neighborCount++;
        }
    }

    if (neighborCount > 0) {
        radialCurvatureDerivative[v] = derivative / neighborCount;
    }
}
