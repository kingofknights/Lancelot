//
// Created by kingofknights on 7/14/23.
//

#include "Lancelot/API/Common/StockPacket.hpp"

#include "Lancelot/API/Adaptor/Adaptor.hpp"
#include "Lancelot/API/Common/Common.hpp"
#include "Lancelot/API/Strategy/Strategy.hpp"
#include "Lancelot/Logger/Logger.hpp"

namespace Lancelot::API {

	inline static int _globalStockPacketUniqueIdentifierCounter = 1;

	int Position::getLastTradeQuantity() const { return _lastTradeQuantity; }
	int Position::getLastTradePrice() const { return _lastTradePrice; }
	int Position::getTotalTradeQuantity() const { return _totalTradeQuantity; }

	void Position::setLastTradeQuantity(int lastTradeQuantity_) { _lastTradeQuantity = lastTradeQuantity_; }
	void Position::setLastTradePrice(int lastTradePrice_) { _lastTradePrice = lastTradePrice_; }
	void Position::setTotalTradeQuantity(int totalTradeQuantity_) { _totalTradeQuantity = totalTradeQuantity_; }

	int Internal::getUniqueClassIdentity() const { return _uniqueClassIdentity; }
	int Internal::getStrategyNumber() const { return _strategyNumber; }

	void Internal::setStrategyNumber(int strategyNumber_) { _strategyNumber = strategyNumber_; }

	const ResultSetT	 *Internal::getResultSetPtr() const { return _resultSetPtr; }
	const AdaptorPtrT	 &Internal::getAdaptorPtr() const { return _adaptorPtr; }
	const StrategyPtrT	 &Internal::getStrategyPtr() const { return _strategyPtr; }
	CustomUserAllocation *Internal::getUserAllocationPtr() const { return _userAllocationPtr; }

	Internal::Internal() : _uniqueClassIdentity(++_globalStockPacketUniqueIdentifierCounter), _userAllocationPtr(nullptr) {}
	Internal::~Internal() { delete _userAllocationPtr; }
	void Internal::setResultSetPtr(const ResultSetT *resultSetPtr_) { _resultSetPtr = resultSetPtr_; }
	void Internal::setAdaptorPtr(const AdaptorPtrT &adaptorPtr_) { _adaptorPtr = adaptorPtr_; }
	void Internal::setStrategyPtr(const StrategyPtrT &strategyPtr_) { _strategyPtr = strategyPtr_; }
	void Internal::setUserAllocationPtr(CustomUserAllocation *userAllocationPtr_) { _userAllocationPtr = userAllocationPtr_; }

	bool OrderDetails::isIoc() const { return _ioc; }
	Side OrderDetails::getSide() const { return _side; }
	int	 OrderDetails::getPrice() const { return _price; }
	int	 OrderDetails::getToken() const { return _token; }
	int	 OrderDetails::getQuantity() const { return _quantity; }
	long OrderDetails::getOrderNumber() const { return _orderNumber; }

	const std::string &OrderDetails::getClientCode() const { return _clientCode; }
	const std::string &OrderDetails::getAlgoCode() const { return _algoCode; }
	const std::string &OrderDetails::getContractDescription() const { return _contractDescription; }

	void OrderDetails::setSide(Side side_) { _side = side_; }
	void OrderDetails::setIoc(bool ioc_) { _ioc = ioc_; }
	void OrderDetails::setToken(int token_) { _token = token_; }
	void OrderDetails::setPrice(int price_) { _price = price_; }
	void OrderDetails::setQuantity(int quantity_) { _quantity = quantity_; }
	void OrderDetails::setOrderNumber(long orderNumber_) { _orderNumber = orderNumber_; }
	void OrderDetails::setClientCode(const std::string &clientCode_) { _clientCode = clientCode_; }
	void OrderDetails::setAlgoCode(const std::string &algoCode_) { _algoCode = algoCode_; }
	void OrderDetails::setContractDescription(const std::string &contractDescription_) { _contractDescription = contractDescription_; }

	StockPacket::StockPacket() : _lastRequest(OrderRequest_NONE), _currentStatus(OrderStatus_NONE), _previousStatus(OrderStatus_NONE) {}
	void StockPacket::setLastRequest(OrderRequest lastRequest_) { _lastRequest = lastRequest_; }
	void StockPacket::setCurrentStatus(OrderStatus currentStatus_) { _currentStatus = currentStatus_; }
	void StockPacket::setPreviousStatus(OrderStatus previousStatus_) { _previousStatus = previousStatus_; }

	OrderRequest StockPacket::getLastRequest() const { return _lastRequest; }
	OrderStatus	 StockPacket::getCurrentStatus() const { return _currentStatus; }
	OrderStatus	 StockPacket::getPreviousStatus() const { return _previousStatus; }

	bool StockPacket::execute(int price_, int quantity_, OrderRequest request_) {
		if (not getAdaptorPtr()) {
			LOG(WARNING, "No adaptor found for stockPacket {} price {} quantity {} request {}", getUniqueClassIdentity(), price_, quantity_, Lancelot::API::toString(request_))
			return false;
		}

		auto orderStatus = getCurrentStatus();
		setCurrentStatus(OrderStatus_PENDING);

		if (getAdaptorPtr()->execute(shared_from_this(), price_, quantity_, request_)) {
			setPrice(price_);
			setQuantity(quantity_);
			return true;
		}
		setCurrentStatus(orderStatus);
		return false;
	}
	void StockPacket::executionReport(OrderStatus orderStatus_) {
		setPreviousStatus(getCurrentStatus());
		setCurrentStatus(orderStatus_);
		getStrategyPtr()->orderEventManager(getUniqueClassIdentity());
		getStrategyPtr()->updateArthur(shared_from_this());
	}

}  // namespace Lancelot::API