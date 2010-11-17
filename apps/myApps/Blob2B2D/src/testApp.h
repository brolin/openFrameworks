#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBox2d.h"
#include "ofxTriangle.h"
#include "ofxTimer.h"

class testApp : public ofBaseApp{

	public:
	
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		
		void makeComplexBody(b2Body* body, vector <ofxTriangleData> triangles);
				
		ofVideoGrabber			vidGrabber;
		
		ofxCvColorImage			curImg;		
		ofxCvGrayscaleImage		bgImg;
		ofxCvGrayscaleImage		curGrayImg;
		ofxCvGrayscaleImage		bgCurDiff;
		ofxCvGrayscaleImage		prevDiff;
		ofxCvGrayscaleImage		curDiff;
		ofxCvGrayscaleImage		diff;
		ofxCvContourFinder		contourFinder;
		
		ofxBox2d				box2d;	
		vector<b2Body*>			bodies;
		vector<ofxTriangle>		tris;		
		vector<int>				shapeCnts;
		vector<float>			colors;
		
		TimedCounter*			counter;

		int		threshold;
		bool	bLearnBakground;
		bool	bTakeB2DShot;

};

#endif
