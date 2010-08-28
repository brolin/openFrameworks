#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED
#include "Vertex.h"

//port from my old processing code, looks messy ;)
//represents a single layer in mesh

class Layer
{
public:
  Vertex *vertice;
  Vertex *center;
  float radius;
  int numVertice;

  Layer()
  {
  }

  void init(int input)
  {
    vertice = new Vertex[input];
    numVertice = input;
  }

  void compute(Vertex *_center, float r, float rx, float ry, float rz)
  {
    center = _center;
    radius = r;

    float seg = PI*2 / numVertice;
    for(int i=0;i<numVertice;i++)
    {
      float _x = r * sin(ry + seg*i) + r * cos(rz*i);
      float _z = r * cos(ry + seg*i) +r * cos(rx*i);
      float _y = r * sin(rx*i) + r * sin(rz*i);
      vertice[i].x = (_x + center->x);
      vertice[i].y = (_y+ center->y);
      vertice[i].z = (_z + center->z);
    }
  }

  void render() //render single layer
  {
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0;i<numVertice;i++)
    {
      glVertex3f(vertice[i].x,vertice[i].y,vertice[i].z);
    }
    glEnd();
  }
};

#endif // LAYER_H_INCLUDED
