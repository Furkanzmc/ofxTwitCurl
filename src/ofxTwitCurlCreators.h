#ifndef OFXTWITTERINITIALIZERS_H
#define OFXTWITTERINITIALIZERS_H
#include "ofxTwitCurlTypes.h"
#include "ofxJSON.h"

class ofxTwitCurlCreators
{
public:
    ofxTwitCurlCreators();

    static User createUserInfo(const ofxJSONElement &userJson, bool isConstructStatus);
    static Tweet createTweet(const ofxJSONElement &tweetJson, bool isConstructRetweet, bool isConstructUser);

    static EntityMedia createMediaEntity(const ofxJSONElement &mediaJson);
    static EntityURL createURLEntity(const ofxJSONElement &urlJson);
    static EntityUserMention createUserMentionEntity(const ofxJSONElement &mentionJson);
    static EntityHashtag createHashtagEntity(const ofxJSONElement &hashtagJson);
    static EntitySymbol createSymbolEntity(const ofxJSONElement &symbolJson);

    static Entities createEntities(const ofxJSONElement &entitiesjson);

    static std::vector<std::string> getStringsFromArray(const ofxJSONElement &elem);
    static Indices createIndices(const ofxJSONElement &indicesJson);

    static EntityMediaSize createMediaSize(const ofxJSONElement &sizeJson);
};

#endif // OFXTWITTERINITIALIZERS_H
