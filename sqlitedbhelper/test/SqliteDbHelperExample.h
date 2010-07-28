#ifndef SQLITEDBHELPEREXAMPLE_H
#define SQLITEDBHELPEREXAMPLE_H

#include "SqliteDbHelper.h"

using namespace QTB;

#define DB_NAME            "sqlite_db_helper_test.db"
#define TEST_TABLE         "account"
#define CREATE_TEST_TABLE  "CREATE TABLE IF NOT EXISTS " \
      "account ( " \
         "age INTEGER NOT NULL, " \
         "name TEXT NOT NULL, " \
         "id INTEGER PRIMARY KEY, " \
         "UNIQUE (name)" \
      ")"

class SqliteDbHelperExample : public SqliteDbHelper
{
public:
    SqliteDbHelperExample(const int requestedVersion);

protected:
    virtual void onCreate(QSqlDatabase &database);
};

#endif // SQLITEDBHELPEREXAMPLE_H
