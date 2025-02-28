#ifndef LANCELOT_INCLUDE_CONTRACT_FETCHER_HPP
#define LANCELOT_INCLUDE_CONTRACT_FETCHER_HPP
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace SQLite {
    class Database;
};
namespace Lancelot {
    using RowWithColumnNameT    = std::unordered_map<std::string, std::string>;
    using RowWithColumnIndexT   = std::vector<std::string>;
    using TableWithColumnNameT  = std::vector<RowWithColumnNameT>;
    using TableWithColumnIndexT = std::vector<RowWithColumnIndexT>;

    class ContractFetcher final {
      public:
        explicit ContractFetcher(const std::string& name_);

        ~ContractFetcher() noexcept;

        void Insert(TableWithColumnIndexT& table_);

        void ExecuteQuery(const std::string& query_);

        auto GetResultWithColumnName(const std::string& query_) -> TableWithColumnNameT;

        auto GetResultWithColumnIndex(const std::string& query_) -> TableWithColumnIndexT;

      private:
        static void PrintMetaData(const std::string& name_);

        SQLite::Database* _database;
    };
}  // namespace Lancelot

#endif  // LANCELOT_INCLUDE_CONTRACT_FETCHER_HPP
