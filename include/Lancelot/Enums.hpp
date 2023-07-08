//
// Created by kingofknights on 7/8/23.
//

#ifndef LANCELOT_INCLUDE_ENUMS_HPP
#define LANCELOT_INCLUDE_ENUMS_HPP
#pragma once

namespace Lancelot {

	enum ExchangeCode : int {
		Exchange_NSE_FUTURE = 0,
		Exchange_NSE_EQUITY,
		Exchange_NSE_CURRENCY,
		Exchange_BSE_FUTURE,
		Exchange_BSE_CURRENCY,
		Exchange_END
	};

	enum Instrument : int {
		Instrument_FUTURE = 0,
		Instrument_OPTION,
		Instrument_EQUITY,
		Instrument_OTHER
	};

	enum OptionType : int {
		OptionType_NONE = 0,
		OptionType_CALL,
		OptionType_PUT,
	};

	enum SideType : int {
		SideType_BUY = 0,
		SideType_SELL
	};
}  // namespace Lancelot
#endif	// LANCELOT_INCLUDE_ENUMS_HPP
