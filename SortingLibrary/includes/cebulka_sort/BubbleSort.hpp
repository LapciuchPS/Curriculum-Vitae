#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include "library_details/Predicators.hpp"
#include <algorithm>
#include <iterator>

namespace ceb
{
	template<typename Container_it, typename Condition = ceb::details::decreasingly_t>
	void bubble_sort(Container_it begin_it, Container_it end_it, Condition condition = {})
	{
		if (not ceb::details::is_sortable(begin_it, end_it))
			return;

		Container_it last_it = end_it;
		bool was_swapped{};

		//iterate unless no swap was made
		do
		{
			was_swapped = false;
			Container_it curr_it = begin_it;
			Container_it next_it = std::next(curr_it);
			Container_it last_swapped_it = end_it;

			//one iteration through a container
			while(next_it != last_it)
			{
				if (not condition(*curr_it, *next_it))
				{
					std::iter_swap(curr_it, next_it);
					was_swapped = true;
					last_swapped_it = next_it;
				}

				++curr_it;
				++next_it;
			}

			last_it = last_swapped_it;

		} while(was_swapped);
	}
}

#endif