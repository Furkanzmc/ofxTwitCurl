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

    void update();

    void setup(const OAuthInfo &info, const std::string &username, const std::string &password);

    void getAccountVerification(std::function<void(User)> callback);
    void search(const string &query, const string &count, const twitCurlTypes::eTwitCurlResultType &resultType, std::function<void(Tweets)> callback);

private:
    bool m_IsRunningRequest;
    twitCurl m_TwitCurl;
    std::vector<std::pair<std::future<User>, std::function<void(User)>>> m_FuturesUserInfo;
    std::vector<std::pair<std::future<Tweets>, std::function<void(Tweets)>>> m_FuturesTweets;

private:
    User accountVerifyCredGet();
    Tweets doSearch(const string &query, const string &count, const twitCurlTypes::eTwitCurlResultType &resultType = twitCurlTypes::eTwitCurlResultTypeMixed);
};

#endif // ofxTwitCurl_H
