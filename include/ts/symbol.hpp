#pragma once

#include "tree_sitter/api.h"
#include <ostream>

extern "C" {

namespace ts {

class Symbol {
public:
	constexpr Symbol(TSSymbol symbol, const char* name)
		: symbol(symbol), name(name) {}

	TSSymbol symbol;
	const char* name;
};

}

}

extern std::ostream& operator<<(std::ostream&, ts::Symbol);