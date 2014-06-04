#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> v = {4, 6, 7, 2, 0, 9, 19};
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ""));
    std::cout<<std::endl;

    std::rotate(v.begin(), v.begin()+1, v.end());
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ""));
    std::cout<<std::endl;

    std::rotate(v.rbegin(), v.rbegin()+1, v.rend());
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ""));
    std::cout<<std::endl;
}
