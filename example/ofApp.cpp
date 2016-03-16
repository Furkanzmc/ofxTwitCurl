#include "ofApp.h"
//openFrameworks
#include "ofMain.h"

ofApp::ofApp()
{

}

void ofApp::setup()
{
    OAuthInfo info;
    info.consumerKey = "";
    info.consumerSecret = "";
    info.oauthTokenKey = "";
    info.oauthTokenSecret = "";

    m_Twitter.setup(info, "", "");

    m_Color = ofColor::red;
    m_Username = "";
}

void ofApp::update()
{
    m_Twitter.update();
}

void ofApp::draw()
{
    ofPushMatrix();
    {
        ofPushStyle();
        {
            ofTranslate(100, 100, 0);
            ofSetColor(m_Color);
            ofCircle(ofPoint(std::sin(ofGetElapsedTimef()) * 100, 50), 25);
        }
        ofPopStyle();
    }
    ofPopMatrix();

    ofDrawBitmapString(m_Username, 0, 20);
    ofDrawBitmapString(std::to_string(ofGetFrameRate()), 0, 50);

    if (m_Image.isAllocated()) {
        m_Image.draw(0, 200, 0);
    }
}

void ofApp::keyPressed(int key)
{

}

void ofApp::keyReleased(int key)
{
    if (key == 'u') {
        m_Color = ofColor::red;
        m_Username = "";
        m_Twitter.getAccountVerification([this](User user) {
            m_Username = user.screenName;
            m_ImageLoader.loadFromURL(m_Image, user.profileImageURL);
            m_Color = ofColor::green;
        });
    }
    else if (key == 's') {
        m_Twitter.search("#openFrameworks", "50", twitCurlTypes::eTwitCurlResultTypeRecent, [this](Tweets tweets) {
            m_Tweets = tweets;
            const Tweet &tweet = tweets.at(ofRandom(0, tweets.size() - 1));
            m_Username = tweet.user.screenName;
            m_Color = ofColor::green;
        });
    }
    else if (key == '2') {
        const Tweet &tweet = m_Tweets.at(ofRandom(0, m_Tweets.size() - 1));
        m_Username = tweet.user.screenName;
        if (tweet.entities.media.size() > 0) {
            m_ImageLoader.loadFromURL(m_Image, tweet.entities.media.at(ofRandom(0, tweet.entities.media.size() - 1)).mediaURL);
        }
    }
}

void ofApp::mouseMoved(int x, int y)
{

}

void ofApp::mouseDragged(int x, int y, int button)
{

}

void ofApp::mousePressed(int x, int y, int button)
{

}

void ofApp::mouseReleased(int x, int y, int button)
{

}

void ofApp::mouseEntered(int x, int y)
{

}

void ofApp::mouseExited(int x, int y)
{

}

void ofApp::windowResized(int w, int h)
{

}

void ofApp::gotMessage(ofMessage msg)
{

}

void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
