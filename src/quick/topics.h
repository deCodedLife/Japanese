#ifndef TOPICS_H
#define TOPICS_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

#include "../types/topic.h"

class Topics : public QObject
{
    Q_OBJECT

public:
    explicit Topics(QObject *parent = nullptr);
    Q_INVOKABLE QJsonArray getTopics();

public slots:
    void UpdateTopics(QList<Topic>);

private:
    QList<Topic> _topics;
};

#endif // TOPICS_H
