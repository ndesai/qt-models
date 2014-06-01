#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQmlContext>
#include "sqlitedatabase.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<SQLiteDatabase>("st.app", 1, 0, "SQLiteDatabase");
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
