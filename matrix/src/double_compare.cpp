#include "double_compare.hpp"

#include <cmath>

namespace doubleCompare {
bool isEqual(const double first, const double second) {
    return std::fabs(first - second) < epsilon;
}

bool isLess(const double first, const double second) {
    return first < second;
}

bool isGreater(const double first, const double second) {
    return isLess(second, first);
}

bool isLessOrEqual(const double first, const double second) {
    return (first < second || isEqual(first, second));
}

bool isGreaterOrEqual(const double first, const double second) {
    return isLessOrEqual(second, first);
}

} // namespace doubleCompare