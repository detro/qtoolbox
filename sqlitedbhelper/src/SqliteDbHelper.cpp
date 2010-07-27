#include "SqliteDbHelper.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QFile>
#include <QSqlDriver>
#include <QStringList>

#include "utility/macros.h"

#define VERSION_UNAVAILABLE -1

#define INFO_TABLE_CREATE           "CREATE TABLE IF NOT EXISTS _db_helper_info_ ( version INTEGER NOT NULL, creation_date INTEGER DEFAULT (datetime('now')) )"
#define TABLE_DROP                  "DROP TABLE IF EXISTS %1"
#define INFO_TABLE_INSERT_VERSION   "INSERT INTO _db_helper_info_ (version) VALUES (?)"
#define INFO_TABLE_SELECT_VERSION   "SELECT version FROM _db_helper_info_"

SqliteDbHelper::SqliteDbHelper(const QString &filePath, const int version, const QString &defaultConnName) :
      m_currVersion(VERSION_UNAVAILABLE),
      m_created(true)
{
   m_database = QSqlDatabase::addDatabase("QSQLITE", defaultConnName);
   m_database.setDatabaseName(filePath);
   if ( m_database.isValid() && m_database.open() ) {
      if ( dbVersion() == VERSION_UNAVAILABLE ) {
         QDEBUG_EXP("SqliteDBHelper::SqliteDBHelper()", "Creating DB: " << m_database.databaseName());
         setDbVersion(version);  //< Set the DB version
         m_created = false;
      } else if ( dbVersion() != version ) {
         QDEBUG_EXP("SqliteDBHelper::SqliteDBHelper()", "Updating DB: " << m_database.databaseName() << " - From version " << dbVersion() << " to version " << version);
         dropTables();           //< Drop all the old-version Tables
         setDbVersion(version);  //< Set the DB version
         m_created = false;
      }
      QDEBUG_EXP("SqliteDBHelper::SqliteDBHelper()", "DB: " << m_database.databaseName() << " - Ready!");
   } else {
      QDEBUG_EXP("SqliteDBHelper::SqliteDBHelper()", "DB: " << m_database.databaseName() << " - " << m_database.lastError().text());
      QWARNING_EXP("SqliteDBHelper::SqliteDBHelper()", "Couldn't open the Database");
   }

   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support Transactions? " << m_database.driver()->hasFeature(QSqlDriver::Transactions));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support QuerySize? " << m_database.driver()->hasFeature(QSqlDriver::QuerySize));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support BLOB? " << m_database.driver()->hasFeature(QSqlDriver::BLOB));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support Unicode? " << m_database.driver()->hasFeature(QSqlDriver::Unicode));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support PreparedQueries? " << m_database.driver()->hasFeature(QSqlDriver::PreparedQueries));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support NamedPlaceholders? " << m_database.driver()->hasFeature(QSqlDriver::NamedPlaceholders));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support PositionalPlaceholders? " << m_database.driver()->hasFeature(QSqlDriver::PositionalPlaceholders));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support LastInsertId? " << m_database.driver()->hasFeature(QSqlDriver::LastInsertId));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support BatchOperations? " << m_database.driver()->hasFeature(QSqlDriver::BatchOperations));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support SimpleLocking? " << m_database.driver()->hasFeature(QSqlDriver::SimpleLocking));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support LowPrecisionNumbers? " << m_database.driver()->hasFeature(QSqlDriver::LowPrecisionNumbers));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support EventNotifications? " << m_database.driver()->hasFeature(QSqlDriver::EventNotifications));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support FinishQuery? " << m_database.driver()->hasFeature(QSqlDriver::FinishQuery));
   QVERBOSE_EXP("SqliteDbHelper::SqliteDbHelper()", "Support MultipleResultSets? " << m_database.driver()->hasFeature(QSqlDriver::MultipleResultSets));
}

