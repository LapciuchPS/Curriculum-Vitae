#include <iostream>
#include <vector>

template<typename T>
void selectionSort(std::vector<T>& container);

int main()
{
    std::vector<float> numbers{ 10.4,20.4,130.5,1.5,32.1,4.3 };

    selectionSort(numbers);

    for (auto& elem : numbers)
        std::cout << elem << " ";
}

template<typename T>
void selectionSort(std::vector<T>& container)
{
    if (container.size() < 2) return;

    for (size_t starting_index = 0; starting_index < container.size(); starting_index++)
    {
        size_t index_to_swap = starting_index;
        T minimal_num = container[starting_index];

        for (size_t curr_index = starting_index + 1; curr_index < container.size(); curr_index++)
        {
            if (minimal_num > container[curr_index])
            {
                minimal_num = container[curr_index];
                index_to_swap = curr_index;
            }
               
        }

        std::swap(container[starting_index], container[index_to_swap]);
    }

}