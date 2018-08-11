
#import "RNSunfish.h"
#import "usi/client/Usi.hpp"
#include "core/util/CoreUtil.hpp"
#include "search/util/SearchUtil.hpp"

@implementation RNSunfish

RCT_EXPORT_MODULE();

RCT_EXPORT_METHOD(getBestMove: (NSString *)listOfMoves
				  callback: (RCTResponseSenderBlock) callback) {
	sunfish::Usi usi;
	std::string thisMoves = std::string([listOfMoves UTF8String]);
	std::string result = usi.getBestMove(thisMoves);
	NSString *thingToReturn = [NSString stringWithUTF8String:result.c_str()];
	callback(@[[NSNull null], thingToReturn]);
}

RCT_EXPORT_METHOD(init: (NSString *)s) {
	sunfish::CoreUtil::initialize();
	sunfish::SearchUtil::initialize();
}

@end
