//
// Created by VIKLOD on 15-06-2023.
//

#ifndef LANCELOT_INCLUDE_CONTRACT_INFO_HPP
#define LANCELOT_INCLUDE_CONTRACT_INFO_HPP

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Lancelot {
enum Exchange;
enum Instrument;
enum OptionType;
struct ResultSetT;
using ResultSetPtrT				= const ResultSetT*;
using RowWithColumnNameT		= std::unordered_map<std::string, std::string>;
using RowWithColumnIndexT		= std::vector<std::string>;
using TableWithColumnNameT		= std::vector<RowWithColumnNameT>;
using TableWithColumnIndexT		= std::vector<RowWithColumnIndexT>;
using ResultSetLoadingCallbackT = std::function<void(ResultSetPtrT)>;

class ContractInfo {
public:
	static void			 Initialize(const std::string& name_, const ResultSetLoadingCallbackT& callback_);
	static ResultSetPtrT GetResultSet(uint32_t token_);

	static uint32_t GetExpiryDate(uint32_t token_);
	static uint32_t GetLotMultiple(uint32_t token_);
	static uint32_t GetLotSize(uint32_t token_);
	static uint32_t GetTickSize(uint32_t token_);
	static uint32_t GetDivisor(uint32_t token_);
	static uint32_t GetFuture(uint32_t token_);
	static float	GetStrikePrice(uint32_t token_);

	static Instrument GetInstType(uint32_t token_);
	static OptionType GetOption(uint32_t token_);
	static Exchange	  GetExchange(uint32_t token_);

	static std::string GetSymbol(uint32_t token_);
	static std::string GetSegment(uint32_t token_);
	static std::string GetName(uint32_t token_);
	static std::string GetDescription(uint32_t token_);

	static bool IsOption(uint32_t token_);
	static bool IsEquity(uint32_t token_);
	static bool IsCall(uint32_t token_);
	static bool IsPut(uint32_t token_);
	static bool IsFuture(uint32_t token_);

	static void					 ExecuteQuery(const std::string& query_);
	static TableWithColumnIndexT GetResultWithIndex(const std::string& query_);
	static TableWithColumnNameT	 GetResultWithName(const std::string& query_);

	static OptionType GetOptionType(const std::string& option_);
	static Instrument GetInstrumentType(const std::string& type_);
	static Exchange	  GetExchangeCode(const std::string& exchange_);
};

}  // namespace Lancelot

#endif	// LANCELOT_INCLUDE_CONTRACT_INFO_HPP
