#include <iostream>
#include <vector>

template <typename T>
void InsertionSort(std::vector<T>& container);

int main()
{
    std::vector<float> numbers{ 23,43,21,4,6,2,7,1};

    InsertionSort(numbers);

    for (auto& elem : numbers)
        std::cout << elem << " ";
}

template <typename T>
void InsertionSort(std::vector<T>& container)
{
    if (container.size() < 2) return;

   for(size_t starting_index = 1; starting_index <container.size(); starting_index++)
   {
       for (size_t curr_index = starting_index; curr_index > 0; curr_index--)
       {
           if (container[curr_index] >= container[curr_index - 1])
               break;

              std::swap(container[curr_index], container[curr_index - 1]);
       }
   }
}