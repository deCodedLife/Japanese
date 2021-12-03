#pragma once

#include <QObject>
#include <QJsonObject>

struct Stat {
    int id;
    QString date;
    int score;

    static Stat fromJson(QJsonObject);
    static QJsonObject toJson(Stat);
};
