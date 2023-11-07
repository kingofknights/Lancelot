//
// Created by VIKLOD on 15-06-2023.
//

#include "Lancelot/ContractInfo/ContractInfo.hpp"

#include <unordered_map>
#include <sstream>

#include "Lancelot/ContractInfo/ContractFetcher.hpp"
#include "Lancelot/ContractInfo/StoreProcedures.hpp"
#include "Lancelot/Enums.hpp"
#include "Lancelot/Structure.hpp"
#include "Gawain.hpp"

namespace Lancelot {

	using ResultSetContainerT	= std::unordered_map<uint32_t, ResultSetPtrT>;
	using TokenToFutureTokenT	= std::unordered_map<uint32_t, uint32_t>;
	using NameToTokenContainerT = std::unordered_map<std::string, uint32_t>;

	namespace details {
		static ResultSetContainerT	 ResultSetContainer;
		static TokenToFutureTokenT	 TokenToFutureToken;
		static NameToTokenContainerT NameToTokenContainer;
		static ContractFetcher*		 contractFetcher = nullptr;
	}  // namespace details

#define GET_RESULT_SET(TYPE, FUNCTION, FIELD)                     \
	TYPE ContractInfo::Get##FUNCTION(uint32_t token_) {           \
		auto iterator = details::ResultSetContainer.find(token_); \
		if (iterator != details::ResultSetContainer.end()) {      \
			return iterator->second->FIELD;                       \
		}                                                         \
		return TYPE{};                                            \
	}

	void LoadResultSetTable(const TableWithColumnNameT& table_, const ResultSetLoadingCallbackT& callback_) {
		for (const auto& row : table_) {
			auto* resultSetPtr = new ResultSetT;

			resultSetPtr->_token	   = std::stoi(row.at("Token"));
			resultSetPtr->_expiryDate  = std::stoi(row.at("ExpiryDate"));
			resultSetPtr->_lotMultiple = std::stoi(row.at("LotMultiple"));
			resultSetPtr->_lotSize	   = std::stoi(row.at("LotSize"));
			resultSetPtr->_tickSize	   = std::stoi(row.at("TickSize"));
			resultSetPtr->_divisor	   = std::stoi(row.at("Divisor"));
			resultSetPtr->_option	   = Lancelot::ContractInfo::GetOptionType(row.at("OptionType"));
			resultSetPtr->_instType	   = Lancelot::ContractInfo::GetInstrumentType(row.at("InstType"));
			resultSetPtr->_exchange	   = Lancelot::ContractInfo::GetExchange(row.at("Exchange"));
			resultSetPtr->_strikePrice = std::stof(row.at("StrikePrice"));
			resultSetPtr->_symbol	   = row.at("Symbol");
			resultSetPtr->_segment	   = row.at("Segment");
			resultSetPtr->_name		   = row.at("Name");

			float close	  = std::stof(row.at("Close")) / resultSetPtr->_divisor;
			float lowDPR  = std::stof(row.at("LowDPR")) / resultSetPtr->_divisor;
			float highDPR = std::stof(row.at("HighDPR")) / resultSetPtr->_divisor;

			{
				std::stringstream ss;
				ss << (resultSetPtr->_strikePrice < 0 ? "FUT" : "OPT");
				ss << ' ' << resultSetPtr->_symbol.data();
				if (resultSetPtr->_strikePrice > 0) ss << ' ' << (resultSetPtr->_strikePrice) << ' ' << (resultSetPtr->_option == Lancelot::OptionType_CALL ? "CE" : "PE");
				ss << ' ' << FORMAT("{:%d%b}", fmt::localtime(resultSetPtr->_expiryDate));
				resultSetPtr->_description = ss.str();
			}
			resultSetPtr->_strikePrice /= resultSetPtr->_divisor;
			details::ResultSetContainer.emplace(resultSetPtr->_token, resultSetPtr);
			details::NameToTokenContainer.emplace(resultSetPtr->_description, resultSetPtr->_token);
			if (callback_) {
				callback_(resultSetPtr, close, lowDPR, highDPR);
			}
		}
	}

	void LoadFutureOptionTable(const TableWithColumnIndexT& table_) {
		for (const auto& row : table_) {
			int option = std::stoi(row.at(0));
			int future = std::stoi(row.at(1));
			details::TokenToFutureToken.emplace(option, future);
		}
	}
	void ContractInfo::Initialize(const std::string& name_, const ResultSetLoadingCallbackT& callback_) {
		details::contractFetcher = new ContractFetcher(name_);

		auto table1 = details::contractFetcher->getResultWithColumnName(GetResultSet_);
		LoadResultSetTable(table1, callback_);

		auto table2 = details::contractFetcher->getResultWithColumnIndex(GetFuture_);
		LoadFutureOptionTable(table2);
	}

	ResultSetPtrT ContractInfo::GetResultSet(uint32_t token_) {
		auto iterator = details::ResultSetContainer.find(token_);
		if (iterator != details::ResultSetContainer.end()) return iterator->second;
		return nullptr;
	}

	uint32_t ContractInfo::GetToken(const std::string& name_) {
		auto iterator = details::NameToTokenContainer.find(name_);
		if (iterator != details::NameToTokenContainer.cend()) return iterator->second;
		return 0;
	}

	GET_RESULT_SET(uint32_t, ExpiryDate, _expiryDate)
	GET_RESULT_SET(uint32_t, LotMultiple, _lotMultiple)
	GET_RESULT_SET(uint32_t, LotSize, _lotSize)
	GET_RESULT_SET(uint32_t, TickSize, _tickSize)
	GET_RESULT_SET(uint32_t, Divisor, _divisor)
	GET_RESULT_SET(float, StrikePrice, _strikePrice)
	GET_RESULT_SET(Instrument, InstType, _instType)
	GET_RESULT_SET(OptionType, Option, _option)
	GET_RESULT_SET(Exchange, Exchange, _exchange)
	GET_RESULT_SET(std::string, Symbol, _symbol)
	GET_RESULT_SET(std::string, Segment, _segment)
	GET_RESULT_SET(std::string, Name, _name)
	GET_RESULT_SET(std::string, Description, _description)

