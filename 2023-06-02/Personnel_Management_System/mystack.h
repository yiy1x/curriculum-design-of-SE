#ifndef MYSTACK_H
#define MYSTACK_H

#include<QString>
#include <malloc.h>
#include <QDebug>
#include <QMessageBox>

/*
 * 定义的宏常量
 * 第一个是栈的初始大小
 * 第二个是栈在延伸的时候的延伸的大小
 * 第三个和第四个是定义的bool常量
 */
#define SIZE_OF_STACK 10
#define SIZE_OF_NEW_STACK 5
#define true 1
#define false 0

class MyStack
{
public:
    MyStack();
    ~MyStack();

    int push (const char *);
    int pop();
    char *top();
    int isEmpty();
    int lastOne();
    int clear();

private:

    int sizeOfStack;
    char **base;
    char **head;


};

#endif // MYSTACK_H
