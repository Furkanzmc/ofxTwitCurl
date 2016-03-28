#ifndef ofxTwitCurl_H
#define ofxTwitCurl_H
#include "twitcurl.h"
#include "ofxTwitCurlTypes.h"
#include "ofxJSON.h"
#include <future>

class ofxTwitCurl
{
public:
    ofxTwitCurl();

    void update(ofEventArgs &args);

    void setup(const ofxTwitCurlTypes::OAuthInfo &info, const std::string &username, const std::string &password);

    void getAccountVerification(std::function<void(ofxTwitCurlTypes::User)> callback);
    void search(const std::string &query, const string &count, const twitCurlTypes::eTwitCurlResultType &resultType,
                std::function<void(ofxTwitCurlTypes::Tweets)> callback);

private:
    bool m_IsRunningRequest;
    twitCurl m_TwitCurl;
    std::vector<std::pair<std::future<ofxTwitCurlTypes::User>, std::function<void(ofxTwitCurlTypes::User)>>> m_FuturesUserInfo;
    std::vector<std::pair<std::future<ofxTwitCurlTypes::Tweets>, std::function<void(ofxTwitCurlTypes::Tweets)>>> m_FuturesTweets;

private:
    ofxTwitCurlTypes::User accountVerifyCredGet();
    ofxTwitCurlTypes::Tweets doSearch(const string &query, const string &count,
                                      const twitCurlTypes::eTwitCurlResultType &resultType = twitCurlTypes::eTwitCurlResultTypeMixed);
};

#endif // ofxTwitCurl_H
