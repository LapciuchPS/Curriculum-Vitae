#ifndef PREDICATORS_HPP
#define PREDICATORS_HPP

#include <iterator>
#include <type_traits>

namespace ceb::details
{
	//extra algorithms used for sorting

	template<typename Container_it>
	bool is_sortable(Container_it begin_it, Container_it end_it)
	{
		//container is not sortable if it contains none or only one element
		return (begin_it == end_it || ++begin_it == end_it) ? false : true;
	}

	//count the previous iterator manually (works for the forward iterator)
	template<typename Container_it>
	Container_it prev(Container_it begin_it, Container_it curr_it)
	{
		Container_it previous_it = begin_it;

		while (std::next(previous_it) != curr_it)
			previous_it++;

		return previous_it;
	}

	template<typename Container_it>
	constexpr bool is_it_bidirectional()
	{
		using input_it_type = std::iterator_traits<Container_it>::iterator_category;

		return std::is_base_of_v<std::bidirectional_iterator_tag, input_it_type>;
	}

	template<typename Container_it>
	Container_it get_previous_it(Container_it begin_it, Container_it curr_it)
	{
		if constexpr (is_it_bidirectional<Container_it>())
		{
			--curr_it;
			return curr_it;
		}
		else
			return prev(begin_it, curr_it);
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
}

namespace ceb
{
	constexpr details::increasingly_t increasingly{};
	constexpr details::decreasingly_t decreasingly{};
}

#endif