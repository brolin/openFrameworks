#include "testApp.h"

#define FRAME_RATE 60
#define TRI_RES 50
#define DIFF_THRESHOLD 500

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(255,255,255);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofEnableSmoothing();

	vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
	
	curImg.allocate(320,240);	
	bgImg.allocate(320,240);
	curGrayImg.allocate(320,240);
	bgCurDiff.allocate(320,240);
	prevDiff.allocate(320,240);
	curDiff.allocate(320,240);
	diff.allocate(320,240);

	box2d.init();
	box2d.setGravity(0, 50);
	box2d.createFloor();
	box2d.checkBounds(true);
	box2d.setFPS(FRAME_RATE);

	counter = new TimedCounter(0, 0, 3000);
	counter->startCount();
	
	bLearnBakground = true;
	bTakeB2DShot = false;
	threshold = 80;
	
}

//--------------------------------------------------------------
void testApp::update(){
	box2d.update();

	bool bNewFrame = false;
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
	if (bNewFrame) {
		curImg.setFromPixels(vidGrabber.getPixels(), 320,240);
		curGrayImg = curImg;
		if (bLearnBakground == true) {
			bgImg = curGrayImg;
			bLearnBakground = false;
		}		
	}

	if(counter->isCounting()){
	
		counter->update();
		
		if(counter->hasChanged()) {
						
			bgCurDiff.absDiff(bgImg, curGrayImg);
			bgCurDiff.threshold(threshold);
			curDiff = bgCurDiff;
			diff.absDiff(prevDiff, curDiff);
			int diffAmt = diff.countNonZeroInRegion(0,0, 320,240);
			cout <<  diffAmt << endl;
			if (diffAmt > DIFF_THRESHOLD) {
				
				contourFinder.findContours(curDiff, 20, (320*240)/3, 10, true);
				
				tris.clear();
				for (int i = 0; i < contourFinder.nBlobs; i++) {
				
					ofxTriangle tri;
					tri.clear();
					tri.triangulate(contourFinder.blobs[i], TRI_RES);
					tris.push_back(tri);
					
					if (bTakeB2DShot) {
						b2BodyDef* bodyDef = new b2BodyDef();
						bodyDef->position.Set(360/OFX_BOX2D_SCALE, 20/OFX_BOX2D_SCALE);
						bodyDef->linearDamping = 0.25;
						bodyDef->angularDamping = 0.25;
						b2Body* body = box2d.getWorld()->CreateBody(bodyDef);	
						makeComplexBody(body, tri.triangles);
						bodies.push_back(body);
						colors.push_back(ofRandom(0, 0xffffff));
					}
				}						
			}
			prevDiff = bgCurDiff;
		}

	}		
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0xffffff);
	curGrayImg.draw(360,20);

	if (bTakeB2DShot) {
	
		for (int i = 0; i < bodies.size(); i++) {
		
			b2Body*	body = bodies[i];
			b2Shape* s = body->GetShapeList();
			const b2XForm& xf = body->GetXForm();
			b2PolygonShape* poly = (b2PolygonShape*)s;
			int count = poly->GetVertexCount();
			const b2Vec2* localVertices = poly->GetVertices();
			vector<b2Vec2> verts;
			
			for(int j = 0; j < count; j++) {
				verts.push_back(b2Mul(xf, localVertices[j]));
			}
			
			int shapeCnt = shapeCnts[i];			
			for (int j = 0; j < shapeCnt-1; j++) {
				b2Shape* next = s->GetNext();
				s = next;
				b2PolygonShape* poly = (b2PolygonShape*)next;
				int count = poly->GetVertexCount();
				const b2Vec2* localVertices = poly->GetVertices();
				for(int k = 0; k < count; k++) {
					verts.push_back(b2Mul(xf, localVertices[k]));
				}					
			}
			
			ofEnableAlphaBlending();
				ofSetColor(colors[i]);
				glBegin(GL_TRIANGLES); 
					for(int j = 0; j < verts.size(); j++) {
						glVertex3f(verts[j].x*OFX_BOX2D_SCALE, verts[j].y*OFX_BOX2D_SCALE, 0);
					}
				glEnd();			
			ofDisableAlphaBlending();		
		}
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
		case '1':
			bTakeB2DShot = !bTakeB2DShot;
			break;	
	}
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

//http://www.psyked.co.uk/box2d/simple-box2d-custom-polygon-creation.htm
void testApp::makeComplexBody(b2Body* body, vector<ofxTriangleData> triangles) {
	int shapeCnt = 0;
	
	for (int i = 0; i < triangles.size(); i++) {
	
		b2PolygonDef* shapeDef = new b2PolygonDef();
		shapeDef->density = 1;
		shapeDef->friction = 5;
		shapeDef->vertexCount = 3;

		shapeDef->vertices[0].Set(triangles[i].a.x/OFX_BOX2D_SCALE, triangles[i].a.y/OFX_BOX2D_SCALE);
		shapeDef->vertices[1].Set(triangles[i].b.x/OFX_BOX2D_SCALE, triangles[i].b.y/OFX_BOX2D_SCALE);
		shapeDef->vertices[2].Set(triangles[i].c.x/OFX_BOX2D_SCALE, triangles[i].c.y/OFX_BOX2D_SCALE);
		
		body->CreateShape(shapeDef);
		shapeCnt++;
	}
	
	shapeCnts.push_back(shapeCnt);
	body->SetMassFromShapes();
}