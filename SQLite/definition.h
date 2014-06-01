#ifndef DEFINITION_H
#define DEFINITION_H
#include <QCoreApplication>
#include <QDir>
#define DEBUG if(1) qDebug() << __PRETTY_FUNCTION__
#define BASEPATH QString(QDir::homePath() + QDir::separator())
#define SQLITEDRIVER "QSQLITE"
#endif // DEFINITION_H
