#ifndef SQLITEDBHELPER_H
#define SQLITEDBHELPER_H

#include <QString>
#include <QSqlDatabase>

#include "macros.h"

QTB_BEGIN_NAMESPACE

/**
   @class SqliteDbHelper
   @brief Simplify Sqlite Database versioning during a project life-cycle.

   It works as a Super-class for other, more specific DbHelpers.
   What it "helps" to do, is to handle the versioning of the database in
   a simple and clean manner: if you ask for a version of DB that is higher
   then the current one, it deletes the current one and creates the new one,
   before returning an open connection to the DB.

   NOTE: This class closes the QSqlDatabase (Connection) that it provides, when destroyed.
   So, don't destroy until finished using the QSqlDatabase.

   This class is not Thread-Safe. This means that you will need one instance of its subclasses
   per-thread. Also, to avoid QSqlDatabase Connection collisions, every instance will have to use
   a different "Connection Name". Use the "defaultConnName" only in one thread.
*/
class SqliteDbHelper
{
public:
   SqliteDbHelper(const QString &filePath, const int version, const QString &defaultConnName = QString());
   virtual ~SqliteDbHelper();

public:
   /**
     Opens a the Default QSqlDatabase connection, based on the name provided at construction.
     The method is NOT Thread-Safe.
   */
   QSqlDatabase open();
   /**
     Opens a new QSqlDatabase connection, with a new Connection Name.
     The receiver takes responsibility of the connection.
     The method is NOT Thread-Safe: this means that you should use it if you want a extra
     connection withing the same thread.

     @param alternativeConnName Alternative/New Connection Name
   */
   QSqlDatabase open(const QString &alternativeConnName);

protected:
   /**
     Subclasses have to implement this method to create their specific Tables.
     The connection to use is passed in by the Superclass.
   */
   virtual void onCreate(QSqlDatabase &database) = 0;

private:
   void setVersion(const int version);
   int version();
   void createIfNecessary();
   void dropTables();
   void logDriverFeatures();

private:
   QSqlDatabase  m_database;
   int           m_currVersion;
   bool          m_created;
};

QTB_END_NAMESPACE

#endif // SQLITEDBHELPER_H
