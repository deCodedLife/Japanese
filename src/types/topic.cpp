#include "topic.h"

Topic Topic::fromJson(QJsonObject data)
{
    return {
        data["id"].toInt(), data["topic"].toString()
    };
}

QJsonObject Topic::toJson(Topic topic)
{
    QJsonObject output;

    output["id"] = topic.id;
    output["topic"] = topic.name;

    return output;
}
