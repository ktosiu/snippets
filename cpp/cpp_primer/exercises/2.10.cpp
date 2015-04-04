#include <iostream>
#include <string>

std::string global_string;
int global_int;

int main () {
    std::cout << "global_string: " << global_string << std::endl;
    std::cout << "global_int: "<< global_int << std::endl;

    std::string local_string;
    int local_int;
    std::cout << "local_string: " << local_string << std::endl;
    std::cout << "local_int: " << local_int << std::endl;
    return 0;
}
