#ifndef LANCELOT_INCLUDE_STRUCTURE_HPP
#define LANCELOT_INCLUDE_STRUCTURE_HPP
#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

namespace Lancelot {

	enum Instrument : int;
	enum OptionType : int;
	enum ExchangeCode : int;

#pragma pack(push, 1)
	using ResultSetT = struct ResultSetT {
		uint32_t	 Token;
		uint32_t	 ExpiryDate;
		uint32_t	 LotMultiple;
		uint32_t	 LotSize;
		uint32_t	 TickSize;
		uint32_t	 Divisor;
		float		 StrikePrice;
		Instrument	 InstType;
		OptionType	 Option;
		ExchangeCode Exchange;
		std::string	 Symbol;
		std::string	 Segment;
		std::string	 Name;
		std::string	 Description;
	};
#pragma pack(pop)

}  // namespace Lancelot

#endif	// LANCELOT_INCLUDE_STRUCTURE_HPP
