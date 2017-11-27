#include<stdio.h>
#include<string.h>
#include "Priority_queue.c"

#define Infinity 9999
#define Empty 999

int main(int argc, char *argv[])
{
    int Num_of_Node = 0 , Num_of_EndNode = 0 , Num_of_Link = 0;
    int count1 = 0 , count2 = 0;
    int Node1 = 0 , Node2 = 0; 
    int ignore;
    int Source , Destination;
    int STP[Num_of_Node];
    //open the topology file
    FILE *file;
    file = fopen("cnstln36.txt","r");
    //Read topology information
    fscanf(file,"%d",&Num_of_Node);
    fscanf(file,"%d",&Num_of_EndNode);
    fscanf(file,"%d",&Num_of_Link);
    //printf("%d %d %d\n",Num_of_Node,Num_of_Link,Num_of_EndNode);


    //Initial the Link Matrix of Node(ALL Link are Infinity First, means no connect)
    int LinkMatrix[Num_of_Node][Num_of_Node];
    for(count1 = 0; count1 < Num_of_Node; count1++)
    {
        for(count2 = 0;count2 < Num_of_Node;count2++)
        {
            LinkMatrix[count1][count2]=Infinity;
        }
    }


    //Fill in the Link State and weight on cnstln36(in this case all Link weight are 1)
    while(fscanf(file,"%d %d %d",&Node1,&Node2,&ignore) != EOF)
    {
        LinkMatrix[Node1][Node2]=1;
        LinkMatrix[Node2][Node1]=1;
    } 
    fclose(file);

    //Key in the source and Destination
    printf("Please key in the Source Node:");
    scanf("%d",&Source);
    printf("\nPlease key in the Destination Node:");
    scanf("%d",&Destination);
    Dijkstra(Source,Destination,Num_of_Node,LinkMatrix);
}

void Dijkstra(int Source , int Destination , int Num_of_Node, int LinkMatrix[Num_of_Node][Num_of_Node])
{
    int Distance[Num_of_Node];  //Record the Shorted Path from source
    int Previous[Num_of_Node];  //Record the Shorted Path Previous Node
    int Visited[Num_of_Node];   //Aleardy Visisited Node(0 is unvisited, 1 is visited)
    int count;
    PQ Q;                       // Priority Queue
    PQNode NewNode;             //Priority Queue Node
    int RemoveNode;             //pop Node from Priority Queue
    int Tmp;


    //initial the distance and shorted path from source
    for(count = 0;count < Num_of_Node; count++)
    {
        //set the all distance from source as infinity
        Distance[count] = Infinity;

        //set Source to Source as 0
        if(Source == count)
        {
            Distance[count] = 0;
        }
        Previous[count] = Empty;
        Visited[count] = 0;
    }

    //Insert Source int Priority queue(use the file of Priority_queue.c)
    InitialPQ(&Q);
    NewNode.Node_Num = Source;
    NewNode.Distance = Distance[Source];
    Enqueue(NewNode,&Q);

    while(1)
    {
        //If Queue is Empty Break the loop
        RemoveNode = Dequeue(&Q);
        ////printf("Remove : %d\n",RemoveNode);
        if(RemoveNode == Empty)
        {
            break;
        }
        //Record this Node as Visited
        Visited[RemoveNode] = 1;

        for(count=0 ;count<Num_of_Node; count++)
        {
            //Find the Node Neighbor
            if(LinkMatrix[RemoveNode][count] != Infinity)
            {
                //Sum the Length From Source to RemoveNode Already Know Shortest Distance
                //And RemoveNode to Neighbor length
                Tmp = Distance[RemoveNode] + LinkMatrix[RemoveNode][count];
                ////printf("count : %d ,Distance[RemoveNode] : %d , LinkMatrix[RemoveNode][count] : %d \n",count,Distance[RemoveNode],LinkMatrix[RemoveNode][count]);
                ////printf("TMP : %d , Distance[count] = %d\n",Tmp,Distance[count]);
                if(Tmp < Distance[count])
                {
                    Distance[count] = Tmp;
                    Previous[count] = RemoveNode;
                    //If Not Visited,Add into the Priority Queue
                    if(Visited[count] == 0)
                    {
                        ////printf("ADD : %d , Distance = %d\n",count,Distance[count]);
                        NewNode.Node_Num = count;
                        NewNode.Distance = Distance[count];
                        Enqueue(NewNode,&Q);
                    }
                }
            }
        }
    }
    //Print The Result
    char SPF[]="";
    GetPath(Num_of_Node,Source,Destination,Previous,SPF);
    
    /* count = Destination;
    printf("The Path : %d",Destination);
    while(Previous[count] != Empty)
    {
        printf(" <- %d",Previous[count]);
        count = Previous[count];
    }
    printf("\n");
    printf("The Distance = %d",Distance[Destination]);
    printf("\n"); */
}

void GetPath(int Num_of_Node,int Source,int Destination,int Previous[Num_of_Node],char SPF[])
{
    int Node;
    char str[10];
    if(Source == Destination)
    {
        sprintf(str,"%d",Source);
        strcat(str,SPF);
        SPF = str;
        printf("%s\n",SPF);
    }
    else
    {
        sprintf(str,"->%d",Destination);  //formate the int as string
        strcat(str,SPF);                 //Put the Shortest Path back on str and save as str
        SPF = str;
        Node = Previous[Destination];
        GetPath(Num_of_Node,Source,Node,Previous,SPF);
    }

}

