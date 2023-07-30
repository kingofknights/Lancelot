//
// Created by kingofknights on 7/15/23.
//

#ifndef LANCELOT_INCLUDE_LANCELOT_API_STRATEGY_STRATEGY_HPP_
#define LANCELOT_INCLUDE_LANCELOT_API_STRATEGY_STRATEGY_HPP_
#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_map>

namespace Lancelot {
	enum Side : int;

	namespace API {

		class Strategy;
		class StockPacket;

		using StrategyPtrT	  = std::shared_ptr<Strategy>;
		using StockPacketPtrT = std::shared_ptr<StockPacket>;
		using StrategyParamT  = std::unordered_map<std::string, std::string>;

		class Strategy : public std::enable_shared_from_this<Strategy> {
		public:
			explicit Strategy(int strategy_);

			virtual ~Strategy();

			void paramEventManager(const StrategyParamT& param_);
			void marketEventManager(int token_);
			void orderEventManager(int uniqueID_);
			void stopEventManager();

			[[nodiscard]] bool activated() const;
			void			   setActivated(bool activated_);

			[[nodiscard]] int getStrategy() const;
			void			  setStrategy(int strategy_);

			template <class Child>
			[[nodiscard]] static StrategyPtrT CreateInstance(int pf_, StrategyParamT strategyParameter_) {
				return std::make_shared<Child>(pf_, strategyParameter_);
			}

		protected:
			virtual void paramEvent(const StrategyParamT& param_) = 0;
			virtual void marketEvent(int token_)				  = 0;
			virtual void orderEvent(int uniqueID_)				  = 0;
			virtual void stopEvent()							  = 0;

			void destroy();

			StockPacketPtrT getStockPacket(int token_, Side side_, const std::string& client_, const std::string& algo_, int ioc_, bool needEvent_ = false);

		private:
			void registerForData(int token_);
			void registerSelf();

		private:
			bool _activated;
			int	 _strategy;

		private:
			pthread_mutex_t _mutex;

			using uniqueTokenT = std::set<int>;
			uniqueTokenT _uniqueToken;
		};
	}  // namespace API
}  // namespace Lancelot
#endif	// LANCELOT_INCLUDE_LANCELOT_API_STRATEGY_STRATEGY_HPP_
