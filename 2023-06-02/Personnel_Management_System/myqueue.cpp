#include "myqueue.h"
#include <cstdlib>
#include "string"
#include <QDebug>
#include <QMessageBox>

MyQueue::MyQueue() : sizeOfQueue(SIZE_OF_QUEUE)
{

    queue = (char * *)malloc(SIZE_OF_QUEUE * sizeof(char *));
    if(queue == NULL)
    {
        qDebug() << "申请内存失败" << endl;
        int yes = QMessageBox::warning(NULL, "错误！", "申请内存失败！退出程序", QMessageBox::Yes, QMessageBox::Yes);
        if(yes == QMessageBox::Yes)
        {
            exit(1);
        }
    }
    head = tail = 0;
    sizeOfQueue = SIZE_OF_QUEUE;
}

MyQueue::~MyQueue()
{
    while(!isQueueEmpty())
    {
        free(queue[tail]);
        tail--;
        if(tail == 0)
        {
            tail = sizeOfQueue;
        }
    }
    free(queue);
    head = tail = 0;
    sizeOfQueue = 0;
}

bool MyQueue::inQueue(const char *tempString)
{
    if(isQueueFull())
    {
        //char ** tempQueue = (char **)realloc(queue, sizeof(char *) *(sizeOfQueue + SIZE_OF_NEW_STACK));
        char ** tempQueue = (char **)malloc(sizeof(char *) * (sizeOfQueue + SIZE_OF_NEW_QUEUE));
        if(!tempQueue)
        {
            qDebug() << "申请内存失败" << endl;
            int yes = QMessageBox::warning(NULL, "错误！", "申请内存失败！退出程序", QMessageBox::Yes, QMessageBox::Yes);
            if(yes == QMessageBox::Yes)
            {
                exit(1);
            }
        }
        int tempCount = 0;
        while(!isQueueEmpty())
        {
            tempQueue[tempCount] = deQueue();
            tempCount++;
        }
        queue = tempQueue;

        head = 0;
        tail = (head + sizeOfQueue) - 2;

        sizeOfQueue += SIZE_OF_NEW_QUEUE;
    }
    if(tempString == NULL)
    {
        char *tempChar = NULL;
        queue[tail] = tempChar;
        tail ++;
        if(tail > sizeOfQueue)
        {
            tail = 0;
        }
        return true;
    }
    else
    {
        char *tempChar = (char *)malloc(sizeof(char) * strlen(tempString) + 1);
        int i;
        for(i = 0; i< (int)strlen(tempString); i++)
        {
            tempChar[i] = tempString[i];
        }
        tempChar[i] = '\0';
        queue[tail] = tempChar;
        tail++;
        if(tail > sizeOfQueue)
        {
            tail = 0;
        }
        return true;
    }
}

char *MyQueue::deQueue()
{
    char *tempString;
    if(head == tail)
    {
        qDebug() << "没有元素了" << endl;
        return NULL;
    }
    else
    {
        tempString = queue[head];
        head++;
        if(head > sizeOfQueue)
        {
            head = 0;
        }
    }

    return tempString;
}

bool MyQueue::isQueueEmpty()
{
    if(head == tail)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MyQueue::isQueueFull()
{
    if((tail + 2) % sizeOfQueue == head)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MyQueue::clear()
{
    while(!isQueueEmpty())
    {
        deQueue();
    }
    return true;
}
