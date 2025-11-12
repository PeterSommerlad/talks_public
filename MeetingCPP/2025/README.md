[Slides for my talk at MeetingC++ 2025](https://github.com/PeterSommerlad/talks_public/blob/main/MeetingCPP/2025/int%20!%3D%20safe%20%26%26%20int%20!%3D%20%E2%84%A4.pdf)

C++ integers suffer from potential inaccuracy in arithmetic operations as well as undefined behavior.

This talk shows the risks involved in inappropriate integer operations and the problems with integral promotion and the "usual arithmetic conversions" that in addition to the original operands types can further confuse programmers.

We will take a look at MISRA C++ guidelines with respect to integer arithmetic and operations and see where are their limitations in static analysis.

However, the power of C++ and new standard library features will allow us to implement safer alternatives. It might be a bit of art required to actually achieve syntactical nicety, efficient implementation and well-defined behavior when dealing with whole numbers and integers. 

Note: this talk will not include approaches for unlimited precision arithmetic that might be required for some domains.

