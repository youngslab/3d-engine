#include <ox/entity.h>
#include <boost/type_index.hpp>
#include <iostream>

template <typename T>
void printNameOfType() {
  std::cout << "Type of T: " << boost::typeindex::type_id<T>().pretty_name()
            << std::endl;
}

int main() { printNameOfType<ox::components>(); }
