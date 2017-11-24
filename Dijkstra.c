#include<stdio.h>
#include<string.h>

#define Infinity 999

int main(int argc, char *argv[])
{
    int Num_of_Node = 0 , Num_of_EndNode = 0 , Num_of_Link = 0;
    int count1 = 0 , count2 = 0;
    int Node1 = 0 , Node2 = 0; 
    int ignore;

    //open the topology file
    FILE *file;
    file = fopen("cnstln36.txt","r");
    //Read topology information
    fscanf(file,"%d",&Num_of_Node);
    fscanf(file,"%d",&Num_of_EndNode);
    fscanf(file,"%d",&Num_of_Link);
    printf("%d %d %d\n",Num_of_Node,Num_of_Link,Num_of_EndNode);


    //Initial the Link Matrix of Node(ALL Link are Infinity First)
    int LinkMatrix[Num_of_Node][Num_of_Node];
    for(count1 = 0; count1 < Num_of_Node; count1++)
    {
        for(count2 = 0;count2 < Num_of_Node;count2++)
        {
            if(count1 == count2)
            {
                LinkMatrix[count1][count2]=0;
            }
            else
            {
                LinkMatrix[count1][count2]=Infinity;
            }
        }
    }


    //Fill in the Link State on cnstln36
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
}