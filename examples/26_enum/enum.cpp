#include <iostream>

enum Day{sunday=0, monday=1, tuesday=2, wednesday=3, thursday=4, friday=5, saturday=6};

int main()
{
    // enums = a user-defined data type that consists of paired named-integer constants
    // Great if you have a set of potential options

    Day today = sunday;
    switch(today)
    {
        case sunday:
            std::cout << "It is Sunday!" << std::endl;
            break;
        case monday:
            std::cout << "It is Monday!" << std::endl;
            break;
        case tuesday:
            std::cout << "It is Tuesday!" << std::endl;
            break;
        case wednesday:
            std::cout << "It is Wednesday!" << std::endl;
            break;
        case thursday:
            std::cout << "It is Thursday!" << std::endl;
            break;
        case friday:
            std::cout << "It is Friday!" << std::endl;
            break;
        case saturday:
            std::cout << "It is Saturday!" << std::endl;
            break;
    }

    return 0;
}
