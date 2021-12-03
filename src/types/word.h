#pragma once

#include <QObject>
#include <QJsonObject>

struct Word {
    int id;
    QString ja;
    QString ru;
    QString pr;
};

void parseWord(Word*, QJsonObject);
