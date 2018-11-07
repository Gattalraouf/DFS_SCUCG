#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

//make this bigger as possible if you work for graphs that have more than 1000000000 node
//TODO change according to the maximum cost used
#define infinite 1000000000

int cost;
int *tmp, *min1, level, *values;

bool isVisited(bool *visited,int V){
    int i;
    for(i=0;i<V;i++) {
        if(visited[i]==false) return false;
    }
    return true;
}

void DFS_SCUCG(int i, int n, bool *visited, int **G,int *tmp, int *min1)
{
    int j;
    //moving to the next level of the tree DFS generates
    level++;
    //Set the Current node to visited
    visited[i]=true;
    //enter the initial element of the table which is the first node to visit in the graph
    if(i==0) tmp[0]=i;
    //Check all the possible cycles
    for(j=0;j<n;j++) {

        if (!visited[j]) {
            //Start counting the cost of every cycle
            cost=cost+G[i][j];
            //saving the cost of edges so we could remove them from the cost when we return
            values[level] =G[i][j];
            //saving the elements order
            tmp[level+1]=j;
            DFS_SCUCG(j, n, visited, G,tmp,min1);

        }
        //check if every node is visited when we are going out of the DFS
        if(isVisited(visited,n)&&j==n-1){
            //saving both the cost and the cycle if it is shorter than the one already saved
            tmp[n]=cost;
            if(min1[n]>tmp[n]) {
                for(i=0;i<=n;i++) {
                    min1[i]=tmp[i];
                }
            }

        }
    }
    //retrieve the cost of the previous level
    cost=cost-values[level-1];
    //mark the node we used in the level as unvisited to allow it to be used in next cycles
    visited[tmp[level]]=false;
    //return in level
    level--;
}



int main() {

    int i;

    int **adj;
    bool *visited;
    int NodesNumber;

    //Number of nodes in the Graph
    //TODO Change the value to what suits your example
    NodesNumber=10;

    adj = malloc(NodesNumber* sizeof(int*));
    for(i=0;i<NodesNumber;i++) {
        adj[i]= malloc(NodesNumber* sizeof(int));
    }

    //Content of adjacency matrix
    //TODO Change the value to what suits your example
    adj[0][0]=0; adj[0][1]=5; adj[0][2]=4; adj[0][3]=3; adj[0][4]=2; adj[0][5]=2; adj[0][6]=2; adj[0][7]=2; adj[0][8]=2; adj[0][9]=2;
    adj[1][0]=5; adj[1][1]=0; adj[1][2]=5; adj[1][3]=5; adj[1][4]=4; adj[1][5]=2; adj[1][6]=2; adj[1][7]=2; adj[1][8]=2; adj[1][9]=2;
    adj[2][0]=4; adj[2][1]=5; adj[2][2]=0; adj[2][3]=2; adj[2][4]=2; adj[2][5]=2; adj[2][6]=2; adj[2][7]=2; adj[2][8]=2; adj[2][9]=2;
    adj[3][0]=3; adj[3][1]=5; adj[3][2]=2; adj[3][3]=0; adj[3][4]=2; adj[3][5]=2; adj[3][6]=2; adj[3][7]=2; adj[3][8]=2; adj[3][9]=2;
    adj[4][0]=2; adj[4][1]=4; adj[4][2]=2; adj[4][3]=2; adj[4][4]=0; adj[4][5]=2; adj[4][6]=2; adj[4][7]=2; adj[4][8]=2; adj[4][9]=2;
    adj[5][0]=2; adj[5][1]=2; adj[5][2]=2; adj[5][3]=2; adj[5][4]=2; adj[5][5]=0; adj[5][6]=2; adj[5][7]=2; adj[5][8]=2; adj[5][9]=2;
    adj[6][0]=2; adj[6][1]=2; adj[6][2]=2; adj[6][3]=2; adj[6][4]=2; adj[6][5]=2; adj[6][6]=0; adj[6][7]=2; adj[6][8]=2; adj[6][9]=2;
    adj[7][0]=2; adj[7][1]=2; adj[7][2]=2; adj[7][3]=2; adj[7][4]=2; adj[7][5]=2; adj[7][6]=2; adj[7][7]=0; adj[7][8]=2; adj[7][9]=2;
    adj[8][0]=2; adj[8][1]=2; adj[8][2]=2; adj[8][3]=2; adj[8][4]=2; adj[8][5]=2; adj[8][6]=2; adj[8][7]=2; adj[8][8]=0; adj[8][9]=2;
    adj[9][0]=2; adj[9][1]=2; adj[9][2]=2; adj[9][3]=2; adj[9][4]=2; adj[9][5]=2; adj[9][6]=2; adj[9][7]=2; adj[9][8]=2; adj[9][9]=0;

    visited = malloc(NodesNumber*sizeof(bool));
    tmp= malloc((NodesNumber+1)*sizeof(int));
    min1= malloc((NodesNumber+1)*sizeof(int));
    values= malloc((NodesNumber)*sizeof(int));

    for(i=0;i<NodesNumber;i++) {
        visited[i]=false;
        tmp[i]=0;
        min1[i]=infinite;
        values[i]=0;
    }
    min1[NodesNumber] = infinite;
    tmp[NodesNumber]=0;

    cost =0;
    level =-1;

    //Start of the Algorithm
    DFS_SCUCG(0,NodesNumber,visited,adj,tmp,min1);

    printf("The minimum cost is :%d \nThe Shortest Cycle is:",min1[NodesNumber]);
    for(i=0;i<NodesNumber;i++) {
        printf(" %d |",min1[i]);
    }
    printf(" %d ",min1[0]);
    return 0;
}