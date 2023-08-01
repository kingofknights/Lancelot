//
// Created by kingofknights on 7/14/23.
//

#ifndef LANCELOT_INCLUDE_LANCELOT_API_COMMON_STOCK_PACKET_HPP_
#define LANCELOT_INCLUDE_LANCELOT_API_COMMON_STOCK_PACKET_HPP_
#pragma once

#include <memory>
#include <string>

namespace Lancelot {
	enum Side : int;
	struct ResultSetT;
	using ResultSetPtrT = const ResultSetT *;

	namespace API {
		enum OrderStatus : int;
		enum OrderRequest : int;
		class Strategy;
		class Adaptor;
		class CustomUserAllocation {
		public:
			virtual ~CustomUserAllocation() = default;
		};

		using StrategyPtrT = std::shared_ptr<Strategy>;
		using AdaptorPtrT  = std::shared_ptr<Adaptor>;

		class Position {
		public:
		private:
		public:
			[[nodiscard]] int getLastTradeQuantity() const;
			[[nodiscard]] int getLastTradePrice() const;
			[[nodiscard]] int getTotalTradeQuantity() const;

			void setLastTradeQuantity(int lastTradeQuantity_);
			void setLastTradePrice(int lastTradePrice_);
			void setTotalTradeQuantity(int totalTradeQuantity_);

		private:
			int _lastTradeQuantity	= 0;
			int _lastTradePrice		= 0;
			int _totalTradeQuantity = 0;
		};

		class Internal {
		public:
			[[nodiscard]] int getUniqueClassIdentity() const;
			[[nodiscard]] int getStrategyNumber() const;

			[[nodiscard]] const ResultSetT	   *getResultSetPtr() const;
			[[nodiscard]] const AdaptorPtrT	   &getAdaptorPtr() const;
			[[nodiscard]] const StrategyPtrT   &getStrategyPtr() const;
			[[nodiscard]] CustomUserAllocation *getUserAllocationPtr() const;

			virtual ~Internal();
			Internal();

			void setStrategyNumber(int strategyNumber_);
			void setResultSetPtr(const ResultSetT *resultSetPtr_);
			void setAdaptorPtr(const AdaptorPtrT &adaptorPtr_);
			void setStrategyPtr(const StrategyPtrT &strategyPtr_);
			void setUserAllocationPtr(CustomUserAllocation *userAllocationPtr_);

		private:
			int _uniqueClassIdentity = 0;
			int _strategyNumber		 = 0;

			ResultSetPtrT		  _resultSetPtr;
			AdaptorPtrT			  _adaptorPtr;
			StrategyPtrT		  _strategyPtr;
			CustomUserAllocation *_userAllocationPtr;
		};

		class OrderDetails {
		public:
			[[nodiscard]] bool isIoc() const;
			[[nodiscard]] Side getSide() const;
			[[nodiscard]] int  getToken() const;
			[[nodiscard]] int  getPrice() const;
			[[nodiscard]] int  getQuantity() const;
			[[nodiscard]] long getOrderNumber() const;

			[[nodiscard]] const std::string &getClientCode() const;
			[[nodiscard]] const std::string &getAlgoCode() const;
			[[nodiscard]] const std::string &getContractDescription() const;

			void setToken(int token_);
			void setSide(Side side_);
			void setPrice(int price_);
			void setQuantity(int quantity_);
			void setIoc(bool ioc_);
			void setOrderNumber(long orderNumber_);
			void setClientCode(const std::string &clientCode_);
			void setAlgoCode(const std::string &algoCode_);
			void setContractDescription(const std::string &contractDescription_);

		private:
			bool _ioc;
			Side _side;
			int	 _token;
			int	 _price;
			int	 _quantity;
			long _orderNumber;

			std::string _clientCode;
			std::string _algoCode;
			std::string _contractDescription;
		};
		class StockPacket : public Position, public Internal, public OrderDetails, public std::enable_shared_from_this<StockPacket> {
		public:
			explicit StockPacket();
			[[nodiscard]] OrderRequest getLastRequest() const;
			[[nodiscard]] OrderStatus  getCurrentStatus() const;
			[[nodiscard]] OrderStatus  getPreviousStatus() const;

			void setLastRequest(OrderRequest lastRequest_);
			void setCurrentStatus(OrderStatus currentStatus_);
			void setPreviousStatus(OrderStatus previousStatus_);

			bool execute(int price_, int quantity_, OrderRequest request_);
			void executionReport(OrderStatus orderStatus_);

		private:
			OrderRequest _lastRequest;
			OrderStatus	 _currentStatus;
			OrderStatus	 _previousStatus;
		};

	}  // namespace API
}  // namespace Lancelot

#endif	// LANCELOT_INCLUDE_LANCELOT_API_COMMON_STOCK_PACKET_HPP_
