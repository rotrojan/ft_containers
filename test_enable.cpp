// #define IS_INTEGRAL(x) template <>\
	// struct is_integral<x> {\
	// static bool const value = true;\
// }

// IS_INTEGRAL(bool);
// IS_INTEGRAL(char);
// IS_INTEGRAL(char16_t);
// IS_INTEGRAL(char32_t);
// IS_INTEGRAL(wchar_t);
// IS_INTEGRAL(signed char);
// IS_INTEGRAL(short int);
// IS_INTEGRAL(int);
// IS_INTEGRAL(long int);
// IS_INTEGRAL(long long int);
// IS_INTEGRAL(unsigned char);
// IS_INTEGRAL(unsigned short int);
// IS_INTEGRAL(unsigned int);
// IS_INTEGRAL(unsigned long int);
// IS_INTEGRAL(unsigned long long int);

// #include <iostream>
// #include <type_traits>

// template <bool B>
// struct enable_if {
// };

// template <>
// struct enable_if<true> {
	// typedef void type;
// };

// template <typename T>
// struct is_integral {
	// static bool const value = false;
// };

// template <>
// struct is_integral<int> {
	// static bool const value = true;
// };

// template <typename T>
// void is_int(T) {
	// std::cout << [> val <<  <]" is not int" << std::endl;
// }

// template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
// void is_int(T) {
	// std::cout[>  << val <] << " is int" << std::endl;
// }

// template <class T>
// void foo(T) { 
    // std::cout << "T is signed" << std::endl; 
// }

// template <class T, class = typename enable_if<std::is_unsigned<T>::value>::type>
// void foo(T) {
    // std::cout << "T is unsigned" << std::endl; 
// }


// int main() {
	// int i = 42;
	// float f = 42.42f;
	// std::cout << std::is_integral<int>::value << std::endl;
	// std::cout << std::is_integral<float>::value << std::endl;
	// unsigned int u = 42;
	// is_int(i);
	// is_int(f);
	// foo(i);
	// foo(u);
	// return (0);
// }
#include <iostream>

/*
 * Enable-if
 * It is used to allow function overloading based on 
 * arbitrary properties of type. Relies on SFINE
 * (if invalid argument or return type is formed during 
 * instantiation of function template, the instantiation 
 * is removed instead of compilation error).
 * Often used in C++ template metaprogramming, 
 * Boost libraries, and C++ STL.
 */


template<bool>
struct EnableIf {};

template<>
struct EnableIf<true> {
    using type = void;
};

template <class T>
void foo(T) { 
    std::cout << "T is signed" << std::endl; 
}

template <class T, class = typename EnableIf<std::is_unsigned<T>::value>::type>
void foo(T) {
    std::cout << "T is unsigned" << std::endl; 
}


int main()
{
    unsigned int x = 5;
    foo(x);

    return 0;
}
