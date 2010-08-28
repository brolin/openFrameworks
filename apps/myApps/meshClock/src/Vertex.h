#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED


//port from my old processing code, looks messy ;)
//a simple x,y,z value class with awful direction function


class Vertex
{
public:
  float x,y,z;

  Vertex()
  {
      x = 0;
      y = 0;
      z = 0;
  }

  Vertex(float _x,float _y, float _z)
  {
    x = _x;
    y = _y;
    z = _z;
  }

  float direction(Vertex input)
  {
    return atan2(x-input.x,z-input.z);
  }
};

#endif // VERTEX_H_INCLUDED
