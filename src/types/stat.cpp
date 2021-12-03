#include "stat.h"

Stat Stat::fromJson(QJsonObject s)
{
    return {
        s["id"].toInt(), s["date"].toString(), s["score"].toInt()
    };
}

QJsonObject Stat::toJson(Stat s)
{
    QJsonObject score;

    score["id"] = s.id;
    score["date"] = s.date;
    score["score"] = s.score;

    return score;
}
