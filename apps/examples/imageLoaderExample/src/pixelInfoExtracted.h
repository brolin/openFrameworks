#ifndef _PIXELINFOEXTRACTED
#define _PIXELINFOEXTRACTED


class pixelInfoExtracted {
 public:
  pixelInfoExtracted(){};
  pixelInfoExtracted(unsigned char color,int ubicacionWidth,int ubicacionHeight,int origen);
  unsigned char colorPixel;
  int ubicacionWidthPixel;
  int ubicacionHeigthPixel;
  int imagenOrigen;
};

#endif
