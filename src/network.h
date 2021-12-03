#pragma once

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class Network : public QObject
{
    Q_OBJECT
signals:
    void recived(QString data);

public:
    explicit Network(QObject *parent = nullptr);
    void get(QString);

public slots:
    void gotData(QNetworkReply*);

private:
    QNetworkAccessManager *mgr = new QNetworkAccessManager();

};
