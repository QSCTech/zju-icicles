//TheSecondShortestPath.c

/*header files*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*Macro Definition*/
#define New(type,n) (type*)malloc(sizeof(type)*n) //Alloc a new space with specific size and use.
#define NewArray(type,n) (type*)calloc(n,sizeof(type)) //Alloc a new space served as an array with specific size and use.
#define NULLPOS -1 //which implies a variable is not existing, often used in stack, queue, heap and other structures.
#define INFINITY INT_MAX //Used to initialize the distance of vertices from the start point.
#define ROOT 1 //point to the minimum element of the heap.
#define Parent(i) (i/2) //the parent of the node i in the heap
#define Left(i) (2*i) //the left child of the node i in the heap
#define Right(i) (Left(i)+1) //the right child of the node i in the heap
#define TRUE 1 //Used to tell the status of a function or a variable, the same as FALSE
#define FALSE 0
#define BEGIN -2 //Used to simulate the last vertex of the start vertex

typedef int element; //used for elements in the stack, which are vertex numbers

typedef struct node // used in ADJ linked list as a node
{
    int vertex;
    int weight;
    struct node* next;
}*list;

typedef struct g{ //The structure of the whole graph.
    int v; //The number of the vertices in graph
    int e; //The number of edges in graph
    list* AdjList; // ADJ linked list, with edges storing in it.
}*graph;

typedef struct h //The structure of a heap
{
    int capacity; //the max number of elements a heap can hold.
    int* vertices; //store the vertices number for every node. vertices[0] = the number of elements in the heap.
    int* distance; //store the distance of each vertex.
}*heap;

typedef struct s //The structure of a stack
{
    int top; //stack top
    int capacity; //the max number of elements a heap can hold.
    element* container; //store the elements in the stack, that is, a vertex number.
}*stack;

/* Function: Top_k
 * Used to get the k_th element away
 * from the stack top.
 * 
 * k: the k_th number, 0 is on the top.
 * s: the stack need to provide
 */
int Top_k(int k,stack s);

/* Function: Minimum
 * Used to get top element of the heap.
 * 
 * h: heap structure need to provide
 * 
 * return_dst: provide the pointer, 
 * and the function will put the 
 * distance of the element in it.
 * 
 * return_vertex:provide the pointer, 
 * and the function will put the 
 * vertex number of the element in it.
 * 
 * If there's no element in the heap,
 * it will return FALSE;
 * else, return TRUE.
 */
int Minimum(heap h,int* return_dst,int* return_vertex);

/* Function: ShortestPath
 * Used to calculate the shortest
 * path in the graph and its path
 * given a source and a destination.
 * with Dijkstra Algorithm.
 * 
 * h: heap you need to provide
 * 
 * g: graph you need to provide
 * 
 * dst: the function will save the shortest
 * distances of each vertex from the source 
 * in it, please make sure it points
 * to a address in the memory with enough
 * space.
 * 
 * source: start point
 * 
 * dest: end point
 * 
 * path: the function will save the shortest
 * paths of each vertex from the source 
 * in it, please make sure it points
 * to a address in the memory with enough
 * space.
 */
int ShortestPath(heap h,graph g,int dst[],int source,int dest,int path[]);

/* Function: ShortestPath
 * Used to calculate the second shortest
 * path in the graph and its path
 * given a source and a destination
 * with Dijkstra Algorithm.
 * 
 * h: heap you need to provide
 * 
 * g: graph you need to provide
 * 
 * dst: the function will save the shortest
 * distances of each vertex from the source 
 * in it, please make sure it points
 * to a address in the memory with enough
 * space.
 * 
 * source: start point
 * 
 * dest: end point
 * 
 * dst_second: the function will save the 
 * second shortest distances of each vertex
 * from the source in it, please make sure 
 * it points to a address in the memory with
 * enough space.
 * 
 * path: the function will save the shortest
 * paths of each vertex from the source 
 * in it, please make sure it points
 * to a address in the memory with enough
 * space.
 * 
 * sec_path: the function will save the second 
 * shortest paths of each vertex from the source 
 * in it, please make sure it points
 * to a address in the memory with enough
 * space.
 */
