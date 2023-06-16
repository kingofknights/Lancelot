//
// Created by VIKLOD on 15-06-2023.
//

#include "Lancelot/ContractInfo.hpp"

#include "Lancelot/ContractFetcher.hpp"
#include "Lancelot/StoreProcedures.hpp"
#include "Lancelot/Structure.hpp"

namespace Lancelot {

using ResultSetContainerT = std::unordered_map<uint32_t, ResultSetPtrT>;
using TokenToFutureTokenT = std::unordered_map<uint32_t, uint32_t>;

static ResultSetContainerT ResultSetContainer;
static TokenToFutureTokenT TokenToFutureToken;

#define GET_RESULT_SET(TYPE, FIELD)                      \
	TYPE ContractInfo::Get##FIELD(uint32_t token_) {     \
		auto iterator = ResultSetContainer.find(token_); \
		if (iterator != ResultSetContainer.end()) {      \
			return iterator->second->FIELD;              \
		}                                                \
		return TYPE{};                                   \
	}

OptionType GetOptionType(const std::string& option_) {
	if (option_ == "CE") return OptionType_CALL;
	if (option_ == "PE") return OptionType_PUT;
	return OptionType_NONE;
}

Instrument GetInstrumentType(const std::string& type_) {
	if (type_.starts_with("FUT")) return Instrument_FUTURE;
	if (type_.starts_with("OPT")) return Instrument_OPTION;
	return Instrument_EQUITY;
}

Exchange GetExchangeCode(const std::string& exchange_) {
	if (exchange_ == "NSE_FO") return Exchange_NSE_FUTURE;
	if (exchange_ == "NSE_EQ") return Exchange_NSE_EQUITY;
	if (exchange_ == "NSE_CD") return Exchange_NSE_CURRENCY;
	if (exchange_ == "BSE_FO") return Exchange_BSE_FUTURE;
	if (exchange_ == "BSE_CD") return Exchange_BSE_CURRENCY;
	return Exchange_END;
}

void LoadResultSetTable(const TableT& table_) {
	for (const auto& row : table_) {
		auto* resultSetPtr = new ResultSetT;
		for (const auto& cell : row) {
			if (cell.first == "Segment") resultSetPtr->Segment = cell.second;
			if (cell.first == "Token") resultSetPtr->Token = std::stoi(cell.second);
			if (cell.first == "Symbol") resultSetPtr->Symbol = cell.second;
			if (cell.first == "ExpiryDate") resultSetPtr->ExpiryDate = std::stoi(cell.second);
			if (cell.first == "InstType") resultSetPtr->InstType = GetInstrumentType(cell.second);
			if (cell.first == "OptionType") resultSetPtr->Option = GetOptionType(cell.second);
			if (cell.first == "LotMultiple") resultSetPtr->LotMultiple = std::stoi(cell.second);
			if (cell.first == "LotSize") resultSetPtr->LotSize = std::stoi(cell.second);
			if (cell.first == "TickSize") resultSetPtr->TickSize = std::stoi(cell.second);
			if (cell.first == "Name") resultSetPtr->Name = cell.second;
			if (cell.first == "Divisor") resultSetPtr->Divisor = std::stoi(cell.second);
			if (cell.first == "Exchange") resultSetPtr->Exchange = GetExchangeCode(cell.second);
			if (cell.first == "Description") resultSetPtr->Description = cell.second;
		}
		resultSetPtr->StrikePrice /= resultSetPtr->Divisor;
		ResultSetContainer.emplace(resultSetPtr->Token, resultSetPtr);
	}
}

void LoadFutureOptionTable(const TableT& table_) {
	for (const auto& row : table_) {
		int option = std::stoi(row.at("option"));
		int future = std::stoi(row.at("future"));
		TokenToFutureToken.emplace(option, future);
	}
}
void ContractInfo::Initialize(const std::string& name_) {
	ContractFetcher contractFetcher(name_);

	auto table = contractFetcher.GetResult(GetResultSet_);
	LoadResultSetTable(table);

	table = contractFetcher.GetResult(GetFuture_);
	LoadFutureOptionTable(table);
}

ResultSetPtrT ContractInfo::GetResultSet(uint32_t token_) {
	auto iterator = ResultSetContainer.find(token_);
	if (iterator != ResultSetContainer.end()) {
		return iterator->second;
	}
	return {};
}
GET_RESULT_SET(uint32_t, ExpiryDate)
GET_RESULT_SET(uint32_t, LotMultiple)
GET_RESULT_SET(uint32_t, LotSize)
GET_RESULT_SET(uint32_t, TickSize)
GET_RESULT_SET(uint32_t, Divisor)
GET_RESULT_SET(float, StrikePrice)
GET_RESULT_SET(Instrument, InstType)
GET_RESULT_SET(OptionType, Option)
GET_RESULT_SET(Exchange, Exchange)
GET_RESULT_SET(std::string, Symbol)
GET_RESULT_SET(std::string, Segment)
GET_RESULT_SET(std::string, Name)
GET_RESULT_SET(std::string, Description)

#undef GET_RESULT_SET

uint32_t ContractInfo::GetFuture(uint32_t token_) {
	const auto iterator = TokenToFutureToken.find(token_);
	if (iterator != TokenToFutureToken.cend()) {
		return iterator->second;
	}
	return token_;
}

bool ContractInfo::IsOption(uint32_t token_) {
	return GetInstType(token_) == Instrument_OPTION;
}

bool ContractInfo::IsEquity(uint32_t token_) {
	return GetInstType(token_) == Instrument_EQUITY;
}

bool ContractInfo::IsCall(uint32_t token_) {
	return GetOption(token_) == OptionType_CALL;
}

bool ContractInfo::IsPut(uint32_t token_) {
	return GetOption(token_) == OptionType_PUT;
}

bool ContractInfo::IsFuture(uint32_t token_) {
	return GetInstType(token_) == Instrument_FUTURE;
}

}  // namespace Lancelot
