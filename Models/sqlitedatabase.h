#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

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
    QString m_source;
    bool m_readonly;

public:
    explicit SQLiteDatabase(QObject *parent = 0);
    ~SQLiteDatabase();
    Q_INVOKABLE void executeQuery(QString queryString, QJSValue callbackFunction = QJSValue());
    Q_INVOKABLE void executeQueriesFromFile(QString path);
    Q_INVOKABLE void closeDatabase();
    QString source() const
    {
        return m_source;
    }

    bool readonly() const
    {
        return m_readonly;
    }

signals:

    void sourceChanged(QString arg);

    void readonlyChanged(bool arg);

    void databaseOpened();

public slots:

    void setSource(QString arg)
    {
        if (m_source != arg) {
            m_source = arg;
            emit sourceChanged(arg);
        }
    }
    void setReadonly(bool arg)
    {
        if (m_readonly != arg) {
            m_readonly = arg;
            emit readonlyChanged(arg);
        }
    }

private slots:
    void openDatabase(QString source);

private:
    QSqlDatabase m_database;
};

#endif // SQLITEDATABASE_H
