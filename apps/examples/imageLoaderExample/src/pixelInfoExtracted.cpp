#include "ofMain.h"
#include "pixelInfoExtracted.h"

pixelInfoExtracted::pixelInfoExtracted(unsigned char color,int ubicacionWidth,int ubicacionHeigth,int origen){
  colorPixel = color;
  ubicacionWidthPixel = ubicacionWidth;
  ubicacionHeigthPixel = ubicacionHeigth;
  imagenOrigen = origen;  
}

