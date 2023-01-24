#include "LinkedList.h"

#include <iostream>
#include <memory>
#include <string>
#include <cassert>

void testLinkedList(){
    LinkedList::LinkedList list{};
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

namespace LinkedList{
std::ostream& operator<<(std::ostream& os, const Node& node){
    os<<node.getValue();
    return os;
}
Node* LinkedList::insert(Node* pos, const std::string& value){
    assert(pos!=nullptr);
    if(pos==begin()){
        head=std::make_unique<Node>(value,move(head),nullptr);
        pos->prev=begin();
    }
    else{
        auto prevNode=pos->prev;
        prevNode->next=std::make_unique<Node>(value,move(prevNode->next),prevNode);
        pos->prev=prevNode->getNext();
    }
    return pos->prev;
}
Node* LinkedList::remove(Node* pos){
    assert(pos!=nullptr);
    assert(pos!=end());
    if(pos==begin()){
        head=std::move(pos->next);
        head->prev=nullptr;
        return begin();
    }
    else{
        auto ret= pos->getNext();
        pos->next->prev=pos->prev;
        pos->prev->next=std::move(pos->next);
        return ret;
    }

}
Node* LinkedList::find(const std::string& value){
    for(auto it=begin();it!=end();it=it->getNext()){
        if(it->getValue()==value){
            return it;
        }
    }
    return(end());
}
void LinkedList::remove(const std::string& value){
    auto target=find(value);
    if(target!=end()){
        remove(target);
    }
}
std::ostream& operator<<(std::ostream& os, const LinkedList& list){
    os<<"[";
    for(auto it=list.begin();it!=list.end();it=it->getNext()){
        os<<*it;
        if(it->getNext()!=list.end()){os<<" ";}
    }
    os<<"]";
    return os;  
}
}