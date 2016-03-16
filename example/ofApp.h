#pragma once

#include "ofBaseApp.h"
#include "ofxTwitCurl.h"
#include "ofImage.h"
#include "ofxThreadedImageLoader.h"
#include <future>

class ofApp : public ofBaseApp
{
public:
    ofApp();

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    ofxTwitCurl m_Twitter;
    ofColor m_Color;
    std::string m_Username;
    ofImage m_Image;
    ofxThreadedImageLoader m_ImageLoader;
    Tweets m_Tweets;
};
