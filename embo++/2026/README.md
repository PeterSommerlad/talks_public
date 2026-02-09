## int != safe && int != ℤ

C++ integers suffer from potential inaccuracy in arithmetic operations as well as undefined behavior.

This talk shows the risks involved in inappropriate integer operations and the problems with integral promotion and the "usual arithmetic conversions" that in addition to the original operands types can further confuse programmers.

We will take a look at MISRA C++ guidelines with respect to integer arithmetic and operations and see where are their limitations in static analysis.

However, the power of C++ and new standard library features will allow us to implement safer alternatives. It might be a bit of art required to actually achieve syntactical nicety, efficient implementation and well-defined behavior when dealing with whole numbers and integers. 

Note: this talk will not include approaches for unlimited precision arithmetic that might be required for some domains.

* assess the risk of integer arithmetic quiz
* why are there hidden problems, shouldn't integers just wrap?
* what safety guidelines say
* options for dealing with inaccuracy (overflow)
* C++26: saturation arithmetic
* convenient, safe, efficient: can we have all 3?


## Class Design the MISRA C++ Way

short talk

We will rush through the concepts that I used to inspire the MISRA C++ guidlines 15.0.1 and 15.0.2 that deal with special member functions. I'll show the class design for manager types and polymorphic bases which are those that require defining special member functions. In all other cases the Rule-of-Zero should apply for your classes.