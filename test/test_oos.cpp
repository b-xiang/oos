/*
 * This file is part of OpenObjectStore OOS.
 *
 * OpenObjectStore OOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenObjectStore OOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenObjectStore OOS. If not, see <http://www.gnu.org/licenses/>.
 */

#include "unit/FirstTestUnit.hpp"
#include "unit/SecondTestUnit.hpp"

#include "tools/AnyTestUnit.hpp"
#include "tools/BlobTestUnit.hpp"
#include "tools/DateTestUnit.hpp"
#include "tools/TimeTestUnit.hpp"
#include "tools/VarCharTestUnit.hpp"
#include "tools/FactoryTestUnit.hpp"
#include "tools/StringTestUnit.hpp"

#include "object/ObjectStoreTestUnit.hpp"
#include "object/ObjectPrototypeTestUnit.hpp"
#include "object/ObjectTransactiontestUnit.hpp"
#include "object/PrototypeTreeTest.hpp"
#include "object/PrimaryKeyUnitTest.hpp"
#include "object/HasManyVectorUnitTest.hpp"
#include "object/HasManyListUnitTest.hpp"

#include "orm/OrmTestUnit.hpp"
#include "orm/TransactionTestUnit.hpp"

#include "sql/ConnectionTestUnit.hpp"
#include "sql/DialectTestUnit.hpp"
#include "sql/QueryTestUnit.hpp"
#include "sql/ConditionUnitTest.hpp"
#include "sql/MSSQLDialectTestUnit.hpp"
#include "sql/SQLiteDialectTestUnit.hpp"

//#include "json/JsonTestUnit.hpp"

#include "connections.hpp"

#ifdef OOS_MYSQL
#ifdef WIN32
#include <mysql_version.h>
#else
#include <mysql/mysql_version.h>
#endif
#endif

using namespace oos;

int main(int argc, char *argv[])
{
  oos::test_suite suite;

  suite.init(argc, argv);

  suite.register_unit(new FirstTestUnit);
  suite.register_unit(new SecondTestUnit);

  suite.register_unit(new AnyTestUnit);
  suite.register_unit(new DateTestUnit);
  suite.register_unit(new TimeTestUnit);
  suite.register_unit(new BlobTestUnit);
  suite.register_unit(new VarCharTestUnit);
  suite.register_unit(new FactoryTestUnit);
  suite.register_unit(new StringTestUnit);

  suite.register_unit(new PrimaryKeyUnitTest);
  suite.register_unit(new PrototypeTreeTestUnit);
  suite.register_unit(new ObjectPrototypeTestUnit);
  suite.register_unit(new ObjectStoreTestUnit);
  suite.register_unit(new ObjectTransactiontestUnit);
  suite.register_unit(new HasManyVectorUnitTest);
  suite.register_unit(new HasManyListUnitTest);

  suite.register_unit(new ConditionUnitTest);
  suite.register_unit(new DialectTestUnit);

#ifdef OOS_MYSQL
  suite.register_unit(new ConnectionTestUnit("mysql_conn", "mysql connection test unit", ::connection::mysql));
  suite.register_unit(new TransactionTestUnit("mysql_transaction", "mysql transaction test unit", ::connection::mysql));
  suite.register_unit(new QueryTestUnit("mysql_query", "mysql query test unit", ::connection::mysql, oos::time(2015, 3, 15, 13, 56, 23)));
  suite.register_unit(new OrmTestUnit("mysql", ::connection::mysql));
#endif

#ifdef OOS_ODBC
  suite.register_unit(new ConnectionTestUnit("mssql_conn", "mssql connection test unit", ::connection::mssql));
  suite.register_unit(new TransactionTestUnit("mssql_transaction", "mssql transaction test unit", ::connection::mssql));
  suite.register_unit(new QueryTestUnit("mssql_query", "mssql query test unit", ::connection::mssql));
  suite.register_unit(new OrmTestUnit("mssql", ::connection::mssql));
  suite.register_unit(new MSSQLDialectTestUnit());
#endif

#ifdef OOS_SQLITE3
  suite.register_unit(new ConnectionTestUnit("sqlite_conn", "sqlite connection test unit", ::connection::sqlite));
  suite.register_unit(new TransactionTestUnit("sqlite_transaction", "sqlite transaction test unit", ::connection::sqlite));
  suite.register_unit(new QueryTestUnit("sqlite_query", "sqlite query test unit", ::connection::sqlite));
  suite.register_unit(new OrmTestUnit("sqlite", ::connection::sqlite));
  suite.register_unit(new SQLiteDialectTestUnit());
#endif

//  suite.register_unit(new TransactionTestUnit("memory_transaction", "memory transaction test unit"));
//
//  suite.register_unit(new JsonTestUnit());

  bool result = suite.run();
  return result ? 0 : 1;
}
