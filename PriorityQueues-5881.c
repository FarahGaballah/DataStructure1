#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct
{
 char* cName;
 double balance;
 int order;
}Item;
/*
 * Heapify index i in array of Items with size n
 */
 void swap( int *a, int *b ) {
  int t;
  t = *a;
  *a = *b;
  *b = t;
}


void max_heapify(Item *arr, int n, int i)
{
	int left, right, largest, parent;
	double temp;
	left = 2*(i);
	right = left + 1;
	largest = i;
	parent=i/2;

 if(left<=n && left>0)
    {
       if(arr[left].balance>arr[i].balance)
       {
           if(arr[left].balance>arr[right].balance){
            largest=left;
            temp = arr[i].balance;
		arr[i].balance = arr[largest].balance;
		arr[largest].balance = temp;
		swap(&arr[i],&arr[largest]);
		max_heapify(arr, n,largest);

           }
       }
    }

    /*while(i>0 && arr[parent].balance==arr[i].balance){
        if(arr[parent].order<arr[i].order){

        swap(&arr[i],&arr[parent]);

        i= parent;
    }}*/






    }






/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ(Item*arr,int n)
{
           for(int i = n/2; i >= 1; i--)
    {
          max_heapify(arr,n,i);
    }

}


// delete the item with max priority and then return it.

Item extract_maximum(Item*arr,int n)
{  Item max;
   max.balance= arr[1].balance;

  arr[1]= arr[n];
  n-=1;
  max_heapify(arr,n,1);
  return max;

}
/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)
{   int i =0;
    int arraySize=0;
  //int order;
double customerBalance;
	FILE* f=fopen(fname,"r");
    assert(f!=NULL);

    while(!feof(f)){
        char* customerName=(char*)malloc(50*sizeof(char));
        fscanf(f,"%s %lf ",customerName,&customerBalance);
        arr[i].cName=customerName;
        arr[i].balance= customerBalance;
        i+=1;
        arr[i].order=i;
        arraySize+=1;
        //arr[i].order=i+1;
       // arr->cName =(char*)malloc(sizeof(0));
       // printf("%s",arr->cName);
    }
    return arraySize;
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{  char name[50];
   int i;
/*   //for(i=n;i>=1;i--)
   {
       //name= arr[i].cName;
      // printf("%s %lf %d\n",arr[i].cName,arr[i].balance,arr[i].order);
      // printf("%d",n);

   }*/
   for ( i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[j].balance < arr[i].balance)
			{
				double tmp = arr[i].balance;
				arr[i].balance = arr[j].balance;
				arr[j].balance = tmp;
				swap(&arr[j].cName,&arr[i].cName);
				swap(&arr[j].order,&arr[i].order);
			}

		}

	}

	for (int i = 0; i < n; i++)
	{ for (int j = 0; j < n; j++)
		{if(arr[j].balance==arr[i].balance){
                if(arr[j].order<arr[i].order){
                  swap(&arr[j].cName,&arr[i].cName);

                        swap(&arr[i].balance,&arr[j].balance);

                }
			}}
		printf(" %s %0.0f %d\n", arr[i].cName,arr[i].balance,arr[i].order);

	}

}
/*
 *
 */
int main(int argc, char**argv) {

	if(argc!=2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile(argv[1],customers);
    construct_PQ(customers,arrLength);
    printCustomersbyPriority(customers,arrLength);
    return 0;
}
