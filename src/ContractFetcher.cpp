#include "Lancelot/ContractInfo/ContractFetcher.hpp"

#include "Lancelot/Logger/Logger.hpp"

namespace Lancelot {
	ContractFetcher::ContractFetcher(const std::string& name_) : _database(name_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) { printMetaData(name_); }

	void ContractFetcher::printMetaData(const std::string& name_) {
		const SQLite::Header header = SQLite::Database::getHeaderInfo(name_);
		LOG(INFO, "SQLite Metadata -> Magic header string: {}", header.headerStr)
		LOG(INFO, "SQLite Metadata -> Page size bytes: {}", header.pageSizeBytes)
		LOG(INFO, "SQLite Metadata -> File format write version: {}", (int)header.fileFormatWriteVersion)
		LOG(INFO, "SQLite Metadata -> File format read version: {}", (int)header.fileFormatReadVersion)
		LOG(INFO, "SQLite Metadata -> Reserved space bytes: {}", (int)header.reservedSpaceBytes)
		LOG(INFO, "SQLite Metadata -> Max embedded payload fraction {}", (int)header.maxEmbeddedPayloadFrac)
		LOG(INFO, "SQLite Metadata -> Min embedded payload fraction: {}", (int)header.minEmbeddedPayloadFrac)
		LOG(INFO, "SQLite Metadata -> Leaf payload fraction: {}", (int)header.leafPayloadFrac)
		LOG(INFO, "SQLite Metadata -> File change counter: {}", header.fileChangeCounter)
		LOG(INFO, "SQLite Metadata -> Database size pages: {}", header.databaseSizePages)
		LOG(INFO, "SQLite Metadata -> First freelist trunk page: {}", header.firstFreelistTrunkPage)
		LOG(INFO, "SQLite Metadata -> Total freelist trunk pages: {}", header.totalFreelistPages)
		LOG(INFO, "SQLite Metadata -> Schema cookie: {}", header.schemaCookie)
		LOG(INFO, "SQLite Metadata -> Schema format number: {}", header.schemaFormatNumber)
		LOG(INFO, "SQLite Metadata -> Default page cache size bytes: {}", header.defaultPageCacheSizeBytes)
		LOG(INFO, "SQLite Metadata -> Largest B tree page number: {}", header.largestBTreePageNumber)
		LOG(INFO, "SQLite Metadata -> Database text encoding: {}", header.databaseTextEncoding)
		LOG(INFO, "SQLite Metadata -> User version: {}", header.userVersion)
		LOG(INFO, "SQLite Metadata -> Incremental vaccum mode: {}", header.incrementalVaccumMode)
		LOG(INFO, "SQLite Metadata -> Application ID: {}", header.applicationId)
		LOG(INFO, "SQLite Metadata -> Version valid for: {}", header.versionValidFor)
		LOG(INFO, "SQLite Metadata -> SQLite version: {}", header.sqliteVersion)
	}

	TableWithColumnNameT ContractFetcher::getResultWithColumnName(const std::string& query_) {
		SQLite::Statement	 query(_database, query_);
		TableWithColumnNameT table;
		while (query.executeStep()) {
			RowWithColumnNameT row;
			for (int i = 0; i < query.getColumnCount(); i++) {
				row.emplace(query.getColumnName(i), query.getColumn(i).getString());
			}
			table.push_back(row);
		}
		return table;
	}

	TableWithColumnIndexT ContractFetcher::getResultWithColumnIndex(const std::string& query_) {
		SQLite::Statement	  query(_database, query_);
		TableWithColumnIndexT table;
		while (query.executeStep()) {
			RowWithColumnIndexT row;
			for (int i = 0; i < query.getColumnCount(); i++) {
				row.emplace_back(query.getColumn(i).getString());
			}
			table.push_back(row);
		}
		return table;
	}

	void ContractFetcher::executeQuery(const std::string& query_) {
		try {
			SQLite::Statement query(_database, query_);
			query.executeStep();
		} catch (std::exception& ex_) {
			LOG(ERROR, "{} {}", __FUNCTION__, ex_.what())
		}
	}

}  // namespace Lancelot
