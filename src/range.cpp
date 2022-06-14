#include "ts/range.hpp"

#include "ts/point.hpp"

#include <ostream>

using ts::Range;

bool operator==(const Range& a, const Range& b) {
	return ((a.start_point.row 		== b.start_point.row) &&
			(a.start_point.column 	== b.start_point.column) &&
			(a.start_byte 			== b.start_byte) &&
			(a.end_point.row 		== b.end_point.row) &&
			(a.end_point.column 	== b.end_point.column) &&
			(a.end_byte 			== b.end_byte));
}

bool operator!=(const Range& a, const Range& b) {
	return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Range& r) {
	return os << "<ts::Range start_point=" << r.start_point
			<< ", start_byte=" << r.start_byte
			<< ", end_point=" << r.end_point
			<< ", end_byte" << r.end_byte << '>';
}