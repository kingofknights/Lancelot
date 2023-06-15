#ifndef LANCELOT_INCLUDE_CONTRACT_FETCHER_HPP
#define LANCELOT_INCLUDE_CONTRACT_FETCHER_HPP
#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#define SQLITE_ENABLE_COLUMN_METADATA
#include <SQLiteCpp/SQLiteCpp.h>

using RowT	 = std::unordered_map<std::string, std::string>;
using TableT = std::vector<RowT>;

namespace Lancelot {
class ContractFetcher final {
public:
	explicit ContractFetcher(const std::string &name_);
	void   ExecuteQuery(const std::string &query_);
	TableT GetResult(const std::string &query_);

private:
	static void printMetaData(const std::string &name_);

	SQLite::Database _database;
};
}  // namespace Lancelot

#endif	// LANCELOT_INCLUDE_CONTRACT_FETCHER_HPP