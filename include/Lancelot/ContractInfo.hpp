//
// Created by VIKLOD on 15-06-2023.
//

#ifndef LANCELOT_INCLUDE_CONTRACT_INFO_HPP
#define LANCELOT_INCLUDE_CONTRACT_INFO_HPP

#include <string>

namespace Lancelot {
enum Exchange;
enum Instrument;
enum OptionType;
struct ResultSetT;
using ResultSetPtrT = const ResultSetT*;

class ContractInfo {
public:
	static void			 Initialize(const std::string& name_);
	static ResultSetPtrT GetResultSet(uint32_t token_);
	static uint32_t		 GetExpiryDate(uint32_t token_);
	static uint32_t		 GetLotMultiple(uint32_t token_);
	static uint32_t		 GetLotSize(uint32_t token_);
	static uint32_t		 GetTickSize(uint32_t token_);
	static uint32_t		 GetDivisor(uint32_t token_);
	static float		 GetStrikePrice(uint32_t token_);
	static Instrument	 GetInstType(uint32_t token_);
	static OptionType	 GetOption(uint32_t token_);
	static Exchange		 GetExchange(uint32_t token_);
	static std::string	 GetSymbol(uint32_t token_);
	static std::string	 GetSegment(uint32_t token_);
	static std::string	 GetName(uint32_t token_);
	static std::string	 GetDescription(uint32_t token_);
};
}  // namespace Lancelot

#endif	// LANCELOT_INCLUDE_CONTRACT_INFO_HPP
