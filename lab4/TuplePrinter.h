#ifndef TUPLE_PRINTER_H
#define TUPLE_PRINTER_H

#include <tuple>
#include <iostream>

namespace TuplePrinter {
    template <typename Tuple, std::size_t Index>
    struct Printer {
        static void print(std::ostream& os, const Tuple& t) {
            Printer<Tuple, Index - 1>::print(os, t);
            os << ", " << std::get<Index - 1>(t);
        }
    };

    template <typename Tuple>
    struct Printer<Tuple, 1> {
        static void print(std::ostream& os, const Tuple& t) {
            os << std::get<0>(t);
        }
    };

    template <typename... Args>
    std::ostream& print_tuple(std::ostream& os, const std::tuple<Args...>& t) {
        os << "(";
        if constexpr (sizeof...(Args) > 0) {
            Printer<decltype(t), sizeof...(Args)>::print(os, t);
        }
        os << ")";
        return os;
    }
}

template <typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t) {
    return TuplePrinter::print_tuple(os, t);
}

#endif
