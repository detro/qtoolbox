#include "SqliteDbHelperExample.h"

#include "macros.h"

#include "activelogs.h"
#ifdef SQLITE_DB_HELPER_EXAMPLE
    #define ENABLE_LOG_MACROS
#endif
#include "logmacros.h"

SqliteDbHelperExample::SqliteDbHelperExample(const int requestedVersion)
   : SqliteDbHelper(DB_NAME, requestedVersion)
{
}


// protected:
void SqliteDbHelperExample::onCreate(QSqlDatabase &database) {
   database.transaction();
   QSqlQuery query(database);
   if ( !query.exec(CREATE_TEST_TABLE) ) {
      WARNING(query.lastError().text());
   }
   if ( !database.commit() ) {
      DEBUG("Couldn't create tables - DB: " << database.databaseName() << " - Error: " << query.lastError().text());
   }
}
