#pragma once
#include <memory>
#include <string>
#include <vector>

#define SQLITE_ENABLE_COLUMN_METADATA

using RowT	 = std::vector<std::string>;
using TableT = std::vector<RowT>;

namespace SQLite {
class Database;
}  // namespace SQLite

using DatabasePtrT = std::unique_ptr<SQLite::Database>;

namespace Lancelot {
class Contract {
public:
	void   Initialize(const std::string &name_);
	void   ExecuteQuery(const std::string &query_);
	TableT GetResult(const std::string &query_);

private:
	static void printMetaData(const std::string &name_);

	DatabasePtrT _database;
};
}  // namespace Lancelot
