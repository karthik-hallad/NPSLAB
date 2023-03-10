#include <stdio.h>
#define N 15
int adj[N][N], dist[N], prev[N], n;
//adj -> edges

void bellmanFord(int src)
{
    int k, i, j;
    for (k = 0; k < n; k++)
    {
    	// running it k times
    	// for each node(i) -> if dist[i] + adj < dist[j]
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (dist[j] > dist[i] + adj[i][j])
                {
                    dist[j] = dist[i] + adj[i][j];
                    //starting src=0, so dist[i] =0 
                    prev[j] = i;
                }
            }
        }
    }
    printf("\nFor Source %d :\n\n", src + 1);
    for (i = 0; i < n; i++)
    {
        if (i == src)
            continue;
            
        j = i;
        printf("Node:%-3d  Distance:%-3d  Path: ", i+1, dist[i]);
        while (j != src)
        {
            printf("%d<-", j+1);
            j = prev[j];
        }
        //3<-2<-src
        printf("%d\n", src+1);
    }
}

int main()
{
    int i, j, src, neg = 0;
    printf("Enter number of nodes : ");
    fflush(stdout);
    scanf("%d", &n);
    printf("Enter adjacency matrix :\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            //if no edge 999
            scanf("%d", &adj[i][j]);
            if (adj[i][j] < 0)
                neg = 1;
        }
    }
    if (neg)
    {
        printf("Negetive edge present!\n");
        return 0;
    }
    
    for (src = 0; src < n; src++)
    {
    	//for each node try dv seprately
    	//src = 0 , dist[src]=0
        for (i = 0; i < n; i++)
        {
        	
            dist[i] = 999;
            prev[i] = -1;
        }
        dist[src] = 0;
        bellmanFord(src);
    }
    return 0;
}
