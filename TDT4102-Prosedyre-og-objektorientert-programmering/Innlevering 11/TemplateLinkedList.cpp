#include "TemplateLinkedList.h"

#include <iostream>
#include <memory>
#include <string>
#include <cassert>

void testTemplateLinkedList(){
    TemplateLinkedList::TemplateLinkedList<std::string> list{};
    list.insert(list.begin(),"f");
    list.insert(list.begin(),"e");
    list.insert(list.begin(),"d");
    auto c = list.insert(list.begin(),"c");
    list.insert(list.begin(),"b");
    list.insert(list.begin(),"a");
    list.insert(c,"q");
    list.remove("a");
    list.remove("a");
    list.remove("q");
    std::cout<<list;
    std::cout<<"\n";
}
