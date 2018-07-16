#ifndef SUNFISH_USI_USI_HPP__
#define SUNFISH_USI_USI_HPP__

#include "../../common/math/Random.hpp"
#include "../../core/position/Position.hpp"
#include "../../core/record/Record.hpp"
#include "../../book/Book.hpp"
#include "../../search/Searcher.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include <queue>
#include <cstdint>

namespace sunfish {
	
	class Usi : public SearchHandler {
	private:
		
		using CommandArguments = std::vector<std::string>;
		
		using TimeType = SearchConfig::TimeType;
		
		struct Options {
			bool ponder;
			unsigned hash;
			bool useBook;
			bool snappy;
			int marginMs;
			int numberOfThreads;
			int maxDepth;
		};
		
		enum class CommandState : uint8_t {
			Ok,
			Error,
			Broken,
		};
		
		struct Command {
			CommandState state;
			std::string value;
		};
		
	public:
		
		Usi();
		std::string getBestMove(const std::string listOfMoves);
		
	private:
		
		std::string runSearch();
		
		std::string search();
		
		void onStart(const Searcher&) override;
		void onUpdatePV(const Searcher& searcher, const PV& pv, float elapsed, int depth, Score score) override;
		void onFailLow(const Searcher& searcher, const PV& pv, float elapsed, int depth, Score score) override;
		void onFailHigh(const Searcher& searcher, const PV& pv, float elapsed, int depth, Score score) override;
		void onIterateEnd(const Searcher& searcher, float elapsed, int depth) override;
		
		Options options_;
		
		std::queue<std::string> deferredCommands_;
		std::queue<Command> commandQueue_;
		
		std::string lastPositionCommand_;
		std::string lastGoCommand_;
		
		Record record_;
		
		TimeType blackTimeMs_;
		TimeType whiteTimeMs_;
		TimeType byoyomiMs_;
		TimeType blackIncMs_;
		TimeType whiteIncMs_;
		bool isInfinite_;
		bool inPonder_;
		
		std::unique_ptr<Searcher> searcher_;
		std::atomic<bool> searcherIsStarted_;
		std::atomic<bool> stopCommandReceived_;
		std::atomic<bool> breakReceiver_;
		
		Book book_;
		bool isBookLoaded;
		
		Random random_;
		
		std::mutex sendMutex_;
		std::mutex receiveMutex_;
		std::thread receiver_;
		
	};
	
} // namespace sunfish

#endif // SUNFISH_USI_USI_HPP__
