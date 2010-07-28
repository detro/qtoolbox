/**
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE.txt
* file distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#include <QString>
#include <QtTest>
#include <QSqlQuery>
#include <QVariant>

#include "SqliteDbHelperExample.h"

class SqlitedbhelperTest : public QObject
{
   Q_OBJECT

public:
   SqlitedbhelperTest();

private:
   void createDbHelperVersion(const int& version);
   void deleteDbHelper();
   void insertRow(const QString& name, const int& age);
   void updateRowById(const int& id, const QString& name, const int& age);
   void deleteRowById(const int& id);
   QString selectNameAtId(const int id);
   int selectAgeAtId(const int id);

private slots:
   void initTestCase();
   void cleanupTestCase();

   void testDbIsValid();
   void testInsert();
   void testUpdate();
   void testDelete();
   void testUpgradeDbAndInsert();
   void testUpgradeDbAndUpdateAbsentRow();

private:
   SqliteDbHelperExample* m_dbHelperExample;
   QSqlDatabase m_db;
};

SqlitedbhelperTest::SqlitedbhelperTest()
   : m_dbHelperExample(NULL)
{
}


// private:
void SqlitedbhelperTest::createDbHelperVersion(const int& version) {
   if ( m_dbHelperExample != NULL ) {
      deleteDbHelper();
   }
   m_dbHelperExample = new SqliteDbHelperExample(version);
   m_db = m_dbHelperExample->open();
}

void SqlitedbhelperTest::deleteDbHelper() {
   m_db.close();
   m_dbHelperExample->destroy();
   delete m_dbHelperExample;
   m_dbHelperExample = NULL;
}

void SqlitedbhelperTest::insertRow(const QString& name, const int& age) {
   QSqlQuery query(m_db);
   query.prepare("INSERT INTO "TEST_TABLE" (name, age) VALUES (?, ?)");
   query.addBindValue(name);
   query.addBindValue(age);
   QVERIFY(query.exec());
}

void SqlitedbhelperTest::updateRowById(const int& id, const QString& name, const int& age) {
   QSqlQuery query(m_db);
   query.prepare("UPDATE "TEST_TABLE" SET name= ?, age = ? WHERE id = ?");
   query.addBindValue(name);
   query.addBindValue(age);
   query.addBindValue(id);
   QVERIFY(query.exec());
}

void SqlitedbhelperTest::deleteRowById(const int& id) {
   QSqlQuery query(m_db);
   query.prepare("DELETE FROM "TEST_TABLE" WHERE id = ?");
   query.addBindValue(id);
   QVERIFY(query.exec());
}

QString SqlitedbhelperTest::selectNameAtId(const int id) {
   QSqlQuery query(m_db);
   query.prepare("SELECT name FROM "TEST_TABLE" WHERE id = ?");
   query.addBindValue(id);
   if ( !query.exec() || !query.first() ) {
      return QString(""); // nothing found
   }
   return query.value(0).toString();
}

int SqlitedbhelperTest::selectAgeAtId(const int id) {
   QSqlQuery query(m_db);
   query.prepare("SELECT age FROM "TEST_TABLE" WHERE id = ?");
   query.addBindValue(id);
   if ( !query.exec() || !query.first() ) {
      return -1; // nothing found
   }
   return query.value(0).toInt();
}


// private slots:
void SqlitedbhelperTest::initTestCase() {
   createDbHelperVersion(1);
   QVERIFY(m_dbHelperExample != NULL && m_db.isOpen());
}

void SqlitedbhelperTest::testDbIsValid() {
   QVERIFY2(m_dbHelperExample->isValid(), "Db Helper not valid after creation");
}

void SqlitedbhelperTest::testInsert() {
   const QString name("firstname secondname");
   const int age = 30;
   insertRow(name, age);
   QVERIFY(name == selectNameAtId(1) && age == selectAgeAtId(1));
}

void SqlitedbhelperTest::testUpdate() {
   const QString name("new firstname secondname");
   const int age = 35;
   updateRowById(1, name, age);
   QVERIFY(name == selectNameAtId(1) && age == selectAgeAtId(1));
}

void SqlitedbhelperTest::testDelete() {
   deleteRowById(1);
   QVERIFY("" == selectNameAtId(1) && -1 == selectAgeAtId(1));
}

void SqlitedbhelperTest::testUpgradeDbAndInsert() {
   testInsert();
   createDbHelperVersion(2);
   testInsert();
}

void SqlitedbhelperTest::testUpgradeDbAndUpdateAbsentRow() {
   createDbHelperVersion(3);
   const QString name("new firstname secondname");
   const int age = 35;
   updateRowById(1, name, age);
   QVERIFY(name != selectNameAtId(1) && age != selectAgeAtId(1));
}

void SqlitedbhelperTest::cleanupTestCase() {
   deleteDbHelper();
   QVERIFY(m_dbHelperExample == NULL);
}

QTEST_APPLESS_MAIN(SqlitedbhelperTest);

#include "tst_SqlitedbhelperTest.moc"
