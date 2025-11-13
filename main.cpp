#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    /*
    LinkedList<int> list;
    list.addHead(123);
    list.addHead(111);
    list.addTail(333);

    list.printForward();
    std::cout << list.getCount() << std::endl;
    list.removeHead();
    list.printForward();
    std::cout << list.getCount() << std::endl;
    list.removeTail();
    list.printForward();
    std::cout << list.getCount() << std::endl;  
    list.removeHead();
    list.printForward();
    std::cout << list.getCount() << std::endl;  

    
    list.addHead(123);
    list.addHead(111);
    list.removeHead();
    list.addHead(111);
    list.addHead(111);
    list.removeTail();
    list.addHead(111);
    list.addHead(111);
    list.removeTail();
    list.removeHead();
    list.addTail(333);

    list.printReverse();
    std::cout << list.getCount() << std::endl;  
    list.clear();
    list.printReverse();
    std::cout << list.getCount() << std::endl;
    */

    ABQ<int> test;

    return 0;
}


#endif
