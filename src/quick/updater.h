#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "../network.h"

class Updater : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonObject words NOTIFY wordsChanged)

signals:
    void wordsChanged(QJsonObject);

public:
    explicit Updater(QObject *parent = nullptr);
    Q_INVOKABLE void getWords(QString url);

public slots:
    void parseData(QString);

private:
    Network net;
};

#endif // UPDATER_H
