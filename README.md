# Design Patterns in Modern C++

## Guidelines

- **memory management**: Use smart pointers to prevent memory leaks.
- **copy control**: Follow [The rule of three/five/zero](https://github.com/ltimaginea/Cpp-Primer/blob/main/CppPrimer/Content/Ch13_CopyControl/Ch13_01_The_rule_of_three_five_zero.md) .
- **virtual destructor**: Make the polymorphic base class destructor public and virtual.
- **prevent slicing**: Make the polymorphic base class copy/move protected to prevent the slicing, and so that only derived classes can invoke them in their own copy/move.
