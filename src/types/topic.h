#pragma once

#include <QObject>
#include <QJsonObject>

struct Topic
{
    int id;
    QString name;

    static Topic fromJson(QJsonObject);
    static QJsonObject toJson(Topic);
};