#undef GET_RESULT_SET

	uint32_t ContractInfo::GetOppositeToken(uint32_t token_) {
		std::string		  name	   = GetDescription(token_);
		bool			  isCall_  = IsCall(token_);
		const std::string call_put = isCall_ ? "CE" : "PE";
		const std::string reverse  = isCall_ ? "PE" : "CE";
		size_t			  pos	   = name.find(call_put);
		if (pos != std::string::npos) {
			name.replace(pos, call_put.length(), reverse);
			return GetToken(name);
		}
		return 0;
	}

	uint32_t ContractInfo::GetFuture(uint32_t token_) {
		const auto iterator = details::TokenToFutureToken.find(token_);
		if (iterator != details::TokenToFutureToken.cend()) return iterator->second;
		return token_;
	}

	bool ContractInfo::IsOption(uint32_t token_) { return GetInstType(token_) == Instrument_OPTION; }

	bool ContractInfo::IsEquity(uint32_t token_) { return GetInstType(token_) == Instrument_EQUITY; }

	bool ContractInfo::IsCall(uint32_t token_) { return GetOption(token_) == OptionType_CALL; }

	bool ContractInfo::IsPut(uint32_t token_) { return GetOption(token_) == OptionType_PUT; }

	bool ContractInfo::IsFuture(uint32_t token_) { return GetInstType(token_) == Instrument_FUTURE; }

	void ContractInfo::ExecuteQuery(const std::string& query_) { details::contractFetcher->executeQuery(query_); }

	TableWithColumnIndexT ContractInfo::GetResultWithIndex(const std::string& query_) { return details::contractFetcher->getResultWithColumnIndex(query_); }

	TableWithColumnNameT ContractInfo::GetResultWithName(const std::string& query_) { return details::contractFetcher->getResultWithColumnName(query_); }

	OptionType ContractInfo::GetOptionType(const std::string& option_) {
		if (option_ == "CE") return OptionType_CALL;
		if (option_ == "PE") return OptionType_PUT;
		return OptionType_NONE;
	}

	Instrument ContractInfo::GetInstrumentType(const std::string& type_) {
		if (type_.starts_with("FUT")) return Instrument_FUTURE;
		if (type_.starts_with("OPT")) return Instrument_OPTION;
		return Instrument_EQUITY;
	}

	Exchange ContractInfo::GetExchange(const std::string& exchange_) {
		if (exchange_ == "NSE_FO") return Exchange_NSE_FUTURE;
		if (exchange_ == "NSE_EQ") return Exchange_NSE_EQUITY;
		if (exchange_ == "NSE_CD") return Exchange_NSE_CURRENCY;
		if (exchange_ == "BSE_FO") return Exchange_BSE_FUTURE;
		if (exchange_ == "BSE_CD") return Exchange_BSE_CURRENCY;
		return Exchange_END;
	}

}  // namespace Lancelot
