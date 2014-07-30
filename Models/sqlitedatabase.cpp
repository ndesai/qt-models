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
        DEBUG << "last insert id " << query.lastInsertId();
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
        valueList.append(query.lastInsertId().toString());
        callbackFunction.call(valueList);
    }
    query.clear();
}

/**
* @brief executeQueriesFromFile Read each line from a .sql QFile
* (assumed to not have been opened before this function), and when ; is reached, execute
* the SQL gathered until then on the query object. Then do this until a COMMIT SQL
* statement is found. In other words, this function assumes each file is a single
* SQL transaction, ending with a COMMIT line.
*
* https://gist.github.com/savolai/6852986
*/

void SQLiteDatabase::executeQueriesFromFile(QString path)
{
    DEBUG << path;
    QFile *file = new QFile(path);
    if(file->exists()
            && !file->open(QFile::ReadOnly | QFile::Text))
    {
        DEBUG << "file could not be opened at path = " << path;
        return;
    }
    QSqlQuery query(m_database);
    while (!file->atEnd())
    {
        QByteArray readLine = "";
        QString cleanedLine;
        QString line = "";

        bool finished = false;

        while(!finished)
        {
            readLine = file->readLine();
            DEBUG << readLine;
            cleanedLine = readLine.trimmed();
            QStringList strings = cleanedLine.split("--");
            cleanedLine = strings.at(0);
            if(!cleanedLine.startsWith("--")
                    && !cleanedLine.startsWith("DROP")
                    && !cleanedLine.isEmpty())
            {
                line += cleanedLine;
            }
            if(cleanedLine.endsWith(";"))
            {
                break;
            }
            if(cleanedLine.startsWith("COMMIT"))
            {
                finished = true;
            }
        }

        if(!line.isEmpty())
        {
            query.exec(line);
        }
        if(!query.isActive())
        {
            DEBUG << QSqlDatabase::drivers();
            DEBUG << query.lastError();
            DEBUG << "Executed query:"<< query.executedQuery();
            DEBUG << "Last query:"<< query.lastQuery();
        }
    }
}