int SecondShortestPath(heap h,graph g,int source,int dest,int dst[],int dst_second[],int path[],int sec_path[]);

/* Function: ShortestPath
 * Used to make the heap empty.
 * h: the heap you need to provide.
 */
void dispose(heap h);

/* Function: exchange
 * Swap the values of two
 * integer.
 * a: operand 1
 * b: operand 2
 */
void exchange(int* a,int* b);

/* Function: push
 * push the element in
 * the stack.
 * 
 * x: the element needed to
 * be provide, often being a
 * vertex number.
 */
void push(stack s,element x);

/* Function: insert
 * insert an element in heap
 * 
 * h: heap
 * vertex: the vertex field of the element put in
 * dst: the distance field of the element put in
 */
void insert(heap h,int vertex,int dst);

/* Function: increase
 * increase the distance of the element in
 * heap, and let in sink in the heap, so that
 * we matain a min-heap's property
 * 
 * h: heap
 * vertex: the index of the element to increase
 * NewDistance: refresh the distance value
 */
void increase(heap h,int index,int NewDistance);

/* Function: decrease
 * decrease the distance of the element in
 * heap, and let it get up from the heap, so that
 * we matain a min-heap's property
 * 
 * h: heap
 * vertex: the index of the element to increase
 * NewDistance: refresh the distance value
 */
void decrease(heap h,int index,int NewDistance);

/* Function: SetSource
 * Often used before a Dijkstra Algorithm, to
 * Initialize the distance and path arrays given
 * a start point.
 * 
 * v: the number of vertices
 * source: the start point
 * dst: distance array
 * path: path array
 */
void SetSource(int v,int source,int dst[],int path[]);

/* Function: PrintPath
 * print the second shortest path
 * 
 * s: stack used in this procedure
 * 
 * end: the end point
 * 
 * short_path: the length of the shortest path
 * 
 * dst: the shortest distances of vertices 
 * away from the source (start point)
 * 
 * reverse_dst: the shortest distances of vertices 
 * away from the end (end point)
 * 
 * path: the shortest path for source(basically, source=0)
 * reverse_path: the shortest path end(basically, end=v-1)
 * sec_path: the second shortest path for source
 */
void PrintPath(stack s,int end,int short_path,int dst[],int reverse_dst[],int path[],int reverse_path[],int sec_path[]);

/* Function: push
 * pop the element from
 * the stack.
 * 
 * return the element popped.
 */
element pop(stack s);

/* Function: push
 * Create a heap.
 * capacity: the maximum size of the heap
 * return the heap variable.
 */
heap CreateHeap(int capacity);

/* Function: push
 * Create a graph
 * v: the number of vertices
 * e: the number of edges
 * return the graph created.
 */
graph CreateGraph(int v,int e);

/* Function: CreateStack
 * Create a stack.
 * capacity: the maximum size of the stack
 * return the stack
 */
stack CreateStack(int capacity);

/* Function: CreateStack
 * Create a node.
 */
list CreateNode(int vertex,int weight,list next);


int main(){
    int v,e;
    scanf("%d%d",&v,&e);
    graph g=CreateGraph(v,e);
    heap h=CreateHeap(4*e+1);

    int* path=New(int,v);
    int* reverse_path=New(int,v);//the shortest path from end point, namely v-1.
    int* sec_path=New(int,v);
    int* dst=New(int,v);
    int* reverse_dst=New(int,v);//the shortest distances away from end point, namely v-1.
    int* sec_dst=New(int,v);
    assert(path&&reverse_dst&&reverse_path&&sec_path&&dst&&reverse_dst&&sec_dst);//assert all space alloced are valid.

    int shortest_path=ShortestPath(h,g,reverse_dst,v-1,0,reverse_path);
    int sec_shortest_path=SecondShortestPath(h,g,0,v-1,dst,sec_dst,path,sec_path);

    printf("%d",sec_shortest_path);

    stack s=CreateStack(e+3);
    PrintPath(s,v-1,shortest_path,dst,reverse_dst,path,reverse_path,sec_path);

    return 0;
}

