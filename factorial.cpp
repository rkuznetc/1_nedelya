#include <iostream>

template <unsigned int N>
constexpr unsigned int factorial(){
    return factorial<(N-1)>() * N;
}

template <>
constexpr unsigned int factorial<0>() {
    return 1;
}


int main(){
    std::cout << factorial<0>() << "\n" << factorial<1>() << "\n" <<
        factorial<2>() << "\n" << factorial<3>() << "\n" << factorial<10>();
    return 0;
}   