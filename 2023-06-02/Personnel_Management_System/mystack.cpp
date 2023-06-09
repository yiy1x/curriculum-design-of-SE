#include "mystack.h"
#include <cstdlib>

MyStack::MyStack():sizeOfStack(SIZE_OF_STACK)
{
    base = (char* *)malloc(SIZE_OF_STACK * sizeof(char *));
    if(base == NULL)
    {
        qDebug() << "申请内存失败！" << endl;
        int yes = QMessageBox::critical(NULL, "错误！" , "申请内存失败！退出程序", QMessageBox::Yes, QMessageBox::Yes);
        if(yes == QMessageBox::Yes)
        {
            exit(1);
        }
    }
    head = base;
    sizeOfStack = SIZE_OF_STACK;
}

MyStack::~MyStack()
{
    while(!isEmpty())
    {
        free(*head);
        head--;
    }
    free(base);
    base = NULL;
    head = NULL;
    sizeOfStack = 0;
}

int MyStack::push(const char* pushValue)
{
    if(head - base >= sizeOfStack)
    {
        base = (char* *)realloc(base, sizeof(char *) * (SIZE_OF_NEW_STACK + sizeOfStack));
        if(base == NULL)
        {
            qDebug() << "申请内存失败！" << endl;
            int yes = QMessageBox::critical(NULL, "错误！" , "申请内存失败！退出程序", QMessageBox::Yes, QMessageBox::Yes);
            if(yes == QMessageBox::Yes)
            {
                exit(1);
            }
        }
        head = base + sizeOfStack;
        sizeOfStack += SIZE_OF_NEW_STACK;
    }
    if(pushValue == NULL)
    {
        char *tempChar = NULL;
        *head++ = tempChar;
    }
    else
    {
        char *tempChar = (char *)malloc(sizeof(char) * strlen(pushValue) + 1);
        if(tempChar == NULL)
        {
            qDebug() << "申请内存失败！" << endl;
            int yes = QMessageBox::critical(NULL, "错误！" , "申请内存失败！退出程序", QMessageBox::Yes, QMessageBox::Yes);
            if(yes == QMessageBox::Yes)
            {
                exit(1);
            }
        }
        int i;
        for(i = 0; i < (int)strlen(pushValue); i++)
        {
            tempChar[i] = pushValue[i];
        }
        tempChar[i] = '\0';
        *head++ = tempChar;
    }

}

int MyStack::pop()
{
    if(head == base)
    {
        qDebug() << "没有元素了" << endl;
        return false;
    }
    else
    {
        --head;
        return true;
    }
}

char* MyStack::top()
{
    if(head > base)
    {
        char* temp = *(--head);
        head++;
        return temp;
    }
    else
    {
        qDebug() << "没有元素了" << endl;
        char * temp = NULL;
        return temp;
    }

}

int MyStack::isEmpty()
{
    if((head - base) >= 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int MyStack::lastOne()
{
    if(head - base == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int MyStack::clear()
{
    while(!isEmpty())
    {
        free(*head);
        head--;
    }
    return true;
}