int Top_k(int k,stack s){
    if(s->top-1-k<0) return NULLPOS;//the number of stack is too few.
    return s->container[s->top-1-k];
}

void PrintPath(stack s,int end,int short_path,int dst[],int reverse_dst[],int path[],int reverse_path[],int sec_path[]){
    /* Since the path[] only
     * store the last vertex,
     * to print the path, we 
     * need a stack to invert
     * the order we print.
     */ 
    int vertex=end;//start from end point.
    int backed=FALSE;//if backed=TRUE, we can straightly head to the source with shortest path.
    int tmp;    

    while (vertex!=BEGIN){
        
        if(
            //the case that the vertex is not in the shortest path.
            dst[vertex]+reverse_dst[vertex]!=short_path ||
            //the case that vertices in the shortest path between the vertex and last vertex are skipped.
            (tmp=Top_k(0,s))!=NULLPOS && tmp !=reverse_path[vertex] ||
            //the case that the last vertex of last vertex is the same as the current vertex.
            Top_k(1,s) == vertex
        )
            backed=TRUE;//the detour has finished.

        push(s,vertex);

        if(backed){
            vertex=path[vertex];//go straight in the shoretest path.
        }
        else{
            vertex=sec_path[vertex];
        }
        
    }

    //print the vertices in the path.
    while((vertex=pop(s))!=NULLPOS){
        printf(" %d",vertex+1);
    }
}

void dispose(heap h){
    h->vertices[0]=0;
}

void push(stack s,element x){
    assert(s->top<=s->capacity);
    s->container[s->top++]=x;
}

element pop(stack s){
    if(!(s->top)) return NULLPOS;
    return s->container[--(s->top)];
}

void exchange(int* a,int* b){
    int tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}

void SetSource(int v,int source,int dst[],int path[]){
    int i;
    for(i=0;i<v;i++){
        dst[i]=INFINITY;
        path[i]=NULLPOS;
    }

    dst[source]=0;
    path[source]=BEGIN;
}

list CreateNode(int vertex,int weight,list next){
    list p = New(struct node,1);
    assert(p);
    p->vertex=vertex;
    p->weight=weight;
    p->next=next;
    return p;
}

graph CreateGraph(int v,int e){
    graph g = New(struct g,1);
    assert(g);
    g->e=e;
    g->v=v;
    g->AdjList=NewArray(list,v);
    assert(g->AdjList);

    int va,vb,w;

    while (e--)
    {
        scanf("%d%d%d",&va,&vb,&w);
        va--;//Because the C array begins from 0, we substact every vertex by 1 to save the space.
        vb--;
        g->AdjList[va]=CreateNode(vb,w,g->AdjList[va]);//Let the new node be the first element of the ADJ list.
        g->AdjList[vb]=CreateNode(va,w,g->AdjList[vb]);
    }
    return g;
}

heap CreateHeap(int capacity){
    heap h = New(struct h,1);
    assert(h);
    h->capacity=capacity;

    h->vertices=New(int,capacity+1);
    assert(h->vertices);

    h->distance=NewArray(int,capacity+1);
    assert(h->distance);

    h->vertices[0]=0;// h->vertices[0] = the number of elements in the heap.
    return h;
}


void decrease(heap h,int index,int NewDistance){//we make the distances the key field of elements in the heap.
    int p;
    int vertex = h->vertices[index];
    while(index > ROOT){
        p=Parent(index);
        if(NewDistance<h->distance[p]){
            h->vertices[index]=h->vertices[p];
            h->distance[index]=h->distance[p];
        }
        else break;
        index = p;
    }
    h->vertices[index]=vertex;
    h->distance[index]=NewDistance;
}

