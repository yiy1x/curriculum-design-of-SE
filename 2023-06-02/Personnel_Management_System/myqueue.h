#ifndef MYQUEUE_H
#define MYQUEUE_H

class MyQueue
{
public:
    MyQueue();
    ~MyQueue();

    bool inQueue(const char *);
    char * deQueue();
    bool isQueueEmpty();
    bool isQueueFull();
    bool clear();


private:
    int sizeOfQueue;
    int head, tail;
    char **queue;
};

#define SIZE_OF_QUEUE 10
#define SIZE_OF_NEW_QUEUE 5

#endif // MYQUEUE_H
