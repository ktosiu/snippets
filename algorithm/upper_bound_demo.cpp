#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> data;// = { 1,1,2,3,4,6};
    auto lower = std::lower_bound(data.begin(), data.end(), 1);
    auto upper = std::upper_bound(data.begin(), data.end(), 1);
    std::copy(lower, upper, std::ostream_iterator<int>(std::cout, ""));
}
