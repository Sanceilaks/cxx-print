# Python-like C++ print function
An a simple C++ analog of python `print()` function.
Usage:
```c++
    vptr::print("First", "Second");
    // stdout => "First Second\n"
```

Or u can use additional parameters:
```c++
    std::ostringstream out;
    vptr::print("First", "Second", vptr::Separator{ "_" }, vptr::EndLine{ "\n____" }, vptr::Output{ out });
    // out => First_Second\n____
```
