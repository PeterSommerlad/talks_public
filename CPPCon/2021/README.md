# What Classes we Design and How

CPPCon 2021-10-28



C++ class design has been error prone since the beginning until Scott Meyers told us about the Rule-of-Three. But even that is not enforced by the language. In addition, C++11 changed the set of compiler-provided special member functions and the intrinsic rules have become more complicated. However, instead of starting from the rules for special member functions, we will look at what role a class type plays and how that maps on what special member functions to define and how, if any. Examples for class roles are Value, Relationship, Manager (scoped, unique, general), Mix-in.

We will also look at the roles of member variable types that influence or imply the role of the class type.
The role of a class will also take out many mysteries of move operations and will lead to clear guidance when and how to implement move: for suppressing copying, for managing unique ownership (Unique Manager) or for optimizing object copies (General Manager).

We will rehearse the Rule of Zero, and learn more about the Rule of Five/Six, the Rule of DesDeMovA, and the Rule of Unique Three.

This all will enable you to much more consciously and safely design your class types and combine types of member variables. You will have then the ability to select from a few reasonable combinations from the plethora of possibilities of special member function combinations: {public:,protected:,private:} x {destructor, default constructor, copy constructor, copy assignment, move constructor, assignment} x {noexcept(true),noexcept(false)} x { =default, =delete, {/*body*/}, not declared } (math as homework)
