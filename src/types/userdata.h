#pragma once

#include <QString>
#include <QJsonObject>

struct UserData {
    int id;
    QString name;
    QString serverUri;

    static QJsonObject toJson(UserData);
    static UserData fromJson(QJsonObject);
};

