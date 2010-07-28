#include "SqliteDbHelperExample.h"

#include "macros.h"

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
