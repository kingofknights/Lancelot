//
// Created by VIKLOD on 15-06-2023.
//

#include "../include/ContractInfo.hpp"

#include "../include/ContractFetcher.hpp"
#include "../include/StoreProcedures.hpp"
namespace Lancelot {

static ResultSetContainerT ResultSetContainer;

#define GET_RESULT_SET(TYPE, FIELD)                      \
	TYPE ContractInfo::Get##FIELD(uint32_t token_) {     \
		auto iterator = ResultSetContainer.find(token_); \
		if (iterator != ResultSetContainer.end()) {      \
			return iterator->second->FIELD;              \
		}                                                \
		return TYPE{};                                   \
	}

void ContractInfo::Initialize(const std::string& name_) {
	ContractFetcher contractFetcher(name_);
	auto			table = contractFetcher.GetResult(GetResultSet_);
	for (const auto& row : table) {
		ResultSetPtrT resultSetPtr = std::make_shared<ResultSetT>();
		for (const auto& cell : row){
			if(cell.first == "Segment"){resultSetPtr->Segment = cell.second;}
			if(cell.first == "Token"){resultSetPtr->Token = std::stoi(cell.second);}
			if(cell.first == "Symbol"){resultSetPtr->Symbol = cell.second;}
			if(cell.first == "ExpiryDate"){resultSetPtr->ExpiryDate = std::stoi(cell.second);}
			if(cell.first == "InstType"){}
			if(cell.first == "OptionType"){}
			if(cell.first == "LotMultiple"){resultSetPtr->LotMultiple = std::stoi(cell.second);}
			if(cell.first == "LotSize"){resultSetPtr->LotSize = std::stoi(cell.second);}
			if(cell.first == "TickSize"){resultSetPtr->TickSize = std::stoi(cell.second);}
			if(cell.first == "Name"){resultSetPtr->Name = cell.second;}
			if(cell.first == "Divisor"){resultSetPtr->Divisor = std::stoi(cell.second);}
			if(cell.first == "Exchange"){}
		}
		resultSetPtr->StrikePrice /= resultSetPtr->Divisor;
		ResultSetContainer.emplace(resultSetPtr->Token, resultSetPtr);
	}
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

}  // namespace Lancelot
