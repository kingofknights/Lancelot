//
// Created by kingofknights on 7/8/23.
//

#ifndef LANCELOT_INCLUDE_ENUMS_HPP
#define LANCELOT_INCLUDE_ENUMS_HPP
#pragma once

#define JSON_PARAMS		   "params"
#define JSON_ID			   "uniqueId"
#define JSON_TOKEN		   "token"
#define JSON_PRICE		   "price"
#define JSON_QUANTITY	   "quantity"
#define JSON_CLIENT		   "client"
#define JSON_SIDE		   "side"
#define JSON_ORDER_ID	   "order_id"
#define JSON_ARGUMENTS	   "arguments"
#define JSON_PF_NUMBER	   "pf"
#define JSON_UNIQUE_ID	   "unique_id"
#define JSON_STRATEGY_NAME "name"
#define JSON_ORDER_TYPE	   "type"
#define JSON_TIME		   "time"
#define JSON_FILL_QUANTITY "fill_quantity"
#define JSON_FILL_PRICE	   "fill_price"
#define JSON_REMAINING	   "remaining"
#define JSON_MESSAGE	   "message"

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

	enum RequestType : int {
		RequestType_LOGIN = 0,
		// ORDER
		RequestType_NEW,
		RequestType_MODIFY,
		RequestType_CANCEL,
		// STRATEGY
		RequestType_APPLY,
		RequestType_SUBSCRIBE,
		RequestType_UNSUBSCRIBE,
		RequestType_SUBSCRIBE_APPLY,
	};

	enum ResponseType : int {
		// ORDER
		ResponseType_PLACED = 0,
		ResponseType_NEW,
		ResponseType_REPLACED,
		ResponseType_CANCELLED,
		ResponseType_NEW_REJECT,
		ResponseType_REPLACE_REJECT,
		ResponseType_CANCEL_REJECT,
		ResponseType_PARTIAL_FILLED,
		ResponseType_FILLED,

		// STRATEGY
		ResponseType_PENDING,
		ResponseType_SUBCRIBED,
		ResponseType_APPLIED,
		ResponseType_UNSUBSCRIBED,
		ResponseType_TERMINATED,
		ResponseType_UPDATES,
		ResponseType_EXCHANGE_DISCONNECT,

		// TRACKER
		ResponseType_TRACKER,
	};

}  // namespace Lancelot
#endif	// LANCELOT_INCLUDE_ENUMS_HPP
