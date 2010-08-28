#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	myShader.loadShader("myShader");

    mesh = new Mesh*[100];
    for(int j=0;j<10;j++)
    {
        for(int i=0;i<10;i++)
        {
            mesh[i+j*10] = new Mesh(0,0,0,360 / 10 * i,360 / 10 * j);
        }
    }
    ofSetVerticalSync(true);
    isBlend = true;

    myFont.loadFont("GOTHICB.TTF", 120);

    hueColor.setMode(OF_COLOR_HSV);
}

//--------------------------------------------------------------
void testApp::update(){

    //send hue to shader
    myShader.setShaderActive(true);
	hueColor.setRange(255);
    hueColor.set((int)((ofGetFrameNum()+1500)/15)%256,250,255);
    hueColor.setRange(1);
	myShader.setUniformVariable3f("hue",hueColor.getRed(),hueColor.getGreen(),hueColor.getBlue());

    for(int i=0;i<100;i++)
	{
        mesh[i]->update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255,255,255);
    glScalef(ofGetScreenWidth()/1920.0,ofGetScreenWidth()/1920.0,1);

	ofEnableAlphaBlending();
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    if(isBlend)
    {
        //subtractive blending
        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE,GL_ZERO,GL_ONE);
        glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT,GL_FUNC_ADD);
    }
    else
    {
        glDisable(GL_BLEND);
    }


    // Create light components
    float ambientLight[] = { 0.2f, 0.8f, 0.8f, 1.0f };
    float diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    float specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float position[] = { -1.5f, 100.0f, 1000.0f, 1.0f };

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);


    glLineWidth (0.01);

	glPushMatrix();
    ofSetColor(255,255,255);

	glTranslatef(1920/1.6, 1080/2, 0);                //trying to match different screen resolution


	//set hue and tell shader
	glRotatef(ofGetFrameNum()*0.1,0.02,0.03,0.05);


    //render solids
	for(int i=0;i<100;i++)
	{
        mesh[i]->render(true);
	}
	myShader.setShaderActive(false);

    //render wireframes (without shader)
    for(int i=0;i<100;i++)
	{
        mesh[i]->render(false);
	}

	glPopMatrix();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);


    //draw clock
    ofSetColor(255,0,0,0.5);
	char timetime[100];
	if(ofGetFrameNum()%30>=15)
        sprintf(timetime,"%02d:%02d",ofGetHours(),ofGetMinutes());
    else sprintf(timetime,"%02d.%02d",ofGetHours(),ofGetMinutes());
    myFont.drawString(timetime, -myFont.stringWidth(timetime)+1920-50,1080/2 + 50);

    sprintf(timetime,"%02d/%02d/%04d",ofGetDay(),ofGetMonth(),ofGetYear());
    myFont.drawString(timetime, 40,1080/2 + 50);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == ' ')
    {
        //take screenshot
        char buffer[100];
        sprintf(buffer,"output%d.png",ofGetFrameNum());
        ofSaveScreen(buffer);
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

