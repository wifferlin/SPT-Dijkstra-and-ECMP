//採用 MinHeap 的方式進行排序，MinHeap 基本規則為 child(2i,2i+1) 的值不能大於 Parent(i)建立二元數
//詳細資料參考 : http://alrightchiu.github.io/SecondRound/priority-queuebinary-heap.html#MinHeapInsert

#include <stdio.h>
#include <stdlib.h>

#define Empty 999 

//定義節點內容
typedef struct PQNode 
{
    int Node_Num;
    int Distance;
} PQNode;

//定義 Heap 內容
typedef struct Priority_Queue
{    
    int size;
    PQNode* MinHeap;
} PQ;

//初始化 MinHeap
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
        //繼續向上檢查直到 ROOT
        index = index/2;
    }
}

int Dequeue(PQ *Q)
{
    if(Q->size != 0)
    {
        //移出最小節點(也就是根節點)
        int RemoveNode_Num = RemoveMin(Q->MinHeap,Q->size);
        //Queue size 增加
        Q->size = Q->size -1;
        //回傳節點號碼
        return RemoveNode_Num;
    }
    else
    {
        return Empty;
    }
    
}

int RemoveMin(PQNode* MinHeap,int size)
{
    //Root 節點即為最小，故取 Root
    PQNode RemoveNode = MinHeap[1];
    //將最尾端節點移至 Root 並開始調整
    MinHeap[1] = MinHeap[size];
    //因移出Root 節點所以 size 減 1
    size = size - 1;
    //調整 MinHeap 的順序
    MinHeapify(MinHeap,size,1);
    //回傳節點號碼
    return RemoveNode.Node_Num;
}

void MinHeapify(PQNode* MinHeap,int size,int index)
{
    PQNode Tmp;
    while(1)
    {
        //當沒有任何 child 時，調整結束
        if(2*index > size)
        {
            break;
        }
        //當只有一個 child 時，只跟他進行比較，不符合規則交換，符合規則跳出
        else if(2*index == size)
        {
            if(MinHeap[2*index].Distance < MinHeap[index].Distance)
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
        //跟所有 child 比較，跟比較小的交換
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