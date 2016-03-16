#include "ofxTwitCurlCreators.h"

ofxTwitCurlCreators::ofxTwitCurlCreators()
{

}


User ofxTwitCurlCreators::createUserInfo(const ofxJSONElement &userJson, bool isConstructStatus)
{
    User user;

    user.isContributorsEnabled = userJson["contributors_enabled"].asBool();
    user.createdAt = userJson["created_at"].asString();
    user.isDefaultProfile = userJson["default_profile"].asBool();
    user.isDefaultProfilePicture = userJson["default_profile_image"].asBool();

    user.description = userJson["description"].asString();
    //TODO: Construct Entities

    user.favoritesCount = userJson["favorites_count"].asInt();
    user.isFollowRequestSent = userJson["follow_request_sent"].asBool();
    user.isFollowing = userJson["following"].asBool();
    user.followersCount = userJson["followers_count"].asInt();

    user.friendsCount = userJson["friends_count"].asInt();
    user.isGeoEnabled = userJson["geo_enabled"].asBool();
    user.id = userJson["id_str"].asString();
    user.isTranslator = userJson["is_translator"].asBool();

    user.lang = userJson["lang"].asString();
    user.listedCount = userJson["listed_count"].asInt();
    user.location = userJson["location"].asString();
    user.name = userJson["name"].asString();

    user.profileBackgroundColor = userJson["profile_background_color"].asString();
    user.profileBackgroundImageURL = userJson["profile_background_image_url"].asString();
    user.profileBackgroundImageURLHTTPS = userJson["profile_background_image_url_https"].asString();
    user.isProfileBackgroundImageTiled = userJson["profile_background_tile"].asBool();

    user.profileBannerURL = userJson["profile_banner_url"].asString();
    user.profileImageURL = userJson["profile_image_url"].asString();
    user.profileImageURLHTTPS = userJson["profile_image_url_https"].asString();
    user.profileLinkColor = userJson["profile_link_color"].asString();

    user.profileSidebarBorderColor = userJson["profile_sidebar_border_color"].asString();
    user.profileSidebarBorderFillColor = userJson["profile_sidebar_fill_color"].asString();
    user.profileTextColor = userJson["profile_text_color"].asString();
    user.isUseProfilebackgroundImage = userJson["profile_use_background_image"].asBool();

    user.isProtected = userJson["protected"].asBool();
    user.screenName = userJson["screen_name"].asString();
    user.isShowAllInlineMedia = userJson["show_all_inline_media"].asBool();
    if (isConstructStatus) {
        user.status = createTweet(userJson["status"], true, false);
    }

    user.statusesCount = userJson["statuses_count"].asInt();
    user.timeZone = userJson["time_zone"].asString();
    user.url = userJson["url"].asString();
    user.utcOffset = userJson["utc_offset"].asInt();

    user.isVerified = userJson["verified"].asBool();
    user.withheldInCountries = userJson["withheld_in_countries"].asString();
    user.withheldScope = userJson["withheld_scope"].asString();


    return user;
}

Tweet ofxTwitCurlCreators::createTweet(const ofxJSONElement &tweetJson, bool isConstructRetweet, bool isConstructUser)
{
    /* Omitted fields:
     * - annotations
     * - contributors
     * - coordinates
     * - current_user_retweet
     * - geo
     * - place
     * - quoted_status
     * - scopes
     */
    Tweet tweet;

    tweet.createdAt = tweetJson["created_at"].asString();
    tweet.favoriteCount = tweetJson["favorite_count"].asInt();
    tweet.isFavorited = tweetJson["favorited"].asBool();
    tweet.filterLevel = tweetJson["filter_level"].asString();

    tweet.id = tweetJson["id_str"].asString();
    tweet.inReplyToScreenName = tweetJson["in_reply_to_screen_name"].asString();
    tweet.inReplyToStatusID = tweetJson["in_reply_to_status_id_str"].asString();
    tweet.inReplyToUserID = tweetJson["in_reply_to_user_id_str"].asString();

    tweet.lang = tweetJson["lang"].asString();
    tweet.isPossiblySensitive = tweetJson["possibly_sensitive"].asBool();
    tweet.quotedStatusID = tweetJson["quoted_status_id_str"].asString();
    tweet.retweetCount = tweetJson["retweet_count"].asInt();

    tweet.isRetweeted = tweetJson["retweeted"].asBool();
    if (isConstructRetweet) {
        tweet.retweetStatus = createTweet(tweetJson["retweet_status"], false, true);
    }
    tweet.source = tweetJson["source"].asString();
    tweet.text = tweetJson["text"].asString();

    tweet.isTruncated = tweetJson["truncated"].asBool();
    if (isConstructUser) {
        tweet.user = createUserInfo(tweetJson["user"], false);
    }
    tweet.isWithheldCopyright = tweetJson["withheld_copyright"].asBool();
    tweet.withheldInCountries = getStringsFromArray(tweetJson["withheld_in_countries"]);

    tweet.withheldScope = tweetJson["withheld_scope"].asString();
    tweet.entities = ofxTwitCurlCreators::createEntities(tweetJson["entities"]);

    return tweet;
}

