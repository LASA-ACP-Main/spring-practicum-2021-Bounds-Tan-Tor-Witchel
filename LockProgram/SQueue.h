#include <iostream>
#include <string>

#ifndef SQUEUE_H
#define SQUEUE_H

struct Qnode
{
	std::string data;
    Qnode* link;
};


class SQueue
{

	private:
        Qnode *front;
        int queueSize = 0;

	public:

    SQueue()
    {
        front = NULL;

    }

	void push(std::string item);
	std::string top();
	std::string pop();
	void display();
    bool isEmpty();
    void clear();
    int size();


};

#endif //SQUEUE_H
