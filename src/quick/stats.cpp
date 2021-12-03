#include "stats.h"

Stats::Stats(QObject *parent) : QObject(parent)
{
}

void Stats::SetScore(QJsonObject s)
{
    _userScore = Stat::fromJson(s);
    emit scoreChanged( s );
}

QJsonObject Stats::GetScore()
{
    return Stat::toJson( _userScore );
}

void Stats::setStat(QJsonObject s)
{
    SetScore( s );
}

void Stats::setStatistic(QList<Stat> s)
{
    statistics = s;

    if ( s.last().date != QDate::currentDate().toString("yyyy.MM.dd") )
    {
        emit newStat();

        Stat temp;
        temp.id = 1;
        temp.date = QDate::currentDate().toString("yyyy.MM.dd");
        temp.score = 0;

        statistics.append(temp);
        SetScore( Stat::toJson(s.last()) );
        emit reloadRequest();
    } else
    {
        SetScore( Stat::toJson(s.last()) );
    }
}
