#include "network.h"

Network::Network(QObject *parent) : QObject(parent)
{
    connect(mgr, &QNetworkAccessManager::finished, this, &Network::gotData);
}

void Network::get(QString url)
{
    QNetworkRequest newRequest;
    newRequest.setUrl( QUrl(url) );
    mgr->get(newRequest);
}

void Network::gotData(QNetworkReply *rpl)
{
    emit recived(rpl->readAll());
}
