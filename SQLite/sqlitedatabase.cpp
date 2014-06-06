#include "sqlitedatabase.h"

SQLiteDatabase::SQLiteDatabase(QObject *parent) :
    QObject(parent),
    m_source(""),
    m_readonly(false),
    m_database(QSqlDatabase())
{
    QObject::connect(this, SIGNAL(sourceChanged(QString)),
                     this, SLOT(openDatabase(QString)));
}

SQLiteDatabase::~SQLiteDatabase()
{
    m_database.close();
}

void SQLiteDatabase::openDatabase(QString source)
{
    if(source.isEmpty())
    {
        DEBUG << "source is empty";
        return;
    }
    if(!m_database.isDriverAvailable(SQLITEDRIVER))
    {
        DEBUG << SQLITEDRIVER << "is not available";
        return;
    }
    QString fullPath = BASEPATH + source;
    bool fullPathExists = QFile(fullPath).exists();
    if(m_readonly && !fullPathExists)
    {
        DEBUG << fullPath;
        DEBUG << "db doesn't exist. cannot continue with readonly as there is nothing to read";
        return;
    }
    if(!fullPathExists)
    {
        DEBUG << fullPath;
        DEBUG << "db doesn't exist. creating..";
    }
    m_database = QSqlDatabase::addDatabase(SQLITEDRIVER);
    m_database.setDatabaseName(fullPath);
    if(!m_database.isValid())
    {
        DEBUG << SQLITEDRIVER << "database is not valid";
        return;
    }
    m_database.open();
    if(m_database.isOpen())
    {
        DEBUG << "database is open";
    }
    else
    {
        DEBUG << "database is not open";
    }
}

void SQLiteDatabase::executeQuery(QString queryString, QJSValue callbackFunction)
{
    DEBUG << queryString;
    QSqlQuery query(m_database);
    query.prepare(queryString);
    bool status;
    QJSEngine *jsEngine = callbackFunction.engine();
    QJSValue resultsList = jsEngine->newArray();
    if (!query.exec())
    {
        DEBUG << "query failed" << query.lastError().text();
        status = false;
    }
    else
    {
        DEBUG << "query successful";
        status = true;
        int index = 0;
        while (query.next())
        {
            QSqlRecord rec = query.record();
            QJSValue obj = jsEngine->newObject();
            for(int col = 0; col < rec.count(); col++) // iterate columns
            {
                QString mapValue = query.value(col).toString();
                obj.setProperty(rec.fieldName(col), mapValue);
            }
            resultsList.setProperty(index++, obj);
        }
    }
    if(callbackFunction.isCallable())
    {
        QJSValueList valueList;
        valueList.append(queryString);
        valueList.append(status);
        valueList.append(resultsList);
        callbackFunction.call(valueList);
    }
}

