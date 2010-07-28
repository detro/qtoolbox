#include "SqliteDbHelper.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QFile>
#include <QSqlDriver>
#include <QStringList>

QTB_BEGIN_NAMESPACE

#define SQLITE_DRIVER_NAME          "QSQLITE"
#define VERSION_UNAVAILABLE         -1

#define INFO_TABLE_CREATE           "CREATE TABLE IF NOT EXISTS _db_helper_info_ ( version INTEGER NOT NULL, creation_date INTEGER DEFAULT (datetime('now')) )"
#define TABLE_DROP                  "DROP TABLE IF EXISTS %1"
#define INFO_TABLE_INSERT_VERSION   "INSERT INTO _db_helper_info_ (version) VALUES (?)"
#define INFO_TABLE_SELECT_VERSION   "SELECT version FROM _db_helper_info_"

SqliteDbHelper::SqliteDbHelper(const QString &filePath, const int version, const QString &defaultConnName) :
      m_currVersion(VERSION_UNAVAILABLE),
      m_created(true)
{
   m_database = QSqlDatabase::addDatabase(SQLITE_DRIVER_NAME, defaultConnName);
   m_database.setDatabaseName(filePath);
   if ( m_database.isValid() && m_database.open() ) {
      if ( dbVersion() == VERSION_UNAVAILABLE ) {
         DEBUG("Creating DB: " << m_database.databaseName());
         setDbVersion(version);     //< Set the DB version
         m_created = false;
      } else if ( dbVersion() != version ) {
         DEBUG("Updating DB: " << m_database.databaseName() << " - From version " << dbVersion() << " to version " << version);
         dropTables();              //< Drop all the old-version Tables
         setDbVersion(version);     //< Set the DB version
         m_created = false;
      }
      DEBUG("DB: " << m_database.databaseName() << " is now Ready!");
   } else {
      WARNING("Couldn't open the Database: " << m_database.databaseName() << " - Error: " << m_database.lastError().text());
   }

   logDriverFeatures(); //< Describe the driver being used
}

SqliteDbHelper::~SqliteDbHelper() {
   if ( m_database.isOpen() )
      m_database.close();
}

// public:
QSqlDatabase SqliteDbHelper::open() {
   checkIsCreated();                   //< Create the DB tables if not already there
   return m_database;
}

QSqlDatabase SqliteDbHelper::open(const QString &alternativeConnName) {
   checkIsCreated();                   //< Create the DB tables if not already there
   QSqlDatabase newConn = QSqlDatabase::database(alternativeConnName, true);
   if ( !newConn.isValid() ) {
      newConn = QSqlDatabase::addDatabase(SQLITE_DRIVER_NAME, alternativeConnName);
      newConn.setDatabaseName(m_database.databaseName());
      if ( !newConn.isValid() || !newConn.open() ) {
         WARNING("Couldn't open a Connection with Alternative Name: " << alternativeConnName");
      }
   }
   return newConn;
}

// private:
void SqliteDbHelper::setDbVersion(const int version) {
   m_database.transaction();           //< TRANSACTION START
   QSqlQuery query(m_database);
   query.exec(INFO_TABLE_CREATE);
   query.prepare(INFO_TABLE_INSERT_VERSION);
   query.bindValue(0, version);
   query.exec();

   if ( !m_database.commit() ) {       //< TRANSACTION COMMIT
      WARNING("Couldn't add the _db_helper_info_ table - Error: " << query.lastError().text());
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
            DEBUG("Current Version of DB: " << m_database.databaseName() << " is: " << m_currVersion);
         } else {
            WARNING("More then 1 DB version? Something went wrong here!");
         }
      } else {
         if ( query.lastError().type() != QSqlError::StatementError ) {
            WARNING("Couldn't fetch the DB Version - DB:" << m_database.databaseName() << " - Error: " << query.lastError().text());
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
      DEBUG("Dropping Table: " << *i);
      if ( !query.exec(tableDropStr.arg(*i)) ) {
         WARNING("Unable to DROP TABLE " << *i << " - Error: " << query.lastError().text());
      }
   }

   if ( !m_database.commit() ) {    //< TRANSACTION COMMIT
      WARNING("Couldn't DROP TABLES. " << m_database.lastError().text());
   }
}

void SqliteDbHelper::logDriverFeatures() {
   VERBOSE_TAG("SQL Driver Config", "Support Transactions? " << m_database.driver()->hasFeature(QSqlDriver::Transactions));
   VERBOSE_TAG("SQL Driver Config", "Support QuerySize? " << m_database.driver()->hasFeature(QSqlDriver::QuerySize));
   VERBOSE_TAG("SQL Driver Config", "Support BLOB? " << m_database.driver()->hasFeature(QSqlDriver::BLOB));
   VERBOSE_TAG("SQL Driver Config", "Support Unicode? " << m_database.driver()->hasFeature(QSqlDriver::Unicode));
   VERBOSE_TAG("SQL Driver Config", "Support PreparedQueries? " << m_database.driver()->hasFeature(QSqlDriver::PreparedQueries));
   VERBOSE_TAG("SQL Driver Config", "Support NamedPlaceholders? " << m_database.driver()->hasFeature(QSqlDriver::NamedPlaceholders));
   VERBOSE_TAG("SQL Driver Config", "Support PositionalPlaceholders? " << m_database.driver()->hasFeature(QSqlDriver::PositionalPlaceholders));
   VERBOSE_TAG("SQL Driver Config", "Support LastInsertId? " << m_database.driver()->hasFeature(QSqlDriver::LastInsertId));
   VERBOSE_TAG("SQL Driver Config", "Support BatchOperations? " << m_database.driver()->hasFeature(QSqlDriver::BatchOperations));
   VERBOSE_TAG("SQL Driver Config", "Support SimpleLocking? " << m_database.driver()->hasFeature(QSqlDriver::SimpleLocking));
   VERBOSE_TAG("SQL Driver Config", "Support LowPrecisionNumbers? " << m_database.driver()->hasFeature(QSqlDriver::LowPrecisionNumbers));
   VERBOSE_TAG("SQL Driver Config", "Support EventNotifications? " << m_database.driver()->hasFeature(QSqlDriver::EventNotifications));
   VERBOSE_TAG("SQL Driver Config", "Support FinishQuery? " << m_database.driver()->hasFeature(QSqlDriver::FinishQuery));
   VERBOSE_TAG("SQL Driver Config", "Support MultipleResultSets? " << m_database.driver()->hasFeature(QSqlDriver::MultipleResultSets));
}

QTB_END_NAMESPACE
