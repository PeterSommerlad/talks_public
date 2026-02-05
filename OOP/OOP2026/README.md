Here is the [handout/slides](https://github.com/PeterSommerlad/talks_public/blob/main/OOP/OOP2026/int%20!%3D%20safe%20%26%26%20int%20!%3D%20%E2%84%A4.pdf) for my OOP 2026 talk on safer integers:



# int != safe && int != ℤ
 
Target audience: Developers

Prerequisites: Basic knowledge in C or C++, For advanced examples some more C++ is helpful but not essential

Additional Information for the Program Team: Integers seem almost natural to a person with some math background. Unfortunately, the range where usual arithmetic operations in a programming language is safe is surprisingly small. This talk will show how small that range can actually be, e.g., for integer multiplication.
Presented before: focussed on C++ only, this talk was submitted to MeetingC++ and ESE Kongress
 
 
### Short Abstract

Programming language integers suffer from potential inaccuracy in arithmetic operations as well as undefined behavior in languages like C++ and C.

This talk shows the risks involved in inappropriate integer operations and the problems with implicit type conversion of the original operands types that can confuse programmers. We will also look at a few other languages besides C++ on how they deal with integer arithmetic.

 
### Extended Abstract

Programming language integers suffer from potential inaccuracy in arithmetic operations as well as undefined behavior in languages like C++ and C.

This talk shows the risks involved in inappropriate integer operations in C++ and the problems with integral promotion and the "usual arithmetic conversions" that in addition to the original operands types can further confuse programmers. We will also look at a few other languages on how they deal with integer arithmetic.

We will take a look at language safety guidelines with respect to integer arithmetic and operations and see where are their limitations in static analysis.

However, the power of C++ and new standard library features will allow us to implement safer alternatives. It might be a bit of art required to actually achieve syntactical nicety, efficient implementation and well-defined behavior when dealing with whole numbers and integers.

Note: this talk will not include approaches for unlimited precision arithmetic that might be required for some domains.

* assess the risk of integer arithmetic quiz

* why are there hidden problems, shouldn't integers just wrap?

* what safety guidelines say

* options for dealing with inaccuracy (overflow)

* C++26: saturation arithmetic

* convenient, safe, efficient: can we have all 3?

 
### Biography of Presenting Authors

Peter Sommerlad is consultant and trainer for Safe Modern C++ and Agile Software Engineering. Peter was professor at and director of IFS Institute for Software at FHO/HSR Rapperswil, Switzerland until February 2020. Peter is co-author of POSA Vol.1 and Security Patterns and contributed to other books as well as several ISO standards (C, C++, vulnerabilities) and C++ guidelines. Peter is a member of MISRA-C++, Hillside, ACM, IEEE Computer Society, ACCU, ISO WG23 and the ISO WG21 C++ committee.