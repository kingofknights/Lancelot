#include "Lancelot/Database/DatabaseHandler.hpp"

#include "Lancelot/Logger/Logger.hpp"
namespace Lancelot {

DatabaseHandler &DatabaseHandler::GetInstance() {
	static DatabaseHandler db;
	return db;
}

void DatabaseHandler::InitConnection(const std::string &connection_, const std::string &user_, const std::string &password_) {
	try {
		_driver		= get_driver_instance();
		_connection = _driver->connect(connection_, user_, password_);

	} catch (sql::SQLException &e) {
		ManageException(e);
	} catch (...) {
		LOG(ERROR, "Unknown exception occured...!")
	}
}

void DatabaseHandler::SetSchema(const std::string &schema_) {
	_connection->setSchema(schema_);
	_statement = _connection->createStatement();
}

void DatabaseHandler::ManageException(sql::SQLException &e) {
	if (e.getErrorCode() != 0) {
		LOG(ERROR, "{} Error {} (MySQL error code: {}), SQLState: {}", e.what(), e.getErrorCode(), e.getSQLState())
	}
}

void DatabaseHandler::RunTransactionQuery(const std::string &query_) {
	try {
		if (!query_.empty()) {
			_statement->executeQuery(query_);
		}
	} catch (sql::SQLException &e) {
		ManageException(e);
	}
}

sql::ResultSet *DatabaseHandler::RunNonTransactionQuery(const std::string &query_) {
	try {
		if (!query_.empty()) {
			auto result = _statement->executeQuery(query_);
			return result;
		}
	} catch (sql::SQLException &e) {
		ManageException(e);
	}
	return nullptr;
}
}  // namespace Lancelot
