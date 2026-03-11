#ifndef GNOME_SORT_HPP
#define GNOME_SORT_HPP

#include <cebulka_sort/library_details/Predicators.hpp>
#include <forward_list>
#include <algorithm>
#include <iterator>

namespace ceb
{
	template <typename Container_it, typename Condition = ceb::increasingly_t>
	void gnome_sort(Container_it begin_it, Container_it end_it, Condition condition={})
	{
		if (not ceb::is_sortable(begin_it, end_it))
			return;

		Container_it curr_it = begin_it;
		Container_it next_it = std::next(curr_it);

		while (next_it != end_it)
		{

			if (not condition(*curr_it, *next_it))
			{
				std::iter_swap(curr_it, next_it);

				if (curr_it != begin_it)
				{
					--curr_it;
					--next_it;
					continue;
				}					
			}
			
			++curr_it;
			++next_it;
		}
	}

	/*	template <typename Condition = ceb::increasingly_t>
	void gnome_sort(std::forward_iterator begin_it, std::forward_iterator end_it, Condition condition = {})
	{
		if (not ceb::is_sortable(begin_it, end_it))
			return;

		Container_it curr_it = begin_it;
		Container_it next_it = std::next(curr_it);
		Container_it previous_it = curr_it;


		while (next_it != end_it)
		{

			if (not condition(*curr_it, *next_it))
			{
				std::swap(*curr_it, *next_it);

				if (curr_it != begin_it)
				{
					next_it = curr_it;
					curr_it = previous_it;

					if (previous_it != begin_it)
						previous_it = ceb::get_previous_it(begin_it, previous_it);
				}

			}
			else
			{
				previous_it = curr_it++;
				++next_it;
			}
		}
	}*/
}

#endif