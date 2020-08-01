#include "primitives.h"
namespace midi
{
	Duration operator+(const Duration& left, const Duration& right)
	{
		return Duration(value(left) + value(right));
	}
	Time operator+(const Time& left, const Duration& right)
	{
		return Time(value(left) + value(right));
	}
	Time operator+(const Duration& left, const Time& right)
	{
		return Time(value(right) + value(left));
	}
	Duration operator-(const Time& left, const Time& right)
	{
		return Duration(value(left) - value(right));
	}
	Duration operator-(const Duration& left, const Duration& right)
	{
		return Duration(value(left) - value(right));
	}
	Time& operator+=(Time& left, const Duration& right)
	{
		value(left) += value(right);
		return left;
	}
	Duration& operator+=(Duration& left, const Duration& right)
	{
		value(left) += value(right);
		return left;
	}
	Duration& operator-=(Duration& left, const Duration& right)
	{
		value(left) -= value(right);
		return left;
	}
}