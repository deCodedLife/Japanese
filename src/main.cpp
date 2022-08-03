#include <QtQml>
#include <QQmlContext>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "database.h"
#include "quick/stats.h"
#include "quick/topics.h"
#include "quick/updater.h"
#include "quick/userinfo.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    Database *db = new Database();
    Updater *updater = new Updater();

    UserInfo *user = new UserInfo();
    Stats *stats = new Stats();

    Topics *topics = new Topics();

    QObject::connect(updater, &Updater::wordsChanged, db, &Database::addWords);

    QObject::connect(db, &Database::userLoaded, user, &UserInfo::setupData);
    QObject::connect(user, &UserInfo::userdataChanged, db, &Database::writeUserData);

    QObject::connect(stats, &Stats::scoreChanged, db, &Database::setNewScore);
    QObject::connect(stats, &Stats::newStat, db, &Database::createStat);
    QObject::connect(stats, &Stats::reloadRequest, db, &Database::loadStats);

    QObject::connect(db, &Database::statsLoaded, stats, &Stats::setStatistic);
    QObject::connect(db, &Database::statLoaded, stats, &Stats::setStat);

    QObject::connect(db, &Database::topicsLoaded, topics, &Topics::UpdateTopics);

    db->configure();

    QGuiApplication app(argc, argv);

    qmlRegisterType<Updater>("Updater", 1, 0, "Updater");
    qmlRegisterType<Database>("DB", 1, 0, "DB");
    qmlRegisterSingletonType(QUrl("qrc:/qml/Presets.qml"), "Presets", 1, 0, "Presets");
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    QQmlApplicationEngine engine;

    QQmlContext *ctx = engine.rootContext();
    ctx->setContextProperty("USERINFO", user);
    ctx->setContextProperty("STATS", stats);
    ctx->setContextProperty("DATABASE", db);
    ctx->setContextProperty("UPDATER", updater);
    ctx->setContextProperty("TOPICS", topics);
    bool turnedOn = true;
    ctx->setContextProperty("isProgressVisible", turnedOn);

    engine.load(url);

    if ( engine.rootObjects().isEmpty() )
    {
        return -1;
    }

    return app.exec();
}
