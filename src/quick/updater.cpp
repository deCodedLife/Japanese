#include "updater.h"

Updater::Updater(QObject *parent) : QObject(parent)
{
    connect(&net, &Network::recived, this, &Updater::parseData);
}

void Updater::getWords(QString url)
{
    net.get(url);
}

void Updater::parseData(QString data)
{
    if ( data.isEmpty() )
    {
        return;
    }

    QJsonObject wordsArray = QJsonDocument::fromJson( data.toUtf8() ).object();

    if ( wordsArray.isEmpty() )
    {
        return;
    }

    emit wordsChanged( wordsArray );
}