EntityMedia ofxTwitCurlCreators::createMediaEntity(const ofxJSONElement &mediaJson)
{
    EntityMedia media;

    media.id = mediaJson["id_str"].asString();
    media.mediaURL = mediaJson["media_url"].asString();
    media.mediaURLHTTPS = mediaJson["media_url_https"].asString();
    media.url = mediaJson["url"].asString();

    media.displayURL = mediaJson["display_url"].asString();
    media.expandedURL = mediaJson["expanded_url"].asString();
    media.type = mediaJson["type"].asString();
    media.indices = createIndices(mediaJson["indices"]);

    media.thumbSize = createMediaSize(mediaJson["sizes"]["thumb"]);
    media.smallSize = createMediaSize(mediaJson["sizes"]["small"]);
    media.mediumSize = createMediaSize(mediaJson["sizes"]["medium"]);
    media.largeSize = createMediaSize(mediaJson["sizes"]["large"]);

    return media;
}

EntityURL ofxTwitCurlCreators::createURLEntity(const ofxJSONElement &urlJson)
{
    EntityURL url;
    url.url = urlJson["url"].asString();
    url.displayURL = urlJson["display_url"].asString();
    url.expandedURL = urlJson["expanded_url"].asString();
    url.indices = createIndices(urlJson["indices"]);

    return url;
}

EntityUserMention ofxTwitCurlCreators::createUserMentionEntity(const ofxJSONElement &mentionJson)
{
    EntityUserMention mention;
    mention.id = mentionJson["id_str"].asString();
    mention.screenName = mentionJson["screen_name"].asString();
    mention.name = mentionJson["name"].asString();
    mention.indices = createIndices(mentionJson["indices"]);

    return mention;
}

EntityHashtag ofxTwitCurlCreators::createHashtagEntity(const ofxJSONElement &hashtagJson)
{
    EntityHashtag hashtag;
    hashtag.indicies = createIndices(hashtagJson["indices"]);
    hashtag.text = hashtagJson["text"].asString();
    return hashtag;
}

EntitySymbol ofxTwitCurlCreators::createSymbolEntity(const ofxJSONElement &symbolJson)
{
    EntitySymbol hashtag;
    hashtag.indicies = createIndices(symbolJson["indices"]);
    hashtag.text = symbolJson["text"].asString();
    return hashtag;
}

Entities ofxTwitCurlCreators::createEntities(const ofxJSONElement &entitiesjson)
{
    Entities entities;

    /* Media Entity */

    const ofxJSONElement &mediaJson = entitiesjson["media"];
    const unsigned int mediaCount = mediaJson.size();
    for (unsigned int mediaIndex = 0; mediaIndex < mediaCount; mediaIndex++) {
        entities.media.push_back(createMediaEntity(mediaJson[mediaIndex]));
    }

    /* URLS Entity */
    const ofxJSONElement &urlsJson = entitiesjson["urls"];
    const unsigned int urlsCount = urlsJson.size();
    for (unsigned int urlIndex = 0; urlIndex < urlsCount; urlIndex++) {
        entities.urls.push_back(createURLEntity(urlsJson[urlIndex]));
    }

    /* UserMentions Entity */
    const ofxJSONElement &mentionsJson = entitiesjson["user_mentions"];
    const unsigned int mentionsCount = mentionsJson.size();
    for (unsigned int mentionIndex = 0; mentionIndex < mentionsCount; mentionIndex++) {
        entities.userMentions.push_back(createUserMentionEntity(mentionsJson[mentionIndex]));
    }

    /* Hashtag Entity */
    const ofxJSONElement &hashtagsJson = entitiesjson["hashtags"];
    const unsigned int hashtagsCount = hashtagsJson.size();
    for (unsigned int hashtagIndex = 0; hashtagIndex < hashtagsCount; hashtagIndex++) {
        entities.hashtags.push_back(createHashtagEntity(hashtagsJson[hashtagIndex]));
    }

    /* Hashtag Entity */
    const ofxJSONElement &symbolsJson = entitiesjson["symbols"];
    const unsigned int symbolsCount = symbolsJson.size();
    for (unsigned int symbolIndex = 0; symbolIndex < symbolsCount; symbolIndex++) {
        entities.symbols.push_back(createSymbolEntity(symbolsJson[symbolIndex]));
    }

    return entities;
}

std::vector<std::string> ofxTwitCurlCreators::getStringsFromArray(const ofxJSONElement &elem)
{
    std::vector<std::string> elems;
    if (elem.isArray() == false) {
        return elems;
    }

    const unsigned int arraySize = elem.size();
    for (unsigned int i = 0; i < arraySize; i++) {
        elems.push_back(elem[i].asString());
    }

    return elems;
}

Indices ofxTwitCurlCreators::createIndices(const ofxJSONElement &indicesJson)
{
    Indices indices;
    if (indicesJson.isArray() == false) {
        return indices;
    }

    const unsigned int indexCount = indicesJson.size();
    for (unsigned int i = 0; i < indexCount; i++) {
        indices.push_back(indicesJson[i].asInt());
    }

    return indices;
}

EntityMediaSize ofxTwitCurlCreators::createMediaSize(const ofxJSONElement &sizeJson)
{
    EntityMediaSize size;
    size.height = sizeJson["h"].asInt();
    size.width = sizeJson["w"].asInt();
    size.resize = sizeJson["resize"].asString();
    return size;
}
