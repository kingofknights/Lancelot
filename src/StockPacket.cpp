//
// Created by kingofknights on 7/14/23.
//

#include "Lancelot/API/Common/StockPacket.hpp"

#include "Lancelot/API/Common/Common.hpp"
namespace Lancelot::API {
	int Position::getLastQuantity() const { return _lastQuantity; }
	int Position::getLastPrice() const { return _lastPrice; }
	int Position::getTotalQuantity() const { return _totalQuantity; }

	void Position::setLastQuantity(int lastQuantity_) { _lastQuantity = lastQuantity_; }
	void Position::setLastPrice(int lastPrice_) { _lastPrice = lastPrice_; }
	void Position::setTotalQuantity(int totalQuantity_) { _totalQuantity = totalQuantity_; }

	int Internal::getUniqueClassIdentity() const { return _uniqueClassIdentity; }
	int Internal::getStrategyNumber() const { return _strategyNumber; }

	void Internal::setUniqueClassIdentity(int uniqueClassIdentity_) { _uniqueClassIdentity = uniqueClassIdentity_; }
	void Internal::setStrategyNumber(int strategyNumber_) { _strategyNumber = strategyNumber_; }

	const ResultSetT   *Internal::getResultSetPtr() const { return _resultSetPtr; }
	const AdaptorPtrT  &Internal::getAdaptorPtr() const { return _adaptorPtr; }
	const StrategyPtrT &Internal::getStrategyPtr() const { return _strategyPtr; }

	void Internal::setResultSetPtr(const ResultSetT *resultSetPtr_) { _resultSetPtr = resultSetPtr_; }
	void Internal::setAdaptorPtr(const AdaptorPtrT &adaptorPtr_) { _adaptorPtr = adaptorPtr_; }
	void Internal::setStrategyPtr(const StrategyPtrT &strategyPtr_) { _strategyPtr = strategyPtr_; }

	bool			   OrderDetails::isIoc() const { return _ioc; }
	Side			   OrderDetails::getSide() const { return _side; }
	int				   OrderDetails::getPrice() const { return _price; }
	int				   OrderDetails::getQuantity() const { return _quantity; }
	long			   OrderDetails::getOrderNumber() const { return _orderNumber; }
	const std::string &OrderDetails::getClientCode() const { return _clientCode; }
	const std::string &OrderDetails::getAlgoCode() const { return _algoCode; }

	void OrderDetails::setSide(Side side_) { _side = side_; }
	void OrderDetails::setIoc(bool ioc_) { _ioc = ioc_; }
	void OrderDetails::setPrice(int price_) { _price = price_; }
	void OrderDetails::setQuantity(int quantity_) { _quantity = quantity_; }
	void OrderDetails::setOrderNumber(long orderNumber_) { _orderNumber = orderNumber_; }
	void OrderDetails::setClientCode(const std::string &clientCode_) { _clientCode = clientCode_; }
	void OrderDetails::setAlgoCode(const std::string &algoCode_) { _algoCode = algoCode_; }

	StockPacket::StockPacket() : _lastRequest(OrderRequest_NONE), _currentStatus(OrderStatus_NONE), _previousStatus(OrderStatus_NONE) {}
	void StockPacket::setLastRequest(OrderRequest lastRequest_) { _lastRequest = lastRequest_; }
	void StockPacket::setCurrentStatus(OrderStatus currentStatus_) { _currentStatus = currentStatus_; }
	void StockPacket::setPreviousStatus(OrderStatus previousStatus_) { _previousStatus = previousStatus_; }

	OrderRequest StockPacket::getLastRequest() const { return _lastRequest; }
	OrderStatus	 StockPacket::getCurrentStatus() const { return _currentStatus; }
	OrderStatus	 StockPacket::getPreviousStatus() const { return _previousStatus; }

}  // namespace Lancelot::API