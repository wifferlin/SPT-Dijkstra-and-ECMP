//採用 MinHeap 的方式進行排序，MinHeap 基本規則為 child(2i,2i+1) 的值不能大於 Parent(i)建立二元數
//詳細資料參考 : http://alrightchiu.github.io/SecondRound/priority-queuebinary-heap.html#MinHeapInsert

#include <stdio.h>
#include <stdlib.h>

typedef struct PQNode 
{
    int Node_Num;
    int Distance;
} PQNode;

typedef struct Priority_Queue
{    
    int size;
    PQNode* MinHeap;
} PQ;

void InitialPQ(PQ* Q)
{
    Q->size = 0;
    Q->MinHeap = (PQNode*)malloc(sizeof(PQNode)*36);
}

void Enqueue(PQNode NewNode,PQ *Q)
{
    //新增節點到 MinHeap 裡並調整
    Insert(NewNode,Q->MinHeap,Q->size);
    //Queue size 增加
    Q->size = Q->size + 1;
}

void Insert(PQNode NewNode,PQNode* MinHeap,int size)
{
    int index;
    PQNode Tmp;
    index = size +1;
    //先把新節點放到樹的最下方
    MinHeap[index] = NewNode;
    //跟 parent 做比較，若比母節點大則上移
    while(MinHeap[index].Distance < MinHeap[index/2].Distance && index > 1)
    {
        //母節點與子節點換位
        Tmp = MinHeap[index/2];
        MinHeap[index/2] = MinHeap[index];
        MinHeap[index] = Tmp;
        //繼續向上檢查
        index = index/2;
    }
}

int Dequeue(PQ *Q)
{
    int RemoveNode_Num = RemoveMin(Q->MinHeap,Q->size);
    Q->size = Q->size -1;
    printf("%d\n",RemoveNode_Num);
    return RemoveNode_Num;
}

int RemoveMin(PQNode* MinHeap,int size)
{
    //Root 節點即為最小，故取 Root
    PQNode RemoveNode = MinHeap[1];
    //將最尾端
    MinHeap[1] = MinHeap[size];
    size = size - 1;
    MinHeapify(MinHeap,size,1);
    return RemoveNode.Node_Num;
}

void MinHeapify(PQNode* MinHeap,int size,int index)
{
    PQNode Tmp;
    while(1)
    {
        if(2*index > size)
        {
            break;
        }
        else if(2*index == size)
        {
            if(MinHeap[2*index].Distance > MinHeap[index].Distance)
            {
                Tmp = MinHeap[index];
                MinHeap[index] = MinHeap[2*index];
                MinHeap[2*index] = Tmp;
                index = 2*index;
            }
            else
            {
                break;
            }
        }
        else
        {
            //左邊小跟左邊換，右邊小跟右邊換
            if(MinHeap[2*index].Distance <= MinHeap[2*index+1].Distance)
            {
                Tmp = MinHeap[index];
                MinHeap[index] = MinHeap[2*index];
                MinHeap[2*index] = Tmp;
                index = 2*index;
            }
            if(MinHeap[2*index].Distance > MinHeap[2*index+1].Distance)
            {
                Tmp = MinHeap[index];
                MinHeap[index] = MinHeap[2*index+1];
                MinHeap[2*index+1] = Tmp;
                index = 2*index+1;
            }
        }
    }
    
}

int main()
{
    PQ Q;
    PQNode NewNode;
    int RemoveNode_Num;
    InitialPQ(&Q);
    NewNode.Node_Num = 0;
    NewNode.Distance = 1;
    Enqueue(NewNode,&Q);
    NewNode.Node_Num = 1;
    NewNode.Distance = 9;
    Enqueue(NewNode,&Q);
    NewNode.Node_Num = 2;
    NewNode.Distance = 1;
    Enqueue(NewNode,&Q);
    NewNode.Node_Num = 3;
    NewNode.Distance = 1;
    Enqueue(NewNode,&Q);
    NewNode.Node_Num = 4;
    NewNode.Distance = 9;
    Enqueue(NewNode,&Q);
    NewNode.Node_Num = 5;
    NewNode.Distance = 1;
    Enqueue(NewNode,&Q);
    RemoveNode_Num = Dequeue(&Q);
    RemoveNode_Num = Dequeue(&Q);
    RemoveNode_Num = Dequeue(&Q);
    RemoveNode_Num = Dequeue(&Q);
    RemoveNode_Num = Dequeue(&Q);
    RemoveNode_Num = Dequeue(&Q);
}