void increase(heap h,int index,int NewDistance){
    int child;
    int vertex = h->vertices[index];
    int LastLeaf=h->vertices[0];

    while(index <= Parent(LastLeaf)){
        child = Left(index);
        if(child!=LastLeaf && h->distance[child]>h->distance[Right(index)])
            child=Right(index);

        if(NewDistance>h->distance[child]){
            h->vertices[index]=h->vertices[child];
            h->distance[index]=h->distance[child];
        }
        else break;
        index=child;
    }
    h->vertices[index]=vertex;
    h->distance[index]=NewDistance;
}

void insert(heap h,int vertex,int dst){
    int LastLeaf = ++(h->vertices[0]);
    assert(LastLeaf<=h->capacity);

    h->vertices[LastLeaf]=vertex;
    decrease(h,LastLeaf,dst);
}

int Minimum(heap h,int* return_dst,int* return_vertex){
    if(h->vertices[0]==0) return FALSE;//There's no element in the heap.
    * return_vertex = h->vertices[ROOT];
    * return_dst = h->distance[ROOT];
    
    int LastLeaf = h->vertices[0]--;
    h->vertices[ROOT]=h->vertices[LastLeaf];

    increase(h,ROOT,h->distance[LastLeaf]);
    return TRUE;
}

int SecondShortestPath(heap h,graph g,int source,int dest,int dst[],int dst_second[],int path[],int sec_path[]){
    int v=g->v;
    int vertex,distance,NewDistance,neighbor,weight,NewVertex;

    dispose(h);

    SetSource(v,source,dst,path);
    SetSource(v,source,dst_second,sec_path);

    /* The second shortest distance from source
     * to source need to be initialized as INFINITY,
     * otherwise the algorithm won't work because the
     * if-statement in line 497.
     */
    dst_second[source]=INFINITY;

    insert(h,source,dst[source]);

    list p;

    while(Minimum(h,&distance,&vertex)){
        if(distance <= dst_second[vertex]){
            p=g->AdjList[vertex];
            while(p){
                neighbor=p->vertex;
                NewDistance=p->weight+distance;
                NewVertex=vertex;

                if(NewDistance < dst[neighbor]){
                    /* if the original distance is larger,
                     * it can be used for the second 
                     * shortest distance.Therefore, we use
                     * a "exchange" to assign the NewDistance
                     * with original shortest distance for the
                     * next if-statement.
                     */
                    exchange(&dst[neighbor],&NewDistance);
                    exchange(&NewVertex,&path[neighbor]);
                    insert(h,neighbor,dst[neighbor]);
                }

                if(NewDistance > dst[neighbor] && NewDistance < dst_second[neighbor]){
                    dst_second[neighbor]=NewDistance;
                    sec_path[neighbor]=NewVertex;
                    //The second shortest distance should also be put into the heap.
                    insert(h,neighbor,dst_second[neighbor]);
                }

                p=p->next;
            }
        }
    }
    return dst_second[dest];

}

stack CreateStack(int capacity){
    stack s=New(struct s,1);
    assert(s);
    s->top=0;
    s->capacity=capacity;
    s->container=New(element,capacity);
    assert(s->container);
    return s;
}

int ShortestPath(heap h,graph g,int dst[],int source,int dest,int path[]){
    int vertex = source;
    int neighbor;
    int distance;
    int v=g->v;
    list p = NULL;

    int *include=New(int,v);//The array used to tell if an element has been popped from the heap.

    assert(include);

    SetSource(v,source,dst,path);
    memset(include,FALSE,sizeof(int)*v);//All elements are not included at the beginning.

    dispose(h);

    insert(h,source,dst[source]);

    while(Minimum(h,&distance,&vertex)){
        if(!include[vertex]){
            include[vertex]=TRUE;
            
            p=g->AdjList[vertex];
            while(p){
                neighbor = p->vertex;

                if(!include[neighbor]){

                    if(dst[neighbor]>distance+p->weight){
                        dst[neighbor]=distance+p->weight;
                        path[neighbor]=vertex;
                        insert(h,neighbor,dst[neighbor]);
                    }
                }   
                p=p->next;
            }
        }
    }

    free(include);
    return dst[dest];
}