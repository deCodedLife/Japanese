#include "userinfo.h"

UserInfo::UserInfo(QObject *parent) : QObject(parent)
{

}

void UserInfo::SetUserData(QJsonObject u)
{
    _userData = UserData::fromJson(u);
    emit userdataChanged( UserData::toJson( _userData ) );
}

QJsonObject UserInfo::GetUserData()
{
    return UserData::toJson( _userData );
}

void UserInfo::setupData(QJsonObject u)
{
    SetUserData( u );
}
