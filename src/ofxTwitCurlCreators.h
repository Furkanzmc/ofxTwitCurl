#ifndef OFXTWITTERINITIALIZERS_H
#define OFXTWITTERINITIALIZERS_H
#include "ofxTwitCurlTypes.h"
#include "ofxJSON.h"

class ofxTwitCurlCreators
{
public:
    ofxTwitCurlCreators();

    static ofxTwitCurlTypes::User createUserInfo(const ofxJSONElement &userJson, bool isConstructStatus);
    static ofxTwitCurlTypes::Tweet createTweet(const ofxJSONElement &tweetJson, bool isConstructRetweet, bool isConstructUser);

    static ofxTwitCurlTypes::EntityMedia createMediaEntity(const ofxJSONElement &mediaJson);
    static ofxTwitCurlTypes::EntityURL createURLEntity(const ofxJSONElement &urlJson);
    static ofxTwitCurlTypes::EntityUserMention createUserMentionEntity(const ofxJSONElement &mentionJson);
    static ofxTwitCurlTypes::EntityHashtag createHashtagEntity(const ofxJSONElement &hashtagJson);
    static ofxTwitCurlTypes::EntitySymbol createSymbolEntity(const ofxJSONElement &symbolJson);

    static ofxTwitCurlTypes::Entities createEntities(const ofxJSONElement &entitiesjson);

    static std::vector<std::string> getStringsFromArray(const ofxJSONElement &elem);
    static ofxTwitCurlTypes::Indices createIndices(const ofxJSONElement &indicesJson);

    static ofxTwitCurlTypes::EntityMediaSize createMediaSize(const ofxJSONElement &sizeJson);
};

#endif // OFXTWITTERINITIALIZERS_H
