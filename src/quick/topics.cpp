#include "topics.h"

Topics::Topics(QObject *parent) : QObject(parent)
{
}

QJsonArray Topics::getTopics()
{
    QJsonArray topics;

    for (Topic t : _topics)
    {
        topics.append( Topic::toJson(t) );
    }

    return topics;
}

void Topics::UpdateTopics(QList<Topic> t)
{

    _topics = t;
}
