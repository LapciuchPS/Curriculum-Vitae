#pragma once

#include "library_details/Predicators.hpp"
#include <algorithm>
#include <iterator>

namespace ceb
{
	template <typename Container_it, typename Condition = ceb::details::increasingly_t>
	void cocktail_sort(Container_it begin_it, Container_it end_it, Condition condition = {})
	{
		if (not ceb::details::is_sortable(begin_it, end_it))
			return;

			Container_it curr_it = begin_it;
			Container_it next_it = std::next(curr_it);
			Container_it new_begin_it = begin_it;
			Container_it new_end_it = end_it;
			bool was_swapped{};
			bool going_end = true;

			auto process_condition = [&condition, &was_swapped](Container_it& curr_it, Container_it& next_it)
				{
					if (not condition(*curr_it, *next_it))
					{
						std::iter_swap(curr_it, next_it);
						was_swapped = true;
					}
				};

				do
				{
					was_swapped = false;

					//going right
					if (going_end)
					{
						while (next_it != new_end_it)
						{
							process_condition(curr_it, next_it);

							++curr_it;
							++next_it;
						}
						new_end_it = curr_it;
						going_end = false;

						curr_it = ceb::details::get_previous_it(begin_it, curr_it);
						next_it = ceb::details::get_previous_it(begin_it, next_it);

					}
					else //going left
					{
						while (curr_it != new_begin_it)
						{
							process_condition(curr_it, next_it);

							curr_it = ceb::details::get_previous_it(begin_it, curr_it);
							next_it = ceb::details::get_previous_it(begin_it, next_it);
						}

						//last condition at the begining of the container
						process_condition(curr_it, next_it);

						new_begin_it = curr_it;
						going_end = true;
						++curr_it;
						++next_it;
					}

				} while (was_swapped);
	}
}