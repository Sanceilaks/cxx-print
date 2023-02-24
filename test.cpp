#include <iostream>
#include <sstream>

#include "cxx_print.hpp"

int main(int, char**) {
    std::ostringstream out;

    vptr::print("First", "Second", vptr::Separator{ "_" }, vptr::EndLine{ "\n____" }, vptr::Output{ out });

    return not (out.str() == "First_Second\n____");
}
