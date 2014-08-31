#include "models_plugin.h"
#include "myitem.h"
#include "sqlitedatabase.h"
#include <qqml.h>
#define QT_NO_DEBUG_OUTPUT 1
void ModelsPlugin::registerTypes(const char *uri)
{
    // @uri st.app.models
    qmlRegisterType<SQLiteDatabase>(uri, 1, 0, "SQLiteDatabase");
}


