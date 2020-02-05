# C++ Class Natures: Where To Find Them And How To Tame Them

C++ classes serve different purposes and from their member types, inheritance structure and special member functions one can distinguish several class natures, such as Values, OO-Bases, Unique Managers. Each class nature, requires specific ability with respect to copying, move operation or side effects on destruction. This talks provides canonical forms for such class types and allows more conscious class design in C++ and safer implementations. The Rule of DesDeMovA is introduced along the Rule of Zero, Three, and Five.

**Target Audience:** Developers, Designers

**Prerequisites:** C++ basic knowledge

**Level:** Practicing

## Extended Abstract

While working on guidelines for safety critical systems the author discovered that looking at the required special member functions and kind of member variables one can clearly distinguish several C++ class type natures. For example, there exist empty types, such as traits, or value types, such as std::string. But also types that manage resources, such as scope guards or unique managers, can be distinguished. A last area are object-oriented polymorphic base classes forming a separate nature. This categorization has direct influence on the applicability of the *"Rule of Zero"*, *"Rule of Five"*, or the author's *"Rule of DesDeMovA"*. The nature of member variables influence the nature of the class embedding them.

This talk maps the landscape of class/type natures and how they influence directly or indirectly the way you specify or the compiler provides copy or move operations and a destructor. With that information you will get concrete guidelines to provide canonical class types more consciously with the least amount of code scaffolding. It also helps you to avoid creating easy to misuse types and gives guidance to encapsulate and hide "dirty tricks" that you might still need or want.

