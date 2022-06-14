#include "ts/symbol.hpp"

namespace ts {

std::ostream& operator<<(std::ostream& os, Symbol sym) {
	return os << "<ts.Symbol " << sym.name << ">";
}

}