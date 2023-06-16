#ifndef LANCELOT_INCLUDE_DATABASE_HANDLER_HPP
#define LANCELOT_INCLUDE_DATABASE_HANDLER_HPP

#pragma once
#include <mysql/jdbc.h>

namespace sql {
class Driver;
class Connection;
class Statement;
class ResultSet;
}  // namespace sql

namespace Lancelot {

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
