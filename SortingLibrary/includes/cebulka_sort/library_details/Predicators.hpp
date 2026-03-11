#ifndef PREDICATORS_HPP
#define PREDICATORS_HPP

#include <iterator>

namespace ceb
{
	//extra algorithms used for sorting
	template<typename Container_it>
	bool is_sortable(Container_it begin_it, Container_it end_it)
	{
		return (begin_it == end_it || ++begin_it == end_it) ? false : true;
	}

	template<typename Container_it>
	Container_it get_previous_it(Container_it begin_it, Container_it curr_it)
	{
		Container_it previous_it = begin_it;

		while (std::next(previous_it) != curr_it)
			previous_it++;

		return previous_it;
	}
	
	//defined sorting conditions
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