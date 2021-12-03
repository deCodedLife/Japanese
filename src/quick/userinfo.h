#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>
#include "../types/userdata.h"

class UserInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonObject data READ GetUserData WRITE SetUserData NOTIFY userdataChanged)

signals:
    void userdataChanged(QJsonObject);

public:
    explicit UserInfo(QObject *parent = nullptr);

public slots:
    void SetUserData(QJsonObject);
    QJsonObject GetUserData();

    void setupData(QJsonObject);

private:
    UserData _userData;

};

#endif // USERINFO_H
