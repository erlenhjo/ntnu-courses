#pragma once

#include <cassert>
#include <memory>
#include <ostream>
#include <string>

// test code 
void testTemplateLinkedList();


namespace TemplateLinkedList {
template<typename T>
class TemplateLinkedList;

template<typename T>
class Node {
private:
    const T value;    // The data held by the TemplateLinkedList
    std::unique_ptr<Node<T>> next; // unique_ptr to the next node
    Node<T>* prev;                 // raw (non-owning) ptr to the previous node
public:
    Node() : value(), next(nullptr), prev(nullptr) {}
    // construct a node with string value, a unique_ptr to the next node, and a pointer to the previous node
    Node(const T & value, std::unique_ptr<Node<T>> next, Node<T>* prev)
        : value(value)
        , next(std::move(next))
        , prev(prev)
    {}
    // We can use the default constructor, since unique_ptr takes care of deleting memory
    ~Node() = default;
    // return the value of the node
    T getValue() const { return value; }

    // return a raw (non-owning) pointer to the next node
    Node<T>* getNext() const { return next.get(); }
    // return a raw (non-owning) pointer to the previous node
    Node<T>* getPrev() const { return prev; }

    // write the value of the node to the ostream
    friend std::ostream & operator<<(std::ostream & os, const Node<T> & node){
    os<<node.getValue();
    return os;
}

    friend class TemplateLinkedList<T>;
};

template<typename T>
class TemplateLinkedList{
private:
    // ptr to the first node
    std::unique_ptr<Node<T>> head;
    // a raw pointer to the last node, the last node is always a dummy node
    // this is declared as a const ptr to a Node, so that tail never can
    // point anywhere else
    Node<T>* const tail;
public:
    //create the dummy node, and make tail point to it
    TemplateLinkedList()
        : head(std::make_unique<Node<T>>())
        , tail(head.get())
    {}

    ~TemplateLinkedList() = default;

    //if next is a nullptr (i.e. head is the dummy node), the list is emtpy
    bool isEmpty() const { return head->next == nullptr; }


    //return a pointer to first element
    Node<T>* begin() const { return head.get(); }
    //return a pointer to beyond-end element
    Node<T>* end() const { return tail; }

    // The insert function takes a pointer to node (pos) and a string (value). It creates a new
    // node which contains value. The new node is inserted into the TemplateLinkedList BEFORE the
    // node pointed to by pos. Returns a pointer to the new Node
    Node<T>* insert(Node<T> *pos, const T& value){
    assert(pos!=nullptr);
    if(pos==begin()){
        head=std::make_unique<Node<T>>(value,move(head),nullptr);
        pos->prev=begin();
    }
    else{
        auto prevNode=pos->prev;
        prevNode->next=std::make_unique<Node<T>>(value,move(prevNode->next),prevNode);
        pos->prev=prevNode->getNext();
    }
    return pos->prev;
}

    // The find function traverses the linked list and returns a pointer to the first node
    // that contains the value given.
    // If the value isn't in the list, find returns a pointer to the dummy node at the end
    // of the list.
    Node<T>* find(const T& value){
    for(auto it=begin();it!=end();it=it->getNext()){
        if(it->getValue()==value){
            return it;
        }
    }
    return(end());
}

    // The remove function takes a pointer to a node, and removes the node from the list. The
    // function returns a pointer to the element after the removed node.
    Node<T>* remove(Node<T>* pos){
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

    // The remove function takes a string and removes the first node which contains the value.
    void remove(const T& value){
    auto target=find(value);
    if(target!=end()){
        remove(target);
    }
}

    // write a string representation of the list to the ostream
    friend std::ostream & operator<<(std::ostream & os, const TemplateLinkedList<T>& list){
    os<<"[";
    for(auto it=list.begin();it!=list.end();it=it->getNext()){
        os<<*it;
        if(it->getNext()!=list.end()){os<<" ";}
    }
    os<<"]";
    return os;  
}
};
}// namespace TemplateLinkedList
