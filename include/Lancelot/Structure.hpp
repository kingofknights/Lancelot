#ifndef LANCELOT_INCLUDE_STRUCTURE_HPP
#define LANCELOT_INCLUDE_STRUCTURE_HPP
#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

namespace Lancelot {

enum Exchange {
	Exchange_NSE_FUTURE = 0,
	Exchange_NSE_EQUITY,
	Exchange_NSE_CURRENCY,
	Exchange_BSE_FUTURE,
	Exchange_BSE_CURRENCY,
	Exchange_END
};

enum Instrument {
	Instrument_FUTURE = 0,
	Instrument_OPTION,
	Instrument_EQUITY,
	Instrument_OTHER
};

enum OptionType {
	OptionType_NONE = 0,
	OptionType_CALL,
	OptionType_PUT,
};

#pragma pack(push, 1)
using ResultSetT = struct ResultSetT {
	uint32_t	Token;
	uint32_t	ExpiryDate;
	uint32_t	LotMultiple;
	uint32_t	LotSize;
	uint32_t	TickSize;
	uint32_t	Divisor;
	float		StrikePrice;
	Instrument	InstType;
	OptionType	Option;
	Exchange	Exchange;
	std::string Symbol;
	std::string Segment;
	std::string Name;
};
#pragma pack(pop)

using ResultSetPtrT		  = std::shared_ptr<ResultSetT>;
using ResultSetContainerT = std::unordered_map<uint32_t, ResultSetPtrT>;

}  // namespace Lancelot

#endif	// LANCELOT_INCLUDE_STRUCTURE_HPP