#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>
#include <memory>

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

  void subdivideLoop1() {
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


    // I) First, compute the valences of the even vertices, the neighboring vertices required to update the position of the even vertices, and the boundaries:
    for(unsigned int tIt = 0 ; tIt < _triangleIndices.size() ; ++tIt) {
      unsigned int a = _triangleIndices[tIt][0];
      unsigned int b = _triangleIndices[tIt][1];
      unsigned int c = _triangleIndices[tIt][2];

 //TODO: Remember the faces shared by the edge: DONE

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

    // The valence of a vertex is the number of adjacent vertices:
    std::vector< unsigned int > evenVertexValence( _vertexPositions.size() , 0 );
    for( unsigned int v = 0 ; v < _vertexPositions.size() ; ++v ) {
      evenVertexValence[ v ] = neighboringVertices[ v ].size();
    }
//TODO: Identify even vertices (clue: check the number of triangles) and remember immediate neighbors for further calculation
    // STARTING HERE:
    for (const auto& pair : trianglesOnEdge) {
    const Edge& edge = pair.first;
    const std::set<unsigned int>& triangles = pair.second;
    if (triangles.size() == 1) {
        evenVertexIsBoundary[edge.a] = true;
        evenVertexIsBoundary[edge.b] = true;
    }
}


    /*
    COMPLETELY FINISHED
    For each vertex:
      Look to which edges it is connected. 
        For each edge to which it is connected:
          look in trianglesOnEdge how many triangles are connected to that edge (just the size)
            Create 
            if size=1:
              the edge is on the border of the mesh, so the vertex is also on the border of the mesh: set the bool mapped to the vertex in evenVertexIsBoundary to true
          after checking all edges: if for no edge size=1 (and so for all edges size=2), then the vertex is not on the border of the mesh

      ORDINARY = NOT ON BORDER, EXTRA ORDINARY = ON BORDER

      in evenVertexIsBoundary, indicate if the vertex is on border or not
    */
    // II) Then, compute the positions for the even vertices: (make sure that you handle the boundaries correctly)
//TODO: Compute the coordinates for even vertices - check both the cases - ordinary and extraordinary

    

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
      
    /*
    For each vertex v:
        For extraordinary case:
          Create Create std::set <unsigned int> neighboursOfNodeOnBorder (it is empty for now)
            define the neighbouring vertices of vertex i that are also on the border
            {
              For each neighbour Nv of v in neighboringVertices[ v ]:
                Verify in evenVertexIsBoundary if u is on the border:
                  if u is on the border: add u to neighboursOfNodeOnBorder
            }
          Calculate v's new position based on the positions of the vertexes of neighboursOfNodeOnBorder and v, which can be found in _vertexPositions. The formula is the figure rechtsbeneden (even mask, extraordinary case) on slide on slide 40 of Curves & Surfaces in CG
          Store v's new position in newVertices
        For ordinary case:
          Calculate v's new position based on the positions of the neighbours in vertices in neighboringVertices and v in  _vertexPositions. The formula is the figure rechsboven (even mask, ordinary case) on slide on slide 40 of Curves & Surfaces in CG
          Store v's new position in newVertices
    */
    


    // III) Then, compute the odd vertices:
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

        //TODO: Update odd vertices


      if (trianglesOnEdge[Eab].size() == 1) {
        // Boundary case: Average of the two endpoint positions
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

      //TODO: Update odd vertices
      
      if (trianglesOnEdge[Ebc].size() == 1) {
        // Boundary case: Average of the two endpoint positions
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

      //TODO: Update odd vertices

      if (trianglesOnEdge[Eca].size() == 1) {
        // Boundary case: Average of the two endpoint positions
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
    


      // set new triangles :
      newTriangles.push_back( glm::uvec3( a , oddVertexOnEdgeEab , oddVertexOnEdgeEca ) );
      newTriangles.push_back( glm::uvec3( oddVertexOnEdgeEab , b , oddVertexOnEdgeEbc ) );
      newTriangles.push_back( glm::uvec3( oddVertexOnEdgeEca , oddVertexOnEdgeEbc , c ) );
      newTriangles.push_back( glm::uvec3( oddVertexOnEdgeEab , oddVertexOnEdgeEbc , oddVertexOnEdgeEca ) );
    }


    // after that:
    _triangleIndices = newTriangles;
    _vertexPositions = newVertices;
    recomputePerVertexNormals( );
    recomputePerVertexTextureCoordinates( );
  }





  void subdivideLoop() {
    subdivideLoop1();
  }

private:
  std::vector<glm::vec3> _vertexPositions;
  std::vector<glm::vec3> _vertexNormals;
  std::vector<glm::vec2> _vertexTexCoords;
  std::vector<glm::uvec3> _triangleIndices;

  GLuint _vao = 0;
  GLuint _posVbo = 0;
  GLuint _normalVbo = 0;
  GLuint _texCoordVbo = 0;
  GLuint _ibo = 0;
};

// utility: loader
void loadOFF(const std::string &filename, std::shared_ptr<Mesh> meshPtr);
void loadOBJ(const std::string &filename, std::shared_ptr<Mesh> meshPtr);

#endif  // MESH_H
