//
// Created by VIKLOD on 15-06-2023.
//

#include "Lancelot/ContractInfo/ContractInfo.hpp"

#include "Lancelot/ContractInfo/ContractFetcher.hpp"
#include "Lancelot/ContractInfo/StoreProcedures.hpp"
#include "Lancelot/Enums.hpp"
#include "Lancelot/Logger/Logger.hpp"
#include "Lancelot/Structure.hpp"

namespace Lancelot {

	using ResultSetContainerT	= std::unordered_map<uint32_t, ResultSetPtrT>;
	using TokenToFutureTokenT	= std::unordered_map<uint32_t, uint32_t>;
	using NameToTokenContainerT = std::unordered_map<std::string, uint32_t>;

	static ResultSetContainerT	 ResultSetContainer;
	static TokenToFutureTokenT	 TokenToFutureToken;
	static NameToTokenContainerT NameToTokenContainer;
	static ContractFetcher*		 contractFetcher = nullptr;

#define GET_RESULT_SET(TYPE, FIELD)                      \
	TYPE ContractInfo::Get##FIELD(uint32_t token_) {     \
		auto iterator = ResultSetContainer.find(token_); \
		if (iterator != ResultSetContainer.end()) {      \
			return iterator->second->FIELD;              \
		}                                                \
		return TYPE{};                                   \
	}

	void LoadResultSetTable(const TableWithColumnNameT& table_, const ResultSetLoadingCallbackT& callback_) {
		for (const auto& row : table_) {
			auto* resultSetPtr		  = new ResultSetT;
			resultSetPtr->Segment	  = row.at("Segment");
			resultSetPtr->Token		  = std::stoi(row.at("Token"));
			resultSetPtr->Symbol	  = row.at("Symbol");
			resultSetPtr->ExpiryDate  = std::stoi(row.at("ExpiryDate"));
			resultSetPtr->InstType	  = ContractInfo::GetInstrumentType(row.at("InstType"));
			resultSetPtr->Option	  = ContractInfo::GetOptionType(row.at("OptionType"));
			resultSetPtr->LotMultiple = std::stoi(row.at("LotMultiple"));
			resultSetPtr->LotSize	  = std::stoi(row.at("LotSize"));
			resultSetPtr->TickSize	  = std::stoi(row.at("TickSize"));
			resultSetPtr->Name		  = row.at("Name");
			resultSetPtr->Divisor	  = std::stoi(row.at("Divisor"));
			resultSetPtr->Exchange	  = ContractInfo::GetExchangeCode(row.at("Exchange"));
			resultSetPtr->StrikePrice = std::stof(row.at("StrikePrice"));
			float close				  = std::stof(row.at("Close")) / resultSetPtr->Divisor;
			float lowDPR			  = std::stof(row.at("LowDPR")) / resultSetPtr->Divisor;
			float highDPR			  = std::stof(row.at("HighDPR")) / resultSetPtr->Divisor;

			{
				std::stringstream ss;
				ss << (resultSetPtr->StrikePrice < 0 ? "FUT" : "OPT");
				ss << ' ' << resultSetPtr->Symbol;
				if (resultSetPtr->StrikePrice > 0) ss << ' ' << (resultSetPtr->StrikePrice) << ' ' << (resultSetPtr->Option == OptionType_CALL ? "CE" : "PE");
				ss << ' ' << FORMAT("{:%d%b}", fmt::localtime(resultSetPtr->ExpiryDate));
				resultSetPtr->Description = ss.str();
			}
			resultSetPtr->StrikePrice /= resultSetPtr->Divisor;
			ResultSetContainer.emplace(resultSetPtr->Token, resultSetPtr);
			NameToTokenContainer.emplace(resultSetPtr->Description, resultSetPtr->Token);
			if (callback_) {
				callback_(resultSetPtr, close, lowDPR, highDPR);
			}
		}
	}

	void LoadFutureOptionTable(const TableWithColumnIndexT& table_) {
		for (const auto& row : table_) {
			int option = std::stoi(row.at(0));
			int future = std::stoi(row.at(1));
			TokenToFutureToken.emplace(option, future);
		}
	}
	void ContractInfo::Initialize(const std::string& name_, const ResultSetLoadingCallbackT& callback_) {
		contractFetcher = new ContractFetcher(name_);

		auto table1 = contractFetcher->getResultWithColumnName(GetResultSet_);
		LoadResultSetTable(table1, callback_);

		auto table2 = contractFetcher->getResultWithColumnIndex(GetFuture_);
		LoadFutureOptionTable(table2);
	}

	ResultSetPtrT ContractInfo::GetResultSet(uint32_t token_) {
		auto iterator = ResultSetContainer.find(token_);
		if (iterator != ResultSetContainer.end()) return iterator->second;
		return nullptr;
	}

	uint32_t ContractInfo::GetToken(const std::string& name_) {
		auto iterator = NameToTokenContainer.find(name_);
		if (iterator != NameToTokenContainer.cend()) return iterator->second;
		return 0;
	}

	GET_RESULT_SET(uint32_t, ExpiryDate)
	GET_RESULT_SET(uint32_t, LotMultiple)
	GET_RESULT_SET(uint32_t, LotSize)
	GET_RESULT_SET(uint32_t, TickSize)
	GET_RESULT_SET(uint32_t, Divisor)
	GET_RESULT_SET(float, StrikePrice)
	GET_RESULT_SET(Instrument, InstType)
	GET_RESULT_SET(OptionType, Option)
	GET_RESULT_SET(ExchangeCode, Exchange)
	GET_RESULT_SET(std::string, Symbol)
	GET_RESULT_SET(std::string, Segment)
	GET_RESULT_SET(std::string, Name)
	GET_RESULT_SET(std::string, Description)
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
		const auto iterator = TokenToFutureToken.find(token_);
		if (iterator != TokenToFutureToken.cend()) return iterator->second;
		return token_;
	}

	bool ContractInfo::IsOption(uint32_t token_) { return GetInstType(token_) == Instrument_OPTION; }

	bool ContractInfo::IsEquity(uint32_t token_) { return GetInstType(token_) == Instrument_EQUITY; }

	bool ContractInfo::IsCall(uint32_t token_) { return GetOption(token_) == OptionType_CALL; }

	bool ContractInfo::IsPut(uint32_t token_) { return GetOption(token_) == OptionType_PUT; }

	bool ContractInfo::IsFuture(uint32_t token_) { return GetInstType(token_) == Instrument_FUTURE; }

	void ContractInfo::ExecuteQuery(const std::string& query_) { contractFetcher->executeQuery(query_); }

	TableWithColumnIndexT ContractInfo::GetResultWithIndex(const std::string& query_) { return contractFetcher->getResultWithColumnIndex(query_); }

	TableWithColumnNameT ContractInfo::GetResultWithName(const std::string& query_) { return contractFetcher->getResultWithColumnName(query_); }

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

	ExchangeCode ContractInfo::GetExchangeCode(const std::string& exchange_) {
		if (exchange_ == "NSE_FO") return Exchange_NSE_FUTURE;
		if (exchange_ == "NSE_EQ") return Exchange_NSE_EQUITY;
		if (exchange_ == "NSE_CD") return Exchange_NSE_CURRENCY;
		if (exchange_ == "BSE_FO") return Exchange_BSE_FUTURE;
		if (exchange_ == "BSE_CD") return Exchange_BSE_CURRENCY;
		return Exchange_END;
	}

	std::string ContractInfo::GetExchangeName(ExchangeCode exchangeCode_) {
		if (exchangeCode_ == Exchange_NSE_FUTURE) return "NSE_FO";
		if (exchangeCode_ == Exchange_NSE_EQUITY) return "NSE_EQ";
		if (exchangeCode_ == Exchange_NSE_CURRENCY) return "NSE_CD";
		if (exchangeCode_ == Exchange_BSE_FUTURE) return "BSE_FO";
		if (exchangeCode_ == Exchange_BSE_CURRENCY) return "BSE_CD";
		return {};
	}
}  // namespace Lancelot
