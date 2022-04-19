#include <iostream>
#include <string>

#ifndef SQUEUE_H
#define SQUEUE_H

struct node
{
	std::string data;
    node* link;
};


class SQueue
{

	private:
		node *front;
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
