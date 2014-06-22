#ifndef DEFINITION_H
#define DEFINITION_H
#include <QCoreApplication>
#include <QDir>
#define DEBUG if(1) qDebug() << __PRETTY_FUNCTION__
#ifdef Q_OS_IOS
#define BASEPATH QString(QStandardPaths::standardLocations(QStandardPaths::DataLocation).first() + QDir::separator())
#else
#define BASEPATH QString(QDir::homePath() + QDir::separator())
#endif
#define SQLITEDRIVER "QSQLITE"
#endif // DEFINITION_H