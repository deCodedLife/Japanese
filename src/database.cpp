#include "database.h"

Database::Database(QObject *parent) : QObject(parent)
{
    type = DATABASE_WORDS;
    db.setDatabaseName("data.bin");    
}

void Database::configure()
{
    initDatabase();
    loadStats();
    loadUserData();
}

void Database::addWord(QJsonObject w)
{
    Word newWord;

    newWord.id = -1;
    parseWord(&newWord, w);

    if ( newWord.id == -1 )
    {
        qDebug() << "[ERROR] Can't add new word. Reason: error dataset";
        return;
    }

    if ( db.open() == false )
    {
        qDebug() << "[ERROR] Can't add new word: Can't open database. Error: " << db.lastError();
        return;
    }

    QSqlQuery query;

    query.prepare("insert into Words (ja, ru, pt) values(:ja, :ru, :pt)");
    query.bindValue(":ja", newWord.ja);
    query.bindValue(":ru", newWord.ru);
    query.bindValue(":pt", newWord.pr);

    query.exec();
    db.close();
}

QJsonArray Database::getWords()
{
    QSqlQuery query;
    QJsonArray words;

    if ( db.open() == false )
    {
        qDebug() << "[ERROR] Can't read words cause can't open database. Error: " << db.lastError();
        return words;
    }

    query.prepare("select * from words");
    query.exec();

    while( query.next() )
    {
        QJsonObject word;

        word["id"] = query.value(0).toInt();
        word["ja"] = query.value(1).toString();
        word["ru"] = query.value(2).toString();
        word["pr"] = query.value(3).toString();

        words.append( word );
    }

    return words;
}

void Database::SetDatabase(QString d)
{
    _dbName = d + ".bin";
    type = parseDB(d);

    emit databaseChanged(d);
}

QString Database::GetDatabase()
{
    return _dbName;
}

void Database::addWords(QJsonObject words)
{
    if ( db.open() == false )
    {
        qDebug() << "[ERROR] Can't update db cause: " << db.lastError();
    }

    QSqlQuery query;

    for ( QJsonValue word : words["words"].toArray() )
    {
        qDebug() << "Current word: " << word;
        if ( rowExist( word["id"].toInt() ) == false )
        {
            query.prepare("insert into Words (id, ja, ru, pr) values (:id, :ja, :ru, :pr)");
            query.bindValue(":id", word["id"].toInt());
            query.bindValue(":ja", word["ja"].toString());
            query.bindValue(":ru", word["ru"].toString());
            query.bindValue(":pr", word["pr"].toString());
            query.exec();
        }
    }

    db.close();
}

void Database::loadUserData()
{
    if ( db.open() == false )
    {
        qDebug() << "[ERROR] Can't init db cause: " << db.lastError();
        return;
    }

    UserData _userData;
    QSqlQuery query;
    query.prepare("select * from User");
    query.exec();

    if ( query.next() )
    {
        _userData.id = query.value(0).toInt();
        _userData.name = query.value(1).toString();
        _userData.serverUri = query.value(2).toString();
    }
    else
    {
        _userData.id = 0;
        _userData.name = "みんな";
        _userData.serverUri = "https://coded.life/jp";

        createNewUser( _userData );
    }

    emit userLoaded( UserData::toJson(_userData) );
    db.close();
}

void Database::loadStats()
{
    if ( db.open() == false )
    {
        qDebug() << "[ERROR] Can't load stats cause: " << db.lastError();
        return;
    }

    QList<Stat> statistics;
    QSqlQuery query;
    query.prepare("select * from Stats");
    query.exec();

    while ( query.next() )
    {
        Stat temp;

        temp.id = query.value(0).toInt();
        temp.date = query.value(1).toString();
        temp.score = query.value(2).toInt();

        statistics.append( temp );
    }

    if ( statistics.isEmpty() )
    {
        createStat();

        Stat temp;
        temp.id = 1;
        temp.date = QDate::currentDate().toString("yyyy.MM.dd");
        temp.score = 0;

        statistics.append(temp);
    }

    emit statsLoaded(statistics);    
    db.close();
}

void Database::createStat()
{
    if ( db.open() == false )
    {
        qDebug() << "[ERROR] Can't add stat cause: " << db.lastError();
        return;
    }

    QSqlQuery query;

    query.prepare("insert into Stats (date, score) values (:date, 0)");
    query.bindValue(":date", QDate::currentDate().toString("yyyy.MM.dd"));
    query.exec();

    db.close();
}

void Database::setNewScore(QJsonObject s)
{
    if ( db.open() == false )
    {
        qDebug() << "[ERROR] Can't update score data cause: " << db.lastError();
        return;
    }

    QSqlQuery query;
    Stat newScore = Stat::fromJson(s);

    query.prepare("update Stats set score = :score where id = :id");
    query.bindValue(":score", newScore.score);
    query.bindValue(":id", newScore.id);

    query.exec();

    db.close();
}

void Database::createNewUser(UserData data)
{
    if ( db.open() == false )
    {
        qDebug() << "[ERROR] Can't create user cause: " << db.lastError();
        return;
    }

    QSqlQuery query;

    query.prepare("insert into User (name, serverUri) values (:name, :serverUri)");
    query.bindValue(":name", data.name);
    query.bindValue(":serverUri", data.serverUri);
    query.exec();

    db.close();
}

void Database::writeUserData(QJsonObject u)
{
    if ( db.open() == false )
    {
        qDebug() << "[ERROR] Can't update userData cause: " << db.lastError();
        return;
    }

    QSqlQuery query;
    UserData data = UserData::fromJson(u);

    query.prepare("update User set id = :id, name = :name, serverUri = :serverUri");
    query.bindValue(":id", data.id);
    query.bindValue(":name", data.name);
    query.bindValue(":serverUri", data.serverUri);

    query.exec();

    db.close();
}

void Database::initDatabase()
{
    if ( db.open() == false )
    {
        qDebug() << "[ERROR] Can't init db cause: " << db.lastError();
        return;
    }

    QSqlQuery query;

    query.prepare(CREATE_DB_WORDS);
    query.exec();

    query.prepare(CREATE_DB_USER);
    query.exec();

    query.prepare(CREATE_DB_STATS);
    query.exec();

    query.prepare(CREATE_DB_TESTS);
    query.exec();

    query.prepare(CREATE_DB_SELECTIONS);
    query.exec();

    db.close();
}

bool Database::rowExist(int id)
{
    QSqlQuery query;

    query.prepare("select id from Words where id = :id");
    query.bindValue(":id", id);
    query.exec();

    return query.next();
}

DBTYPES parseDB(QString type)
{
    if ( type == "words" )
    {
        return DATABASE_WORDS;
    }

    return DATABASE_NONE;
}

