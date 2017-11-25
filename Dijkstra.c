#include<stdio.h>
#include<string.h>

#define Infinity 999

int main(int argc, char *argv[])
{
    int Num_of_Node = 0 , Num_of_EndNode = 0 , Num_of_Link = 0;
    int count1 = 0 , count2 = 0;
    int Node1 = 0 , Node2 = 0; 
    int ignore;
    int Source , Destination; 
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

/* 
    //print the LinkState
    for(count1=0;count1<Num_of_Node;count1++)
    {
        for(count2=0;count2<Num_of_Node;count2++)
        {
            printf("%d ",LinkMatrix[count1][count2]);
        }
        printf("\n");
    }  
*/
    printf("Please key in the Source Node:");
    scanf("%d",&Source);
    printf("\nPlease key in the Destination Node:");
    scanf("%d",&Destination);
    Dijkstra(Source,Destination,Num_of_Node,LinkMatrix[Num_of_Node][Num_of_Node]);
}

void Dijkstra(int Source , int Destination,int Num_of_Node, int LinkMatrix[Num_of_Node][Num_of_Node])
{
    int Distance[Num_of_Node];
    int Previous[Num_of_Node];
    int Visited[Num_of_Node];
    int count;
    //initial the distance and shorted path from source
    for(count = 0;count < Num_of_Node;count++)
    {
        //set the distance of source neighbor as 1, others as infinity
        if(LinkMatrix[Source][count] == 1)
        {
            Distance[count] = 1;
        }
        else
        {
            Distance[count] = Infinity;
        }
        //set Source to Source as 0
        if(Source == count)
        {
            Distance[count] = 0;
        }
    }
    //
}