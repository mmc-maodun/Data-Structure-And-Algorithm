# Data-Structure-And-Algorithm
Data Structure And Algorithm（常用数据结构与算法C/C++实现）
# DataStructutres-Project
------------Sorting Algo with  coding-------
1) Bubble Sort
2) Insertion Sort
3) Selection Sort
4) Quick Sort
5) Merge Sort
6) Count Sort
7) Radix sort
8) Bucket/Bin Sort
9) Shell Sort

-----Bubble Sort-----------
#include<stdio.h>

void swap(int *x,int *y)
{
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}

void BubbleSort(int arr[],int n)
{
	int i,j,flag;
	for(i=0;i<n-1;i++)
	{  
	     flag=0;  //optimize the code if list already sorted we don't need to go next passes
		for(j=0;j<n-1-i;j++)
		{
			if(arr[j]>arr[j+1]){
			 swap(&arr[j],&arr[j+1]);
		     flag=1;
			}
		}
		if(flag==0)
		  break;
	}
}

void main()
{
	int i;
	int arr[]={7,2,4,3,2,1,2};
	
	BubbleSort(arr,7);
	
	for(i=0;i<7;i++)
	  printf("%d\n",arr[i]);
}


----Insertion Sort---------
void InsertionSort(int arr[],int n)
{
	int i,j,temp;
	for(i=1;i<n;i++)
	{
		temp=arr[i];
		j=i-1;
		while(j>=0 && arr[j]>temp)
		{
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=temp;
	}
}


void main()
{
	int i;
	int arr[]={8,5,3,7,2};
	
	InsertionSort(arr,5);
	
	for(i=0;i<5;i++)
	  printf("%d\n",arr[i]);
}

---Selection Sort------
#include<stdio.h>
void swap(int *x,int *y)
{
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}


void selectionSort(int arr[],int n)
{
	int i,j,min;
	for(i=0;i<n-1;i++)
	{
		min=i;
		for(j=i+1;j<n;j++)
		{
			if(arr[j]<arr[min])
			 min=j;
		}
		swap(&arr[i],&arr[min]);
	}
}

void main()
{
	int i;
	int arr[]={8,6,3,2,5,4};
	
	selectionSort(arr,6);
	
	for(i=0;i<6;i++)
	  printf("%d\n",arr[i]);
}

---Quick Sort------

#include<stdio.h>

int partition(int arr[],int start,int end)
{
	int x=(rand()%(end-start+1))+start;  //for pick randome element 
	int pindex=start,i,temp;
	
	temp=arr[end];        //swap(arr[x],arr[end])
	arr[end]=arr[x];
	arr[x]=temp;
	
	int pivote=arr[end];
	for(i=start;i<end;i++)
	{
		if(arr[i]<=pivote)
		{
			temp=arr[i];
			arr[i]=arr[pindex];
			arr[pindex]=temp;
			pindex++;
		}
	}
	arr[end]=arr[pindex];
	arr[pindex]=pivote;
    return pindex;
}

void QuickSort(int arr[],int s,int e)
{
	int pindex;
	if(e>s)
	{
		pindex=partition(arr,s,e);
		QuickSort(arr,s,pindex-1);
		QuickSort(arr,pindex+1,e);
	}
}

void main()
{
	int i;
	int arr[]={7,2,1,6,8,3,4};
	
	QuickSort(arr,0,6);
	
	for(i=0;i<7;i++)
	  printf("%d\n",arr[i]);
}

---Merge Sort---
#include<stdio.h>
void MergeSort(int arr[],int start,int end)
{
	int mid;
	if(end>start)
	{
		mid=(start+end)/2;
		MergeSort(arr,start,mid);
		MergeSort(arr,mid+1,end);
		Merge(arr,start,end,mid);
	}
}

void Merge(int arr[],int s,int e,int mid)
{
	int n1=(mid-s)+1;  //size of left array
	int n2=e-mid;      //size of right array
	int L[n1],R[n2];   //creating left and right array
	int i,j,k;
	for(i=0;i<n1;i++)
   	   L[i]=arr[s+i];      //copy left element array to left array 
	for(i=0;i<n2;i++)
	   R[i]=arr[mid+1+i];      //copy right element array to right array
	i=0;j=0;k=s;
	while(i<n1 && j<n2)
	{
	    if(L[i]<=R[j])
		  arr[k++]=L[i++];
		else
		  arr[k++]=R[j++];  	
    }      
    while(i<n1)
    {
    	arr[k++]=L[i++];
	}
	 while(j<n2)
    {
    	arr[k++]=R[j++];
	}
}

void main()
{
	int arr[]={7,2,1,6,8,5,3,4};
	int i;
	MergeSort(arr,0,7);
	printf("After performing sorting:\n");
	for(i=0;i<8;i++)
	  printf("%d\n",arr[i]);
}

---count Sort---
#include<stdio.h>

int maxEle(int arr[],int n)
{
	int i,max=arr[0];
	for(i=1;i<n;i++)
	{
		if(arr[i]>max)
		  max=arr[i];
	}
	return max;
}

void countSort(int arr[],int n)
{
	int output[n];
	int max=maxEle(arr,n);
	int count[max+1];
	int i;
	 
	for(i=0;i<=max;i++)
	    count[i]=0;
	
	for(i=0;i<n;i++)
	   count[arr[i]]++;
	   
	for(i=1;i<=max;i++)
	  count[i]=count[i]+count[i-1];
	  
	for(i=n-1;i>=0;i--)
	   output[--count[arr[i]]]=arr[i];
	   
	for(i=0;i<n;i++)
	   arr[i]=output[i];       	 
}

void main()
{
    int i; 
	int arr[]={6,4,3,4,5,2,5,1,0,8};
	countSort(arr,10);
		printf("After performing sorting:\n");
	for(i=0;i<10;i++)
	  printf("%d\n",arr[i]);
}

--Radix Sort---

#include<stdio.h>
int maxEle(int arr[],int n)
{
	int i,max=arr[0];
	for(i=1;i<n;i++)
	{
		if(arr[i]>max)
		  max=arr[i];
	}
	return max;
}

void countSort(int arr[],int n,int temp)
{
	int output[n];
	int count[10];
	int i;
	 
	for(i=0;i<10;i++)
	    count[i]=0;
	
	for(i=0;i<n;i++)
	   count[(arr[i]/temp)%10]++;
	   
	for(i=1;i<10;i++)
	  count[i]=count[i]+count[i-1];
	  
	for(i=n-1;i>=0;i--)
		output[--count[(arr[i]/temp)%10]]=arr[i];
	
	for(i=0;i<n;i++)
	   arr[i]=output[i];       	 
}


void radixSort(int arr[],int n)
{
	int max=maxEle(arr,n);
	int temp;
	for(temp=1;max/temp>0;temp=temp*10)
	{
		countSort(arr,n,temp);
	}
}

void main()
{
	int i; 
	int arr[]={212,107,150,25,5,2,99,160,45};
	radixSort(arr,9);
		printf("After performing sorting:\n");
	for(i=0;i<9;i++)
	  printf("%d\n",arr[i]);
}

---Shell Sort----









