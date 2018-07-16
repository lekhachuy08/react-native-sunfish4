#include "Usi.hpp"
#include "../../common/string/StringUtil.hpp"
#include "../../common/resource/Resource.hpp"
#include "../../common/thread/ScopedThread.hpp"
#include "../../book/BookUtil.hpp"
#include "../../core/record/SfenParser.hpp"
#include "../../search/eval/Material.hpp"
#include "../../logger/Logger.hpp"
#include <iomanip>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <functional>
#include <chrono>
#include <cctype>
#include <cstdint>
#include <cstdlib>

namespace sunfish {
	
	Usi::Usi() : breakReceiver_(false), isBookLoaded(false) {	
		options_.ponder = true;
		options_.hash = 0;
		options_.useBook = true;
		options_.snappy = true;
		options_.marginMs = 500;
		options_.numberOfThreads = 1;
		options_.maxDepth = Searcher::DepthInfinity;
		
		searcher_.reset(new Searcher(Evaluator::sharedEvaluator()));
		searcher_->setHandler(this);
		
		if (!isBookLoaded) {
			book_.load();
			isBookLoaded = true;
		}
		
//		lastPositionCommand_ = command.value;
	}
	
	std::string Usi::getBestMove(const std::string listOfMoves) {
		auto args = StringUtil::split("position startpos moves " + listOfMoves, [](char c) {
			return isspace(c);
		});
		
		lastPositionCommand_ = "position startpos moves " + listOfMoves;
		if (!SfenParser::parseUsiCommand(args.begin(),
										 args.end(),
										 record_)) {
			return "err: resign";
		}
		
		return runSearch();
	}
	
	std::string Usi::runSearch() {
		blackTimeMs_ = 0;
		whiteTimeMs_ = 0;
		byoyomiMs_ = 0;
		blackIncMs_ = 0;
		whiteIncMs_ = 0;
		isInfinite_ = false;
		
		// check opening book
		if (options_.useBook) {
			auto pos = generatePosition(record_, -1);
			Move bookMove = BookUtil::select(book_, pos, random_);
			if (!bookMove.isNone()) {
				return bookMove.toStringSFEN();
			}
		}
		
		searcherIsStarted_ = false;
		stopCommandReceived_ = false;
		inPonder_ = false;
		
		return search();
	}
	
	std::string Usi::search() {
		auto pos = generatePosition(record_, -1);
		auto config = searcher_->getConfig();
		
		bool isBlack = pos.getTurn() == Turn::Black;
		TimeType remainingTimeMs = isBlack ?  blackTimeMs_ : whiteTimeMs_;
		TimeType incrementMs = isBlack ?  blackIncMs_ : whiteIncMs_;
		config.maximumTimeMs = remainingTimeMs + byoyomiMs_ - options_.marginMs;
		config.optimumTimeMs = std::max(remainingTimeMs / 50,
										std::min(remainingTimeMs, byoyomiMs_ + incrementMs))
		+ byoyomiMs_;
		
		if (options_.snappy) {
			config.optimumTimeMs /= 3;
		}
		
		if (!options_.snappy && remainingTimeMs == 0 && incrementMs == 0) {
			config.optimumTimeMs = SearchConfig::InfinityTime;
		}
		
		config.numberOfThreads = options_.numberOfThreads;
		
		searcher_->setConfig(config);
		
		searcher_->idsearch(pos, options_.maxDepth * Searcher::Depth1Ply, &record_);
		
		const auto& result = searcher_->getResult();
		
		if (!result.move.isNone()) {
			return result.move.toStringSFEN();
		} else {
			return "resign";
		}
	}
	
	void Usi::onStart(const Searcher&) {
		searcherIsStarted_ = true;
	}
	
	void Usi::onUpdatePV(const Searcher& searcher, const PV& pv, float elapsed, int depth, Score score) {
	}
	
	void Usi::onFailLow(const Searcher& searcher, const PV& pv, float elapsed, int depth, Score score) {
	}
	
	void Usi::onFailHigh(const Searcher& searcher, const PV& pv, float elapsed, int depth, Score score) {
	}
	
	void Usi::onIterateEnd(const Searcher& searcher, float elapsed, int depth){
	}
}
