#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QJSValue>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QJSEngine>
#include <QStandardPaths>
#include "definition.h"
class SQLiteDatabase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool readonly READ readonly WRITE setReadonly NOTIFY readonlyChanged)
public:
    explicit SQLiteDatabase(QObject *parent = 0);
    ~SQLiteDatabase();
    Q_INVOKABLE void executeQuery(QString queryString, QJSValue callbackFunction = QJSValue());
    Q_INVOKABLE void executeQueriesFromFile(QString path);
    Q_INVOKABLE void closeDatabase();
    QString source() const;
    bool readonly() const;

signals:
    void sourceChanged(QString arg);
    void readonlyChanged(bool arg);
    void databaseOpened();

public slots:
    void setSource(QString arg);
    void setReadonly(bool arg);

private slots:
    void openDatabase();

private:
    QSqlDatabase m_database;
    QString m_source;
    bool m_readonly;
};
