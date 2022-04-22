
#include "SQueue.h"



void SQueue::push(std::string item)
{
    Qnode* newNode = new Qnode;
    newNode->data = item;
    newNode->link = nullptr;
    if(front == nullptr){
        front = newNode;
    }
    else{
        Qnode* counting = front;
        while(counting->link != nullptr) {
                counting = counting->link;
        }
        Qnode* temp = counting->link;
        counting->link = newNode;
        newNode->link = temp;
    }
    queueSize++;
}


std::string SQueue::top()
{
    if(front == nullptr){
        return nullptr;
    }
    else{
        return front->data;
    }
}


std::string SQueue::pop()
{
    if(front == nullptr){
        return nullptr;
    }
    else{
        std::string toReturn = front->data;
        front = front->link;
        queueSize--;
        return toReturn;
    }
}
void SQueue::display()
{
    Qnode* counter = front;
    while(counter != nullptr){
        std::cout<<(counter->data)<<std::endl;
        counter = counter->link;
    }

}


bool SQueue::isEmpty(){
    if(front == nullptr || front->data == ""){return true;}
    return false;
}

void SQueue::clear(){
    while(front != nullptr && front->data != ""){
        pop();
    }
    front = nullptr;
    queueSize = 0;
}

int SQueue::size(){
    return queueSize;
}