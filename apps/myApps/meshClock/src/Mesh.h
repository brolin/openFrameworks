#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "Vertex.h"
#include "Layer.h"


//port from my old processing code, looks messy ;)
//contains layers and connect them become a mesh

class Mesh
{
public:
  Layer* layers;
  Vertex center;
  float radius;
  float spacingY;
  float spacingX;
  float h;

  int numLayers;
  int numVertice;
  float decay;
  float rx,ry,rz;
  float bendFactor;
  float bendFactorTarget;
  float px,py;

  float srx,sry;

  float seedx,seedy,seedz;

  int startCount;
  float layerNum;

  Mesh(float _x, float _y, float _z,float _srx,float _sry)
  {
    bendFactor = 0.4;
    bendFactorTarget = random(0,0.5);
    startCount = 0;
    layerNum = 0;
    center.x = _x;
    center.y = _y;
    center.z = _z;
    decay = 0.9;
    radius = 50;
    numVertice = random(3,5);
    numLayers = (int)random(20,30);
    rx = random(-100,100);
    ry = random(-100,100);
    rz = random(-100,100);
    spacingX = ry/numVertice;
    h = random(10,50);
    spacingY = h * layerNum;

    srx = _srx;
    sry = _sry;

    seedx = random(100);
    seedy = random(100);
    seedz = random(100);

    layers = new Layer[numLayers];


    float temRad = radius;

    px = random(-1,1);
    py = random(-1,1);
    for(int i=0;i<numLayers;i++)
    {
      layers[i].init(numVertice);
      Vertex *tempV = new Vertex(center.x+(-i)*spacingY+cos(px*180/PI)*spacingY*i,center.y+(-i)*spacingY+sin(px*180/PI)*spacingY*i+sin(py*180/PI)*spacingY*i,center.z+(-i)*spacingY+cos(py*180/PI)*spacingY*i);

      layers[i].compute(tempV,temRad,rx,spacingX* i,rz);
      delete tempV;
      temRad *=decay;
    }
  }

  void update()
  {
    bendFactor += (bendFactorTarget - bendFactor)*0.005;
    if(ofGetFrameNum()%500 == 0)
    {
        bendFactorTarget = random(0,0.5);
    }
    if(startCount>0)
      startCount--;
    else
    {
      if(layerNum<1)
        layerNum+=0.01;

      seedx += 0.01;
      seedy += 0.01;
      seedz += 0.01;

      rx=(0.3-0.5)*20;
      ry=(0.7-0.5)*20;

      spacingX = ry/numVertice;
      spacingY =  h* layerNum;

      float temRad = radius;
      for(int i=0;i<numLayers;i++)
      {
        Vertex *tempV = new Vertex(center.x+(-i)*spacingY+cos(px*bendFactor*i)*spacingY*i,center.y+(-i)*spacingY+sin(px*bendFactor*i)*spacingY*i+sin(py*bendFactor*i)*spacingY*i,center.z+(-i)*spacingY+cos(py*bendFactor*i)*spacingY*i);

        layers[i].compute(tempV,temRad,rx,spacingX* i,rz);
        delete tempV;
        temRad *=decay;
      }
    }
  }

  void render(bool filled)
  {
    glRotatef(sry,0,1,0);
    glRotatef(srx,1,0,0);
    glPushMatrix();


    glTranslatef(center.x,center.y,center.z);

    glRotatef(PI/2,1,0,0);
    glPopMatrix();
    layers[0].render();
    layers[numLayers-1].render();
    for(int i=0;i<numLayers-1;i++)
    {
      for(int j=0;j<numVertice;j++)
      {
        if(filled)
            glBegin(GL_TRIANGLES);
        else glBegin(GL_LINES);
        vertex(layers[i+1].vertice[j]);
        vertex(layers[i].vertice[(j+1)%numVertice]);
        vertex(layers[i+1].vertice[(j+1)%numVertice]);
        glEnd();

        if(filled)
            glBegin(GL_TRIANGLES);
        else glBegin(GL_LINES);
        vertex(layers[i].vertice[(j+2)%numVertice]);
        vertex(layers[i].vertice[(j+1)%numVertice]);
        vertex(layers[i+1].vertice[(j+1)%numVertice]);
        glEnd();
      }
    }
  }


    //a simple port for processing style random()
  float random(float _1, float _2 = 23123123123.123123)
  {
      if(_2 == 23123123123.123123)
      {
          return ofRandom(0,_1);
      }
      return ofRandom(_1,_2);
  }

    //a simple port for processing style vertex()
  void vertex(Vertex& input)
  {
      glVertex3f(input.x,input.y,input.z);
  }

};

#endif // MESH_H_INCLUDED
