#include "models_plugin.h"
#include "myitem.h"
#include "sqlitedatabase.h"
#include <qqml.h>

void ModelsPlugin::registerTypes(const char *uri)
{
    // @uri st.app.models
    qmlRegisterType<SQLiteDatabase>(uri, 1, 0, "SQLiteDatabase");
}


