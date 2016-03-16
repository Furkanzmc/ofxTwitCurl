#ifndef OFXTWITTERTYPES_H
#define OFXTWITTERTYPES_H
#include <string>
#include <array>
#include <vector>

struct OAuthInfo {
    std::string consumerKey = "",
                consumerSecret = "",
                oauthTokenKey = "",
                oauthTokenSecret = "";
};

/** ---------- Entity Types Begin ---------- **/

using Indices = std::vector<unsigned int>;

struct EntityMediaSize {
    unsigned int width = 0, height = 0;
    std::string resize = "";
};

struct EntityMedia {
    std::string id = "",
                mediaURL = "",
                mediaURLHTTPS = "",
                url = "",
                displayURL = "",
                expandedURL = "",
                type = "";

    Indices indices;

    EntityMediaSize smallSize;
    EntityMediaSize mediumSize;
    EntityMediaSize largeSize;
    EntityMediaSize thumbSize;

};

struct EntityURL {
    std::string url = "",
                displayURL = "",
                expandedURL = "";

    Indices indices;
};

struct EntityUserMention {
    std::string id = "",
                screenName = "",
                name = "";

    Indices indices;
};

struct EntityHashtag {
    std::string text = "";
    Indices indicies;
};

struct EntitySymbol {
    std::string text = "";
    Indices indicies;
};

struct EntityVideoVariant {
    unsigned int bitrate = 0;
    std::string contentType = "", url = "";
};

struct EntityVideoInfo {
    std::pair<unsigned int, unsigned int> aspectRatio { 0, 0 };
    unsigned int duration = 0;

    std::vector<EntityVideoVariant> variants;
};

struct EntityExtended {
    std::string id = "",
                mediaURL = "",
                mediaURLHTTPS = "",
                url = "",
                displayURL = "",
                expandedURL = "",
                type = "";

    Indices indices;

    EntityMediaSize smallSize;
    EntityMediaSize mediumSize;
    EntityMediaSize largeSize;
    EntityMediaSize thumbSize;
};

struct Entities {
    std::vector<EntityMedia> media;
    std::vector<EntityURL> urls;
    std::vector<EntityUserMention> userMentions;
    std::vector<EntityHashtag> hashtags;
    std::vector<EntitySymbol> symbols;
    EntityExtended extendedEntity;
};

/** ---------- Entity Types End ---------- **/

/** ---------- Places Types Begin ---------- **/

struct PlaceAttributes {
    std::string streetAddess = "",
                locality = "",
                region = "",
                countryCode = "",
                postalCode = "",
                phone = "",
                twitter = "",
                url = "",
                id = "";
};

struct PlaceBoundingBox {
    std::vector<std::pair<float, float>> coordinates;
    std::string type = "";
};

struct Place {
    PlaceAttributes attributes;
    PlaceBoundingBox boundingBox;
    std::string country = "",
                countryCode = "",
                fullname = "",
                id = "",
                name = "",
                placeType = "",
                url = "";
};

/** ---------- Places Types End ---------- **/

/** ---------- User Types Begin ---------- **/

struct UserInfo {
    bool isContributorsEnabled = false,
         isDefaultProfile = false,
         isDefaultProfilePicture = false,
         isFollowRequestSent = false,
         isFollowing = false,
         isGeoEnabled = false,
         isTranslator = false,
         isProfileBackgroundImageTiled = false,
         isUseProfilebackgroundImage = false,
         isProtected = false,
         isShowAllInlineMedia = false,
         isVerified = false;

    std::string createdAt = "",
                description = "",
                id = "",
                lang = "",
                location = "",
                name = "",
                profileBackgroundColor = "",
                profileBackgroundImageURL = "",
                profileBackgroundImageURLHTTPS = "",
                profileBannerURL = "",
                profileImageURL = "",
                profileImageURLHTTPS = "",
                profileLinkColor = "",
                profileSidebarBorderColor = "",
                profileSidebarBorderFillColor = "",
                profileTextColor = "",
                screenName = "",
                timeZone = "",
                url = "",
                withheldInCountries = "",
                withheldScope = "";

    unsigned int favoritesCount = 0,
                 followersCount = 0,
                 friendsCount = 0,
                 listedCount = 0,
                 statusesCount = 0;
    int utcOffset = 0;

    Entities entities;
};

/** ---------- User Types End ---------- **/

/** ---------- Tweet Types Begin ---------- **/

struct TweetContributor {
    std::string id = "", screenName = "";
};

struct TweetInfo {
    std::pair<float, float> coordinates { 0.f, 0.f };
    std::string createdAt = "",
                id = "",
                inReplyToScreenName = "",
                source = "",
                text = "",
                inReplyToStatusID = "",
                inReplyToUserID = "",
                filterLevel = "",
                lang = "",
                quotedStatusID = "",
                withheldScope = "";

    std::vector<std::string> withheldInCountries;

    bool isFavorited = false,
         isTruncated = false,
         isRetweeted = false,
         isPossiblySensitive = false,
         isWithheldCopyright = false;

    unsigned int retweetCount = 0, favoriteCount = 0;

    Entities entities;
    Place place;
    UserInfo user;//User User
    std::vector<TweetContributor> contributors;
};

struct Tweet : public TweetInfo {
    TweetInfo retweetStatus;
};

/** ---------- Tweet Types End ---------- **/

struct User : public UserInfo {
    Tweet status;
};

using Tweets = std::vector<Tweet>;
using Users = std::vector<User>;

#endif // OFXTWITTERTYPES_H
