
Talk: MISRA C++ 202x: Will your C++ be Ready?
======

Prof. Peter Sommerlad, FHO HSR Rapperswil  
----

New MISRA C++ programming guidelines are on their way and several experts from the ISO C++ standardization committee are participating in its development.
This guarantees that the upcoming guidelines will address current C++ best practices. 
Those practices allow to express more software with less code that is often also more efficient and safer than current industry practices in the embedded software world.
This talk is a call to action to educate your developers to be able to write MISRA C++ conformant code in the near future. 
It will give examples of how future MISRA C++ 202x compliant code will look like and provide an overview, what obsoleted practices your developers might have to unlearn and what new modern C++ quality practices need to be mastered. 

> "If you think education is expensive, try ignorance" (attributed to Derek Bok, Ann Landers and others). 


Class 6.4 Safe Modern C++
=====

Prof. Peter Sommerlad, FHO HSR Rapperswil  
------

With the introduction of C++11/14/17 new best practices have evolved that are reflected in safety programming guidelines. Many practices that have been established for years using C or old-style C++ are now considered obsolete or risky, where better designs and usage of language constructs have been established. For example, plain pointers that dominate old code will be applied only very sparsely and encapsulated in modern safe C++. The use of standard library algorithms allows reducing the risk of loops by better articulating behavior. Encapsulation of primitive types for representing domain values can be done without overhead. This class will introduce new ways to solve problems and demonstrates how to migrate from older practices. In some cases it shows where automated tools can help to avoid them or repair existing code interactively. 