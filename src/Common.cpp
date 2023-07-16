#include "Lancelot/API/Common/Common.hpp"

namespace Lancelot::API {
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
}  // namespace Lancelot::API
