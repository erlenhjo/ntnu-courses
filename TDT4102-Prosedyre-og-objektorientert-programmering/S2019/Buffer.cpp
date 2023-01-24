#include "Buffer.h"


RingBuf::RingBuf(int capacity)
    :buf{new char[capacity]},capacity{capacity},start{0},size{0}
    {}

RingBuf::RingBuf(const RingBuf& other){
    capacity=other.capacity;
    size=other.size;
    start=other.start;
    buf = new char[capacity];
    for(int i{0};i<capacity;++i){
        buf[i]=other.buf[i];
    }
}

RingBuf::~RingBuf(){
    delete[] buf;
}

RingBuf::RingBuf(RingBuf&& other){
    capacity=other.capacity;
    size=other.size;
    start=other.start;
    buf=other.buf;
    other.buf=nullptr;
}

RingBuf& RingBuf::operator=(RingBuf rhs){
    capacity=rhs.capacity;
    size=rhs.size;
    start=rhs.start;
    buf=new char[capacity];
    for(int i{0};i<capacity;++i){
        buf[i]=rhs.buf[i];
    }
    return *this;
}

void RingBuf::write(char c){
    *(buf+(start+size)%capacity)=c;
    if(size!=capacity){
        size+=1;
    }
    else{
        if(start!=capacity-1){
            start+=1;
        } 
        else{
            start=0;
        }   
    }
}

char RingBuf::read(){
    if(size==0){
        throw "Error: Empty buffer";
    }
    char ret=*(buf+start);
    if(start!=capacity-1){
        start+=1;
    } else{
        start=0;
    }
    size-=1;
    return ret;
}
void RingBuf::write(string s){
    for(char c:s){
        write(c);
    }
}
string RingBuf::read(int count){
    string out{""};
    if(count==-1 || count>size){
        int orgSize=size;
        for(int i{0};i<orgSize;++i){
            out+=read();
        }
    }
    else{
        for(int i{0};i<count;++i){
            out+=read();
        }
    }
    return out;
}

string RingBuf::peek(){
    int st=start;
    int sz=size;
    string retVal=read(-1);
    start=st;
    size=sz;
    return retVal;
}

void testRingBuf(){
    RingBuf rb{5};
    
    assert(rb.peek()=="");
    assert(rb.start==0);
    assert(rb.size==0);

    rb.write("ABC");

    
    assert(rb.peek()=="ABC");
    assert(rb.start==0);
    assert(rb.size==3);

    rb.write("DEF");
    cout<<rb.start<<endl;
    assert(rb.peek()=="BCDEF");
    assert(rb.start==1);
    assert(rb.size==5);


    string s=rb.read(3);

    assert(rb.peek()=="EF");
    assert(rb.start==4);
    assert(rb.size==2);
    assert(s=="BCD");

    s=rb.read(-1);

    assert(rb.peek()=="");
    assert(rb.start==1);
    assert(rb.size==0);
    assert(s=="EF");
}