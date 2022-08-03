#pragma once

#include <QSql>
#include <QtSql>
#include <QObject>
#include <QJsonArray>

#include "types/word.h"
#include "types/stat.h"
#include "types/topic.h"
#include "types/userdata.h"

#define CREATE_DB_WORDS "create table if not exists Words (id INTEGER NOT NULL UNIQUE, ja TEXT NOT NULL, ru TEXT NOT NULL, pr TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT) )"
#define CREATE_DB_USER "create table if not exists User (id INTEGER NOT NULL UNIQUE, name TEXT NOT NULL, serverUri TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT) )"
#define CREATE_DB_STATS "create table if not exists Stats (id INTEGER NOT NULL UNIQUE, date TEXT NOT NULL, score TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT) )"
#define CREATE_DB_TESTS "create table if not exists Tests (id INTEGER NOT NULL UNIQUE, content TEXT NOT NULL, insertations TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT) )"
#define CREATE_DB_SELECTIONS "create table if not exists Selections (id INTEGER NOT NULL UNIQUE, question TEXT NOT NULL, variants TEXT NOT NULL, answer TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT) )"
#define CREATE_DB_TOPICS "create table if not exists Topics (id INTEGER NOT NULL UNIQUE, topic TEXT NOT NULL, PRIMARY KEY (id AUTOINCREMENT) )"

typedef enum {
    DATABASE_NONE,
    DATABASE_WORDS,
    DATABASE_USERDATA
} DBTYPES;

DBTYPES parseDB(QString);

class Database : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ GetDatabase WRITE SetDatabase NOTIFY databaseChanged)

signals:
    void databaseChanged(QString);
    void statsLoaded(QList<Stat>);
    void statLoaded(QJsonObject);
    void userLoaded(QJsonObject);
    void topicsLoaded(QList<Topic>);

public:
    explicit Database(QObject *parent = nullptr);
    void configure();

    Q_INVOKABLE QJsonArray getWords();
    Q_INVOKABLE void addWord(QJsonObject);

    void SetDatabase(QString);
    QString GetDatabase();

public slots:
    void addWords(QJsonObject);

    void loadUserData();
    void loadStats();
    void loadTopics();

    void createStat();
    void setNewScore(QJsonObject);
    void createNewUser(UserData);
    void writeUserData(QJsonObject);

private:

    void initDatabase();
    bool rowExist(int id);

    DBTYPES type;
    QString _dbName;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;

};
