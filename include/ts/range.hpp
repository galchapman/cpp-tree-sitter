#pragma once

#include "ts.hpp"

namespace ts {

using Range = TSRange;

}

bool operator==(const ts::Range&, const ts::Range&);
bool operator!=(const ts::Range&, const ts::Range&);

std::ostream& operator<<(std::ostream&, const ts::Range&);