#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>
#include <memory>
#include <Eigen>


#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <map>
#include <set>

class Mesh {
public:
  virtual ~Mesh();

  const std::vector<glm::vec3> &vertexPositions() const { return _vertexPositions; }
  std::vector<glm::vec3> &vertexPositions() { return _vertexPositions; }

  const std::vector<glm::vec3> &vertexNormals() const { return _vertexNormals; }
  std::vector<glm::vec3> &vertexNormals() { return _vertexNormals; }

  const std::vector<glm::vec2> &vertexTexCoords() const { return _vertexTexCoords; }
  std::vector<glm::vec2> &vertexTexCoords() { return _vertexTexCoords; }

  const std::vector<glm::uvec3> &triangleIndices() const { return _triangleIndices; }
  std::vector<glm::uvec3> &triangleIndices() { return _triangleIndices; }

  /// Compute the parameters of a sphere which bounds the mesh
  void computeBoundingSphere(glm::vec3 &center, float &radius) const;

  void recomputePerVertexNormals(bool angleBased = false);
  void recomputePerVertexTextureCoordinates( );

  void init();
  void initOldGL();
  void render();
  void clear();
  void calculatePrincipalCurvature();
  void calculateRadialCurvature(const glm::vec3& cameraPosition);

  void subdivideLoop1()
  {
    // Declare new vertices and new triangles. Initialize the new positions for the even vertices with (0,0,0):
    std::vector<glm::vec3> newVertices( _vertexPositions.size() , glm::vec3(0,0,0) );
    std::vector<glm::uvec3> newTriangles;

    struct Edge {
      unsigned int a , b;
      Edge( unsigned int c , unsigned int d ) : a( std::min<unsigned int>(c,d) ) , b( std::max<unsigned int>(c,d) ) {}
      bool operator < ( Edge const & o ) const {   return a < o.a  ||  (a == o.a && b < o.b);  }
      bool operator == ( Edge const & o ) const {   return a == o.a  &&  b == o.b;  }
    };

    std::map< Edge , unsigned int > newVertexOnEdge; // this will be useful to find out whether we already inserted an odd vertex or not
    std::map< Edge , std::set< unsigned int > > trianglesOnEdge; // this will be useful to find out if an edge is boundary or not
    std::vector< std::set< unsigned int > > neighboringVertices( _vertexPositions.size() ); // this will be used to store the adjacent vertices, i.e., neighboringVertices[i] will be the list of vertices that are adjacent to vertex i.
    std::vector< bool > evenVertexIsBoundary( _vertexPositions.size() , false );


    for(unsigned int tIt = 0 ; tIt < _triangleIndices.size() ; ++tIt) {
      unsigned int a = _triangleIndices[tIt][0];
      unsigned int b = _triangleIndices[tIt][1];
      unsigned int c = _triangleIndices[tIt][2];


      Edge Eab(a,b);
      Edge Ebc(b,c);
      Edge Eca(c,a);

      trianglesOnEdge[Eab].insert(tIt);
      trianglesOnEdge[Ebc].insert(tIt);
      trianglesOnEdge[Eca].insert(tIt);

      neighboringVertices[ a ].insert( b );
      neighboringVertices[ a ].insert( c );
      neighboringVertices[ b ].insert( a );
      neighboringVertices[ b ].insert( c );
      neighboringVertices[ c ].insert( a );
      neighboringVertices[ c ].insert( b );
    }
    std::vector< unsigned int > evenVertexValence( _vertexPositions.size() , 0 );
    for( unsigned int v = 0 ; v < _vertexPositions.size() ; ++v ) {
      evenVertexValence[ v ] = neighboringVertices[ v ].size();
    }

    for (const auto& pair : trianglesOnEdge) {
    const Edge& edge = pair.first;
    const std::set<unsigned int>& triangles = pair.second;
    if (triangles.size() == 1) {
        evenVertexIsBoundary[edge.a] = true;
        evenVertexIsBoundary[edge.b] = true;
      }
    }
    
    for(unsigned int v = 0 ; v < _vertexPositions.size() ; ++v) {
      glm::vec3 sumNeighbours(0.0,0.0,0.0);
    if(evenVertexIsBoundary[v]==false)
    {
      int n= evenVertexValence[ v ];

      for(unsigned int u : neighboringVertices[v]) {
        sumNeighbours+=_vertexPositions[u];
      }

      float warren_formula;
      if (n==3)
      {
        warren_formula= 3.0f/16.0f;
      }
      else
      {
        warren_formula= 3.0f/(8.0f*n);
      }

      newVertices[v]=(sumNeighbours*warren_formula) + ((1-n*warren_formula)*_vertexPositions[v]);
    }
    else
    {

      for(unsigned int u : neighboringVertices[v]) {
        if(evenVertexIsBoundary[u]==true)
        {
          sumNeighbours+=_vertexPositions[u];
        }
      }

      newVertices[v]=(0.125f*sumNeighbours) + (0.75f*_vertexPositions[v]);
    }


    }
      
    for(unsigned int tIt = 0 ; tIt < _triangleIndices.size() ; ++tIt) {
      unsigned int a = _triangleIndices[tIt][0];
      unsigned int b = _triangleIndices[tIt][1];
      unsigned int c = _triangleIndices[tIt][2];


      Edge Eab(a,b);
      unsigned int oddVertexOnEdgeEab = 0;
      if( newVertexOnEdge.find( Eab ) == newVertexOnEdge.end() ) {
        newVertices.push_back( glm::vec3(0,0,0) );
        oddVertexOnEdgeEab = newVertices.size() - 1;
        newVertexOnEdge[Eab] = oddVertexOnEdgeEab;
      }
      else { oddVertexOnEdgeEab = newVertexOnEdge[Eab]; }

      if (trianglesOnEdge[Eab].size() == 1) {
        newVertices[oddVertexOnEdgeEab] = 0.5f * (_vertexPositions[a] + _vertexPositions[b]);
      } 
      
      else {

        glm::vec3 positionOddVertex = 0.375f * (_vertexPositions[a] + _vertexPositions[b]);

        for (unsigned int triangleIndex :  trianglesOnEdge[Eab])
        {
          const glm::uvec3 &triangleOfEdge = _triangleIndices[triangleIndex];
          for (unsigned int vertex : {triangleOfEdge[0],triangleOfEdge[1],triangleOfEdge[2]})
          {
            if (vertex!=a && vertex!=b)
            {
              positionOddVertex+=0.125f*_vertexPositions[vertex];
            }
          }
        }

        newVertices[oddVertexOnEdgeEab] = positionOddVertex;
    
      }



      Edge Ebc(b,c);
      unsigned int oddVertexOnEdgeEbc = 0;
      if( newVertexOnEdge.find( Ebc ) == newVertexOnEdge.end() ) {
        newVertices.push_back( glm::vec3(0,0,0) );
        oddVertexOnEdgeEbc = newVertices.size() - 1;
        newVertexOnEdge[Ebc] = oddVertexOnEdgeEbc;
      }
      else { oddVertexOnEdgeEbc = newVertexOnEdge[Ebc]; }      
      if (trianglesOnEdge[Ebc].size() == 1) {
        newVertices[oddVertexOnEdgeEbc] = 0.5f * (_vertexPositions[b] + _vertexPositions[c]);
      } 
      
      else {

        glm::vec3 positionOddVertex = 0.375f * (_vertexPositions[b] + _vertexPositions[c]);

        for (unsigned int triangleIndex :  trianglesOnEdge[Ebc])
        {
          const glm::uvec3 &triangleOfEdge = _triangleIndices[triangleIndex];
          for (unsigned int vertex : {triangleOfEdge[0],triangleOfEdge[1],triangleOfEdge[2]})
          {
            if (vertex!=b && vertex!=c)
            {
              positionOddVertex+=0.125f*_vertexPositions[vertex];
            }
          }
        }

        newVertices[oddVertexOnEdgeEbc] = positionOddVertex;
    
      }

      Edge Eca(c,a);
      unsigned int oddVertexOnEdgeEca = 0;
      if( newVertexOnEdge.find( Eca ) == newVertexOnEdge.end() ) {
        newVertices.push_back( glm::vec3(0,0,0) );
        oddVertexOnEdgeEca = newVertices.size() - 1;
        newVertexOnEdge[Eca] = oddVertexOnEdgeEca;
      }
      else { oddVertexOnEdgeEca = newVertexOnEdge[Eca]; }

      if (trianglesOnEdge[Eca].size() == 1) {
        newVertices[oddVertexOnEdgeEca] = 0.5f * (_vertexPositions[c] + _vertexPositions[a]);
      } 
      
      else {

        glm::vec3 positionOddVertex = 0.375f * (_vertexPositions[c] + _vertexPositions[a]);

        for (unsigned int triangleIndex :  trianglesOnEdge[Eca])
        {
          const glm::uvec3 &triangleOfEdge = _triangleIndices[triangleIndex];
          for (unsigned int vertex : {triangleOfEdge[0],triangleOfEdge[1],triangleOfEdge[2]})
          {
            if (vertex!=c && vertex!=a)
            {
              positionOddVertex+=0.125f*_vertexPositions[vertex];
            }
          }
        }

        newVertices[oddVertexOnEdgeEca] = positionOddVertex;
    
      }
    
      newTriangles.push_back( glm::uvec3( a , oddVertexOnEdgeEab , oddVertexOnEdgeEca ) );
      newTriangles.push_back( glm::uvec3( oddVertexOnEdgeEab , b , oddVertexOnEdgeEbc ) );
      newTriangles.push_back( glm::uvec3( oddVertexOnEdgeEca , oddVertexOnEdgeEbc , c ) );
      newTriangles.push_back( glm::uvec3( oddVertexOnEdgeEab , oddVertexOnEdgeEbc , oddVertexOnEdgeEca ) );
    }

    _triangleIndices = newTriangles;
    _vertexPositions = newVertices;
    recomputePerVertexNormals( );
    recomputePerVertexTextureCoordinates( );
  }


  void subdivideLoop() 
  {
    subdivideLoop1();
  }
private:
  std::vector<glm::vec3> _vertexPositions;
  std::vector<glm::vec3> _vertexNormals;
  std::vector<glm::vec2> _vertexTexCoords;
  std::vector<glm::uvec3> _triangleIndices;
  std::vector<float> principalCurvatureKappa1;
  std::vector<float> principalCurvatureKappa2;
  std::vector<glm::vec3> principalDirectionK1;
  std::vector<glm::vec3> principalDirectionK2;
  std::vector<float> radialCurvature;

  GLuint _vao = 0;
  GLuint _posVbo = 0;
  GLuint _normalVbo = 0;
  GLuint _texCoordVbo = 0;
  GLuint _ibo = 0;
  GLuint _curvatureKappa1Vbo = 0;
  GLuint _curvatureKappa2Vbo = 0;
  GLuint _radialCurvatureVbo=0;
};

// utility: loader
void loadOFF(const std::string &filename, std::shared_ptr<Mesh> meshPtr);
void loadOBJ(const std::string &filename, std::shared_ptr<Mesh> meshPtr);

#endif  // MESH_H
