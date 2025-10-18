#pragma once

namespace doubleCompare {

constexpr double epsilon = 1.0e-7;

bool isEqual(const double, const double);
bool isLess(const double, const double);
bool isLessOrEqual(const double, const double);
bool isGreater(const double, const double);
bool isGreaterOrEqual(const double, const double);

} // namespace doubleCompare