#include "userdata.h"

UserData UserData::fromJson(QJsonObject obj)
{
    return {
        obj["id"].toInt(), obj["name"].toString(), obj["serverUri"].toString()
    };
}

QJsonObject UserData::toJson(UserData u)
{
    QJsonObject user;

    user["id"] = u.id;
    user["name"] = u.name;
    user["serverUri"] = u.serverUri;

    return user;
}
