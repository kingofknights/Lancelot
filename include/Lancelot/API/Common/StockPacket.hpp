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
			[[nodiscard]] int getLastQuantity() const;
			[[nodiscard]] int getLastPrice() const;
			[[nodiscard]] int getTotalQuantity() const;

			void setLastQuantity(int lastQuantity_);
			void setLastPrice(int lastPrice_);
			void setTotalQuantity(int totalQuantity_);

		private:
			int _lastQuantity  = 0;
			int _lastPrice	   = 0;
			int _totalQuantity = 0;
		};

		class Internal {
		public:
			[[nodiscard]] int getUniqueClassIdentity() const;
			[[nodiscard]] int getStrategyNumber() const;

			[[nodiscard]] const ResultSetT	 *getResultSetPtr() const;
			[[nodiscard]] const AdaptorPtrT	 &getAdaptorPtr() const;
			[[nodiscard]] const StrategyPtrT &getStrategyPtr() const;
			[[nodiscard]] CustomUserAllocation				 *getUserAllocationPtr() const;

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
			[[nodiscard]] int  getPrice() const;
			[[nodiscard]] int  getQuantity() const;
			[[nodiscard]] long getOrderNumber() const;

			[[nodiscard]] const std::string &getClientCode() const;
			[[nodiscard]] const std::string &getAlgoCode() const;

			void setSide(Side side_);
			void setPrice(int price_);
			void setQuantity(int quantity_);
			void setIoc(bool ioc_);
			void setOrderNumber(long orderNumber_);
			void setClientCode(const std::string &clientCode_);
			void setAlgoCode(const std::string &algoCode_);

		private:
			bool _ioc;
			Side _side;
			int	 _price;
			int	 _quantity;
			long _orderNumber;

			std::string _clientCode;
			std::string _algoCode;
		};
		class StockPacket : public Position, public Internal, public OrderDetails, std::enable_shared_from_this<StockPacket> {
		public:
			explicit StockPacket();
			[[nodiscard]] OrderRequest getLastRequest() const;
			[[nodiscard]] OrderStatus  getCurrentStatus() const;
			[[nodiscard]] OrderStatus  getPreviousStatus() const;

			void setLastRequest(OrderRequest lastRequest_);
			void setCurrentStatus(OrderStatus currentStatus_);
			void setPreviousStatus(OrderStatus previousStatus_);

			bool execute(int price_, int quantity_, OrderRequest request_);

		private:
			OrderRequest _lastRequest;
			OrderStatus	 _currentStatus;
			OrderStatus	 _previousStatus;
		};

	}  // namespace API
}  // namespace Lancelot

#endif	// LANCELOT_INCLUDE_LANCELOT_API_COMMON_STOCK_PACKET_HPP_
