#include "testApp.h"
#include "pixelInfoExtracted.h"
#include <vector>


//--------------------------------------------------------------
void testApp::setup(){	 
  // bikers.loadImage("images/bikers.jpg");
  // gears.loadImage("images/gears.gif");
  // tdf.loadImage("images/tdf_1972_poster.jpg");
  // tdfSmall.loadImage("images/tdf_1972_poster.jpg");
  // tdfSmall.resize(tdf.width / 4, tdf.height / 4);
  // tdfSmall.setImageType(OF_IMAGE_GRAYSCALE);
  // transparency.loadImage("images/transparency.png");
  
  //  vector <pixelInfoExtracted> vectorPIE;

  transparency.loadImage("images/TantaRealidades_limpio.png");
  bikeIcon.loadImage("images/TantaRealidades_024-11-4.png");
  //	bikeIcon.setImageType(OF_IMAGE_GRAYSCALE);
  unsigned char * pixels = bikeIcon.getPixels();
  unsigned char * pixels2 = transparency.getPixels();
  unsigned char * pixelsF = transparency.getPixels();
  int w = bikeIcon.width;
  int h = bikeIcon.height;
  int bytespp = bikeIcon.bpp/8;
  cout<<bikeIcon.bpp<<endl;
  cout<<bikeIcon.type<<endl;
  for (int i = 0; i < w*bytespp; i++){
    for (int j = 0; j < h*bytespp; j++){
      //		  int value = pixels[j * w + i];
      if(pixels[j * w + i] == pixels2[j * w + i]){
	pixelsF[j * w + i] = 0x000000;
      }else{
	pixelsF[j * w + i] = pixels[j * w + i];
	pixelInfoExtracted temp;
	temp.colorPixel = pixels[j * w + i];
	// Quiero guardar la verdadera ubicacion de los pixels. Los limites son 
	// width= 1152 heigth= 864
	// El color tampoco corresponde
	temp.ubicacionWidthPixel = i;
	temp.ubicacionHeigthPixel = j;
	temp.imagenOrigen = 1;
	vectorPIE.push_back(temp);
      }
    }
      //		  float pct = 1 - (value / 255.0f);
      //		  ofCircle(i*10,500 + j*10,1 + 5*pct);		
    }
  cout<<vectorPIE.size()<<endl;
  bikers.setFromPixels(pixelsF,w,h,OF_IMAGE_COLOR,true);
  }


//--------------------------------------------------------------
void testApp::update(){
  ofBackground(255,255,255);	
}


//--------------------------------------------------------------
void testApp::draw(){	
<<<<<<< HEAD
  ofSetColor(0xFFFFFF);
=======
	ofSetHexColor(0xFFFFFF);
>>>>>>> upstream/master

	// bikers.draw(0,0);
	// gears.draw(600,0);
	// tdf.draw(600,300);
	
<<<<<<< HEAD
	// ofSetColor(0xDD3333);
	// tdfSmall.draw(200,300);
	
	// ofSetColor(0xFFFFFF);
	// ofEnableAlphaBlending();
	// transparency.draw(sin(ofGetElapsedTimeMillis()/1000.0f) * 100 + 500,20);
  //	transparency.draw(sin(ofGetElapsedTimeMillis()/1000.0f) * 100 + 500,20);
	//	ofDisableAlphaBlending();
	
	
	//	ofSetColor(0x000000);
	
	// getting the pixels out of an image, 
	// and then use the values to draw circles
	// unsigned char * pixels = bikeIcon.getPixels();
	// unsigned char * pixels2 = transparency.getPixels();
	// unsigned char * pixelsF = transparency.getPixels();
	// int w = bikeIcon.width;
	// int h = bikeIcon.height;
	// for (int i = 0; i < w; i++){
	// 	for (int j = 0; j < h; j++){
	// 	  for (int k = 0; k < 3; k++){
	// 	    //		  int value = pixels[j * w + i];
	// 	    pixelsF[j * w * k + i] = pixels[j * w * k + i] - pixels2[j * w * k + i];
	// 	  //		  float pct = 1 - (value / 255.0f);
	// 	  //		  ofCircle(i*10,500 + j*10,1 + 5*pct);		
	// 	  }
	// 	}
	// }
  bikers.draw(0,0);
  ofSetColor(0xFFFFFF);
	//	bikeIcon.draw(0,0);
  //  cout<<vectorPIE[13].colorPixel<<endl;
  // vector<pixelInfoExtracted>::const_iterator cii;
  // for(cii = vectorPIE.begin(); cii <= vectorPIE.end(); cii++){
  //   //  cout<<cii->colorPixel<<endl;
  //   ofSetColor(cii->colorPixel);
  //   ofCircle(cii->ubicacionWidthPixel,cii->ubicacionHeigthPixel,2);
  // }
  //  cout<<"W: "<<vectorPIE[13].ubicacionWidthPixel<<" H: "<<vectorPIE[13].ubicacionHeigthPixel<<endl;
  for(int i=0; i< 400; i++){
    // cout<<"W: "<<vectorPIE[i].ubicacionWidthPixel<<" H: "<<vectorPIE[i].ubicacionHeigthPixel<<endl;
    // cout<<"R: "<<(vectorPIE[i].colorPixel>>16)<<" G: "<<(vectorPIE[i].colorPixel>>8)<<" B: "<<(vectorPIE[i].colorPixel>>0)<<endl;
    // cout<<"imagen origen: "<<vectorPIE[i].imagenOrigen<<endl;
    ofSetColor(vectorPIE[i].colorPixel);
    ofCircle(vectorPIE[i].ubicacionWidthPixel,vectorPIE[i].ubicacionHeigthPixel,2);
  }
=======
	ofSetHexColor(0xDD3333);
	tdfSmall.draw(200,300);
	
	ofSetHexColor(0xFFFFFF);
	ofEnableAlphaBlending();
	transparency.draw(sin(ofGetElapsedTimeMillis()/1000.0f) * 100 + 500,20);
	ofDisableAlphaBlending();
	
	
	ofSetHexColor(0x000000);
	
	// getting the pixels out of an image, 
	// and then use the values to draw circles
	unsigned char * pixels = bikeIcon.getPixels();
	int w = bikeIcon.width;
	int h = bikeIcon.height;
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++){
			int value = pixels[j * w + i];
			float pct = 1 - (value / 255.0f);
			ofCircle(i*10,500 + j*10,1 + 5*pct);		
		}
	}
	
	ofSetHexColor(0xFFFFFF);
	bikeIcon.draw(300,500, 20,20);
>>>>>>> upstream/master
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
