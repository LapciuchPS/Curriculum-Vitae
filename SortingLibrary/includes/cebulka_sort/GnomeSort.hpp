#ifndef GNOME_SORT_HPP
#define GNOME_SORT_HPP

#include "library_details/Predicators.hpp"
#include <algorithm>
#include <iterator>

namespace ceb
{
	template <typename Container_it, typename Condition = ceb::details::increasingly_t>
	void gnome_sort(Container_it begin_it, Container_it end_it, Condition condition={})
	{
		if (not ceb::details::is_sortable(begin_it, end_it))
			return;

		//prepares iterators for sorting
		Container_it curr_it = begin_it;
		Container_it next_it = std::next(curr_it);

		while (next_it != end_it)
		{

			if (not condition(*curr_it, *next_it))
			{
				std::iter_swap(curr_it, next_it);

				//go backwards until both elements are in the right order
				if (curr_it != begin_it)
				{
					curr_it = ceb::details::get_previous_it(begin_it, curr_it);
					next_it = ceb::details::get_previous_it(begin_it, next_it);
					continue;
				}
			}

			//go forward while both elements are in the right order
			// or when the swap was made at the beginnig of the container
			++curr_it;
			++next_it;
		}
	}
}

#endif