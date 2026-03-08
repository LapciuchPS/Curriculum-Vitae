#ifndef PREDICATORS_HPP
#define PREDICATORS_HPP

namespace ceb
{
	struct increasingly_t
	{
		template<typename T1, typename T2>
		bool operator()(const T1& el1, const T2& el2)
		{
			return el1 <= el2;
		}
	};

	struct decreasingly_t
	{
		template<typename T1, typename T2>
		bool operator()(const T1& el1, const T2& el2)
		{
			return el1 >= el2;
		}
	};

	constexpr increasingly_t increasingly{};
	constexpr decreasingly_t decreasingly{};
}

#endif