SqliteDbHelper::~SqliteDbHelper() {
   QDEBUG("SqliteDbHelper::~SqliteDbHelper()");
   if ( m_database.isOpen() )
      m_database.close();
}

// public:
QSqlDatabase SqliteDbHelper::open() {
   checkIsCreated(); //< Create the DB tables if not already there
   return m_database;
}

QSqlDatabase SqliteDbHelper::open(const QString &alternativeConnName) {
   checkIsCreated(); //< Create the DB tables if not already there
   QSqlDatabase newConn = QSqlDatabase::database(alternativeConnName, true);
   if ( !newConn.isValid() ) {
      newConn = QSqlDatabase::addDatabase("QSQLITE", alternativeConnName);
      newConn.setDatabaseName(m_database.databaseName());
      if ( !newConn.isValid() || !newConn.open() ) {
         QDEBUG_EXP("SqliteDBHelper::open(...)", "Alternative Connection Name: " << alternativeConnName);
         QWARNING_EXP("SqliteDBHelper::open(...)", "Couldn't open a Connection with Alternative Name");
      }
   }
   return newConn;
}

// private:
void SqliteDbHelper::setDbVersion(const int version) {
   m_database.transaction();        //< TRANSACTION START
   QSqlQuery query(m_database);
   query.exec(INFO_TABLE_CREATE);
   query.prepare(INFO_TABLE_INSERT_VERSION);
   query.bindValue(0, version);
   query.exec();

   if ( !m_database.commit() ) {    //< TRANSACTION COMMIT
      QDEBUG_EXP("SqliteDBHelper::setDbVersion()", "DB: " << m_database.databaseName() << " - " << query.lastError().text());
      QDEBUG_EXP("SqliteDBHelper::setDbVersion()", "Last Query: " << query.lastQuery());
      QWARNING_EXP("SqliteDBHelper::setDbVersion()", "Couldn't add the _db_helper_info_ table");
   } else {
      m_currVersion = version;
   }
}

int SqliteDbHelper::dbVersion() {
   if ( m_currVersion == VERSION_UNAVAILABLE ) {
      QSqlQuery query(m_database);
      if ( query.exec(INFO_TABLE_SELECT_VERSION) ) { //< Try to query for Curr. Version
         if ( query.size() != 1 ) {
            query.first();
            m_currVersion = query.value(0).toInt();
            QDEBUG_EXP("SqliteDBHelper::dbVersion()", "Current Version of DB: " << m_database.databaseName() << " is: " << m_currVersion);
         } else {
            QWARNING_EXP("SqliteDBHelper::dbVersion()", "More then 1 DB version? Something went wrong here!");
         }
      } else {
         if ( query.lastError().type() != QSqlError::StatementError ) {
            QWARNING_EXP("SqliteDBHelper::dbVersion()",
               "Couldn't fetch the DB Version - "
               << "DB:" << m_database.databaseName()
               << " - " << query.lastError().text()
               );
         }
      }
   }
   return m_currVersion;
}

void SqliteDbHelper::checkIsCreated() {
   if ( !m_created ) {
      onCreate(m_database);
      m_created = true;
   }
}

void SqliteDbHelper::dropTables() {
   QStringList tables = m_database.tables(QSql::Tables);
   m_database.transaction();        //< TRANSACTION START

   QSqlQuery query(m_database);
   QString tableDropStr(TABLE_DROP);
   for ( QStringList::iterator i = tables.begin(); i != tables.end(); ++i) {
      QDEBUG_EXP("SqliteDbHelper::dropTables()", "Dropping Table: " << *i);
      if ( !query.exec(tableDropStr.arg(*i)) ) {
         QWARNING_EXP("SqliteDbHelper::dropTables()", "Unable to DROP TABLE " << *i << " - Error: " << query.lastError().text());
      }
   }

   if ( !m_database.commit() ) {    //< TRANSACTION COMMIT
      QWARNING_EXP("SqliteDbHelper::dropTables()", "Couldn't DROP TABLES. " << m_database.lastError().text());
   }
}
