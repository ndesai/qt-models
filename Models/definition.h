#ifndef DEFINITION_H
#define DEFINITION_H
#include <QCoreApplication>
#include <QDir>
#define DEBUG if(0) qDebug() << __PRETTY_FUNCTION__
#ifdef Q_OS_IOS
#define BASEPATH QString(QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first() + QDir::separator())
#else
#define BASEPATH QString(QDir::homePath() + QDir::separator())
#endif
#define SQLITEDRIVER "QSQLITE"
#endif // DEFINITION_H
