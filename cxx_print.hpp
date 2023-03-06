#pragma once

#include <string>
#include <iostream>
#include <ostream>
#include <functional>

namespace vptr {
    struct Separator {
        std::string_view sep;
    };

    struct EndLine {
        std::string_view endl;
    };

    struct Output {
        std::reference_wrapper<std::ostream> out;
    };

    template<class T, class U = std::remove_reference_t<T>>
    inline constexpr bool _is_separator_type_v = std::is_same_v<U, Separator>;

    template<class T, class U = std::remove_reference_t<T>>
    inline constexpr bool _is_endline_type_v = std::is_same_v<U, EndLine>;

    template<class T, class U = std::remove_reference_t<T>>
    inline constexpr bool _is_output_type_v = std::is_same_v<U, Output>;

    template<class T>
    inline constexpr bool _is_parameter_type_v = _is_separator_type_v<T> 
        or _is_endline_type_v<T> 
        or _is_output_type_v<T>;

    constexpr auto _setup_settings (Output& out, Separator &sep, EndLine &endl, auto &&val) {
        if constexpr (_is_separator_type_v<decltype(val)>) {
            sep = val;
        }
        else if constexpr (_is_endline_type_v<decltype(val)>){
            endl = val;
        }
        else if constexpr (_is_output_type_v<decltype(val)>) {
            out = val;
        }
    }

    constexpr auto _print_value (Output& out, Separator &sep, auto &&val) {
        if constexpr (not _is_parameter_type_v<decltype(val)>) {
            out.out.get() << sep.sep << val;
        }
    }

    constexpr auto print (auto &&first, auto &&...args) {
        Separator sep{ " " };
        EndLine endl{ "\n" };
        Output out { std::cout };

        (_setup_settings (out, sep, endl, args), ...);

        out.out.get() << first;
        (_print_value (out, sep, args), ...);

        out.out.get() << endl.endl;
    }
}
