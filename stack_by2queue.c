#include <stdio.h>
#include "seqqueue.h"
typedef struct StackBy2Queue
{
    SeqQueue queue1;
    SeqQueue queue2;
}StackBy2Queue;

void StackInit(StackBy2Queue* stack)
{
    if(stack == NULL)
    {
        //非法操作
        return;
    }
    SeqQueueInit(&stack->queue1);
    SeqQueueInit(&stack->queue2);
}

void StackPush(StackBy2Queue* stack,SeqQueueType value)
{
    if(stack == NULL)
    {
        //非法操作
        return;
    }
    //input队列为非空队列
    SeqQueue* input=stack->queue1.size!=0?&stack->queue1:&stack->queue2;
    SeqQueuePush(input,value);
}

void StackPop(StackBy2Queue* stack)
{
    if(stack == NULL)
    {
        //非法操作
        return;
    }
    if(stack->queue1.size==0&&stack->queue2.size==0)
    {
        //空队列
        return;
    }
    //元素多对队列为from队列，即要移动的队列
    //元素少对队列为to队列，即要移动到的队列
    SeqQueue* from=NULL;
    SeqQueue* to=NULL;
    if(stack->queue1.size>0)
    {
        from=&stack->queue1;
        to=&stack->queue2;
    }
    else
    {
        from=&stack->queue2;
        to=&stack->queue1;
    }
    //把from中的元素移动到to队列中,直到from中只有一个元素
    while(1)
    {
        if(from->size==1)
        {
            break;
        }
        SeqQueueType value;
        SeqQueueFront(from,&value);
        SeqQueuePop(from);
        SeqQueuePush(to,value);
    }
    SeqQueuePop(from);

}

int StackTop(StackBy2Queue* stack,SeqQueueType* output_value)
{
    if(stack == NULL || output_value == NULL)
    {
        //非法操作
        return 0;
    }
    
    if(stack->queue1.size==0&&stack->queue2.size==0)
    {
        //空队列
        return 0;
    }
    SeqQueue* from=NULL;
    SeqQueue* to=NULL;
    if(stack->queue1.size>0)
    {
        from=&stack->queue1;
        to=&stack->queue2;
    }
    else
    {
        from=&stack->queue2;
        to=&stack->queue1;
    }
    while(1)
    {
        if(from->size==1)
        {
            break;
        }
        //SeqQueueType value;
        SeqQueueFront(from,output_value);
        SeqQueuePop(from);
        SeqQueuePush(to,*output_value);
    }
    return 1;
}


#include <stdio.h>
#define TEST_HEADER printf("\n========%s=========\n",__FUNCTION__)
void Test()
{
    TEST_HEADER;
    StackBy2Queue stack;
    StackInit(&stack);
    StackPush(&stack,'a');
    StackPush(&stack,'b');
    StackPush(&stack,'c');
    StackPush(&stack,'d');
    SeqQueueType value;
    int ret;
    ret = StackTop(&stack,&value);
    printf("ret expected 1,actuall %d\n",ret);
    printf("value expected d,actuall %c\n",value);

    StackPop(&stack);
    ret = StackTop(&stack,&value);
    printf("ret expected 1,actuall %d\n",ret);
    printf("value expected d,actuall %c\n",value);
    
    StackPop(&stack);
    ret = StackTop(&stack,&value);
    printf("ret expected 1,actuall %d\n",ret);
    printf("value expected d,actuall %c\n",value);

    StackPop(&stack);
    ret = StackTop(&stack,&value);
    printf("ret expected 1,actuall %d\n",ret);
    printf("value expected d,actuall %c\n",value);

    StackPop(&stack);
    ret = StackTop(&stack,&value);
    printf("ret expected 0,actuall %d\n",ret);
    //printf("value expected d,actuall %c\n",value);

}

int main()
{
    Test();
    return 0;
}
