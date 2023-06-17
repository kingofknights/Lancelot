#ifndef LANCELOT_INCLUDE_DATABASE_HANDLER_HPP
#define LANCELOT_INCLUDE_DATABASE_HANDLER_HPP

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace sql {
class Driver;
class Connection;
class Statement;
class ResultSet;
class SQLException;
}  // namespace sql

namespace Lancelot {
using RowWithColumnNameT	= std::unordered_map<std::string, std::string>;
using RowWithColumnIndexT	= std::vector<std::string>;
using TableWithColumnNameT	= std::vector<RowWithColumnNameT>;
using TableWithColumnIndexT = std::vector<RowWithColumnIndexT>;
class DatabaseHandler {
public:
	static DatabaseHandler &GetInstance();

	void InitConnection(const std::string &connection_, const std::string &user_, const std::string &password_);

	void SetSchema(const std::string &schema_);

	void RunTransactionQuery(const std::string &query_);

	sql::ResultSet *RunNonTransactionQuery(const std::string &query_);

protected:
	void ManageException(sql::SQLException &e);

private:
	sql::Driver *	 _driver	 = nullptr;
	sql::Connection *_connection = nullptr;
	sql::Statement * _statement	 = nullptr;
};

}  // namespace Lancelot

#endif	// LANCELOT_INCLUDE_DATABASE_HANDLER_HPP
