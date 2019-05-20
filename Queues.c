#include <stdio.h>
#include <stdlib.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct {
	char *name;
	int remaining_time;
} Process, *Item;
/*
 *
 */
typedef struct Node {
	Item data;
	struct Node* next;
} Node;
/*
 *
 */
typedef struct {
	Node* top;
	Node* bottom;
} Queue;
/*
 *
 */
void init(Queue *q) {
  q->top=NULL;
   q->bottom=NULL;


}
/*
 *
 */
int isEmpty(Queue *q) {
	return(q->top==NULL&&q->bottom==NULL);

}
/*
 *
 */
 // delete the front node and returns its value
Item dequeue(Queue *q) {
     Node *p;
	 Item x= q->top->data;
	 p=q->top;
	 q->top=q->top->next;
	 free(p);
     return(x);

}
/*
 *
 */
void enqueue(Queue *q, Item val) {
	Node *p;
	 p = malloc(sizeof(Node));
	 p->data= val;
	 p->next=NULL;
	 if(isEmpty(q)){
        q->top = q->bottom = p;
	 }
	 else{
        q->bottom->next= p;
        q->bottom=p;
	 }
}
/*
 *
 */
void destroy(Queue *q) {
	/*Node*p;
	q->top;
	while(p->next != NULL){

	 p = p -> next;
}
free(p);*/
int count=0;

    while(!isEmpty(q)){
        count++;
    }
    for(int i=1;i<count;i++)
        free(q);
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
   Queue *q= (Queue*)malloc(sizeof(Queue));
   init(q);
   Process p1, p2;
   Item m = &p1;
   Item n;
   FILE* f = fopen("robinhood.txt","r");
   while(!feof(f)){
        fscanf(f,p1.name,p1.remaining_time);
   enqueue(q,m);
   n= dequeue(q);


   }
   fclose(f);

}
/*
 *
 */
int main(int argc, char**argv) {
	if(argc!=2) {
		printf("Usage: %s robinhood.txt\n", argv[0]);
		exit(1);
	}

	RoundRobin(argv[1]);

	return 0;
}
