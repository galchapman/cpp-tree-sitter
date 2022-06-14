#include "ts/point.hpp"

std::ostream& operator<<(std::ostream& os, const ts::Point& p) {
	return os << '(' << p.row << ", " << p.column << ')';
}