#ifndef STALIN_SORT_HPP
#define STALIN_SORT_HPP

#include "Predicators.hpp"

#include <iterator>
#include <unordered_map>
#include <algorithm>
#include <functional>

namespace ceb
{
	//works for vector, list and deque container
	template<typename Container, typename Condition = ceb::increasingly_t>
	void stalin_sort(Container& container, Condition condition = {})
	{
		if (container.empty())
			return;

		typename Container::iterator curr_it = container.begin();
		typename Container::iterator next_it = std::next(container.begin());
		auto last_kept = *curr_it;

		while (next_it != container.end())
		{
			
			if (not condition(last_kept, *next_it))
				next_it = container.erase(next_it);
			else
			{
				curr_it = next_it;
				last_kept = *curr_it;
				++next_it;
			}
		}
	}

	template<typename T, typename Condition = ceb::increasingly_t>
	void stalin_sort(std::forward_list<T>& forward_list, Condition condition = {})
	{
		if (forward_list.empty())
			return;

		typename std::forward_list<T>::iterator curr_it = forward_list.begin();

		while(std::next(curr_it) != forward_list.end())
		{
			if (not condition(*curr_it, *std::next(curr_it)))
				forward_list.erase_after(curr_it);
			else
				++curr_it;
		}
	}
}

#endif
