#ifndef STATS_H
#define STATS_H

#include <QObject>
#include "../types/stat.h"

class Stats : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonObject data READ GetScore WRITE SetScore NOTIFY scoreChanged)

signals:
    void scoreChanged(QJsonObject);
    void newStat();
    void reloadRequest();

public:
    explicit Stats(QObject *parent = nullptr);

public slots:
    void SetScore(QJsonObject);
    QJsonObject GetScore();

    void setStat(QJsonObject);
    void setStatistic(QList<Stat>);

private:
    Stat _userScore;
    QList<Stat> statistics;

};

#endif // STATS_H
