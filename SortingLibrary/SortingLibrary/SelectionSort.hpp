#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include <cebulka_sort/library_details/Predicators.hpp>
#include <algorithm>
#include <iterator>

namespace ceb
{
	template<typename Container_it, typename Condition = ceb::details::increasingly_t>
	void selection_sort(Container_it begin_it, Container_it end_it, Condition condition = {})
	{
		if (not ceb::details::is_sortable(begin_it, end_it))
			return;

		Container_it curr_it = begin_it;

		while(curr_it != end_it)
		{
			Container_it condition_it = curr_it;
			Container_it moving_it = std::next(curr_it);

			while (moving_it != end_it)
			{
				if (not condition(*condition_it, *moving_it))
					condition_it = moving_it;

				++moving_it;
			}
				

			if(*condition_it != *curr_it)
				std::iter_swap(curr_it, condition_it);

			++curr_it;
		}
	}
}

#endif
