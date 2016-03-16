#include "ofxTwitCurl.h"
#include "urlencode.h"
#include "ofxTwitCurlCreators.h"

#define OPERATION_CHECK() \
    do { \
        if (m_IsRunningRequest) { \
            ofLogWarning("ofxTwitCurl") << __FUNCTION__ << ": Only one operation at a time is allowed."; return; \
        } \
        else { \
            m_IsRunningRequest = true; \
        } \
    } while (false)

ofxTwitCurl::ofxTwitCurl()
    : m_IsRunningRequest(false)
    , m_TwitCurl()
{
}

void ofxTwitCurl::update()
{
    for (unsigned int i = 0; i < m_FuturesUserInfo.size(); i++) {
        std::pair<std::future<User>, std::function<void(User)>> &p = m_FuturesUserInfo.at(i);
        std::future<User> &fut = p.first;
        std::chrono::milliseconds span(1);

        if (fut.valid() && fut.wait_for(span) != std::future_status::timeout) {
            const User user = fut.get();
            if (p.second) {
                p.second(user);
            }

            m_FuturesUserInfo.erase(m_FuturesUserInfo.begin() + i);
            m_IsRunningRequest = false;
        }
    }

    for (unsigned int i = 0; i < m_FuturesTweets.size(); i++) {
        std::pair<std::future<Tweets>, std::function<void(Tweets)>> &p = m_FuturesTweets.at(i);
        std::future<Tweets> &fut = p.first;
        std::chrono::milliseconds span(1);

        if (fut.valid() && fut.wait_for(span) != std::future_status::timeout) {
            const Tweets tweets = fut.get();
            if (p.second) {
                p.second(tweets);
            }

            m_FuturesTweets.erase(m_FuturesTweets.begin() + i);
            m_IsRunningRequest = false;
        }
    }
}

void ofxTwitCurl::setup(const OAuthInfo &info, const std::string &username, const std::string &password)
{
    m_TwitCurl.setTwitterUsername(username);
    m_TwitCurl.setTwitterPassword(password);
    m_TwitCurl.getOAuth().setConsumerKey(info.consumerKey);
    m_TwitCurl.getOAuth().setConsumerSecret(info.consumerSecret);
    m_TwitCurl.getOAuth().setOAuthTokenKey(info.oauthTokenKey);
    m_TwitCurl.getOAuth().setOAuthTokenSecret(info.oauthTokenSecret);
}

void ofxTwitCurl::getAccountVerification(std::function<void(User)> callback)
{
    OPERATION_CHECK();
    std::future<User> fut = std::async(&ofxTwitCurl::accountVerifyCredGet, this);
    m_FuturesUserInfo.push_back(std::make_pair(std::move(fut), std::move(callback)));
}

void ofxTwitCurl::search(const string &query, const string &count, const twitCurlTypes::eTwitCurlResultType &resultType, std::function<void(Tweets)> callback)
{
    OPERATION_CHECK();
    std::future<Tweets> fut = std::async(&ofxTwitCurl::doSearch, this, query, count, resultType);
    m_FuturesTweets.push_back(std::make_pair(std::move(fut), std::move(callback)));
}

User ofxTwitCurl::accountVerifyCredGet()
{
    std::string response = "";
    if (m_TwitCurl.accountVerifyCredGet()) {
        m_TwitCurl.getLastWebResponse(response);

        ofxJSONElement json;
        json.parse(response);
        return ofxTwitCurlCreators::createUserInfo(json, true);
    }

    return User();
}

Tweets ofxTwitCurl::doSearch(const std::string &query, const std::string &count, const twitCurlTypes::eTwitCurlResultType &resultType)
{
    Tweets tweets;
    std::string response = "";
    if (m_TwitCurl.search(query, count, resultType)) {
        m_TwitCurl.getLastWebResponse(response);
    }
    else {
        m_TwitCurl.getLastCurlError(response);
        ofLogError("ofxTwitCurl") << __FUNCTION__ << ": " << response << "\n";
        return tweets;
    }

    ofxJSONElement json;
    json.parse(response);
    const ofxJSONElement statuses = json["statuses"];
    const unsigned int statusCount = statuses.size();
    for (unsigned int i = 0; i < statusCount; i++) {
        tweets.push_back(ofxTwitCurlCreators::createTweet(statuses[i], true, true));
    }

    return tweets;
}


