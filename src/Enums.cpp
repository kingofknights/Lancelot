//
// Created by kingofknights on 7/9/23.
//

#include "Lancelot/Enums.hpp"

#include "Lancelot/API/Common/Common.hpp"
namespace Lancelot {

	std::string toString(Exchange exchangeCode_) {
		switch (exchangeCode_) {
			case Exchange_NSE_FUTURE: return "NSE_FUTURE";
			case Exchange_NSE_EQUITY: return "NSE_EQUITY";
			case Exchange_NSE_CURRENCY: return "NSE_CURRENCY";
			case Exchange_BSE_FUTURE: return "BSE_FUTURE";
			case Exchange_BSE_CURRENCY: return "BSE_CURRENCY";
			case Exchange_END: return "Exchange_END";
		}
		return __FUNCTION__;
	}

	std::string toString(Instrument instrument_) {
		switch (instrument_) {
			case Instrument_FUTURE: return "Instrument_FUTURE";
			case Instrument_OPTION: return "Instrument_OPTION";
			case Instrument_EQUITY: return "Instrument_EQUITY";
			case Instrument_OTHER: return "Instrument_OTHER";
		}
		return __FUNCTION__;
	}

	std::string toString(OptionType optionType_) {
		switch (optionType_) {
			case OptionType_NONE: return "OptionType_NONE";
			case OptionType_CALL: return "OptionType_CALL";
			case OptionType_PUT: return "OptionType_PUT";
		}
		return __FUNCTION__;
	}

	std::string toString(Side side_) {
		switch (side_) {
			case Side_BUY: return "Side_BUY";
			case Side_SELL: return "Side_SELL";
		}
		return __FUNCTION__;
	}

	std::string toString(RequestType requestType_) {
		switch (requestType_) {
			case RequestType_LOGIN: return "RequestType_LOGIN";
			case RequestType_NEW: return "RequestType_NEW";
			case RequestType_MODIFY: return "RequestType_MODIFY";
			case RequestType_CANCEL: return "RequestType_CANCEL";
			case RequestType_APPLY: return "RequestType_APPLY";
			case RequestType_SUBSCRIBE: return "RequestType_SUBSCRIBE";
			case RequestType_UNSUBSCRIBE: return "RequestType_UNSUBSCRIBE";
			case RequestType_SUBSCRIBE_APPLY: return "RequestType_SUBSCRIBE_APPLY";
		}
		return __FUNCTION__;
	}

	std::string toString(ResponseType responseType_) {
		switch (responseType_) {
			case ResponseType_PLACED: return "ResponseType_PLACED";
			case ResponseType_NEW: return "ResponseType_NEW";
			case ResponseType_REPLACED: return "ResponseType_REPLACED";
			case ResponseType_CANCELLED: return "ResponseType_CANCELLED";
			case ResponseType_NEW_REJECT: return "ResponseType_NEW_REJECT";
			case ResponseType_REPLACE_REJECT: return "ResponseType_REPLACE_REJECT";
			case ResponseType_CANCEL_REJECT: return "ResponseType_CANCEL_REJECT";
			case ResponseType_PARTIAL_FILLED: return "ResponseType_PARTIAL_FILLED";
			case ResponseType_FILLED: return "ResponseType_FILLED";
			case ResponseType_PENDING: return "ResponseType_PENDING";
			case ResponseType_SUBCRIBED: return "ResponseType_SUBCRIBED";
			case ResponseType_APPLIED: return "ResponseType_APPLIED";
			case ResponseType_UNSUBSCRIBED: return "ResponseType_UNSUBSCRIBED";
			case ResponseType_TERMINATED: return "ResponseType_TERMINATED";
			case ResponseType_UPDATES: return "ResponseType_UPDATES";
			case ResponseType_EXCHANGE_DISCONNECT: return "ResponseType_EXCHANGE_DISCONNECT";
			case ResponseType_TRACKER: return "ResponseType_TRACKER";
		}
		return __FUNCTION__;
	}

	namespace API {
		std::string toString(OrderType orderType_) {
			switch (orderType_) {
				case OrderType_LIMIT: return "OrderType_LIMIT";
				case OrderType_MARKET: return "OrderType_MARKET";
				case OrderType_IOC: return "OrderType_IOC";
				case OrderType_SPREAD: return "OrderType_SPREAD";
			}
			return __FUNCTION__;
		}

		std::string toString(StrategyStatus status_) {
			switch (status_) {
				case StrategyStatus_PENDING: return "StrategyStatus_PENDING";
				case StrategyStatus_ACTIVE: return "StrategyStatus_ACTIVE";
				case StrategyStatus_APPLIED: return "StrategyStatus_APPLIED";
				case StrategyStatus_INACTIVE: return "StrategyStatus_INACTIVE";
				case StrategyStatus_TERMINATED: return "StrategyStatus_TERMINATED";
				case StrategyStatus_WAITING: return "StrategyStatus_WAITING";
				case StrategyStatus_DISCONNECTED: return "StrategyStatus_DISCONNECTED";
			}
			return __FUNCTION__;
		}
		std::string toString(OrderStatus status_) {
			switch (status_) {
				case OrderStatus_NONE: return "OrderStatus_NONE";
				case OrderStatus_PLACED: return "OrderStatus_PLACED";
				case OrderStatus_NEW: return "OrderStatus_NEW";
				case OrderStatus_REPLACED: return "OrderStatus_REPLACED";
				case OrderStatus_CANCELLED: return "OrderStatus_CANCELLED";
				case OrderStatus_NEW_REJECT: return "OrderStatus_NEW_REJECT";
				case OrderStatus_REPLACE_REJECT: return "OrderStatus_REPLACE_REJECT";
				case OrderStatus_CANCEL_REJECT: return "OrderStatus_CANCEL_REJECT";
				case OrderStatus_PARTIAL_FILLED: return "OrderStatus_PARTIAL_FILLED";
				case OrderStatus_FILLED: return "OrderStatus_FILLED";
				case OrderStatus_PENDING: return "OrderStatus_PENDING";
				case OrderStatus_ADAPTOR_REJECT: return "OrderStatus_ADAPTOR_REJECT";
			}
			return __FUNCTION__;
		}
		std::string toString(OrderRequest request_) {
			switch (request_) {
				case OrderRequest_NONE: return "OrderRequest_NONE";
				case OrderRequest_NEW: return "OrderRequest_NEW";
				case OrderRequest_MODIFY: return "OrderRequest_MODIFY";
				case OrderRequest_CANCEL: return "OrderRequest_CANCEL";
				case OrderRequest_IOC: return "OrderRequest_IOC";
				case OrderRequest_CANCEL_ALL: return "OrderRequest_CANCEL_ALL";
			}
			return __FUNCTION__;
		}
	}  // namespace API

}  // namespace Lancelot