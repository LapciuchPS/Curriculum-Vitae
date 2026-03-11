#ifndef GNOME_SORT_HPP
#define GNOME_SORT_HPP

#include <cebulka_sort/library_details/Predicators.hpp>
#include <forward_list>
#include <algorithm>
#include <iterator>
#include <type_traits>

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

		//determines the iterator type we work with and the algoritm implementation accordingly
		using input_it_type = std::iterator_traits<Container_it>::iterator_category;

		if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, input_it_type>)
		{
			while (next_it != end_it)
			{

				if (not condition(*curr_it, *next_it))
				{
					std::iter_swap(curr_it, next_it);

					//go backwards until both elements are in the right order
					if (curr_it != begin_it)
					{
						--curr_it;
						--next_it;
						continue;
					}
				}

				//go forward while both elements are in the right order
				// or when the swap was made at the beginnig of the container
				++curr_it;
				++next_it;
			}
		}
		else
		{
			Container_it previous_it = curr_it;

			while (next_it != end_it)
			{

				if (not condition(*curr_it, *next_it))
				{
					std::iter_swap(curr_it, next_it);

					//go backwards until both elements are in the right order
					if (curr_it != begin_it)
					{
						next_it = curr_it;
						curr_it = previous_it;

						if (previous_it != begin_it)
							previous_it = ceb::details::get_previous_it(begin_it, previous_it);

						continue;
					}

				}
				
				//go forward while both elements are in the right order
				// or when the swap was made at the beginnig of the container
					previous_it = curr_it++;
					++next_it;
			}
		}
		
	}
}

#endif