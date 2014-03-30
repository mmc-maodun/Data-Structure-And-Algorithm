/*
回溯法求一个集合中和为定值的所有组合
*/

#include <stdio.h>
#define N 11
int w[N] = {1, 2, 7, 4, 11, 6, 5, 9, 14, 8, 3}; 
int r[N];           
int bag = 9;    

int Search(int *w, int *r, int pos, int weight); 

int main()
{
    int n = Search(w, r, N-1, bag);
    printf("%d",n);
    return 0;
}


int Search(int *w, int *r, int pos, int weight)
{
    static int sum = 0;
    int j;
   if(weight == 0){
        ++sum;
        for(j=N-1; j>pos; --j)
            if(r[j]) printf("%d ", w[j]);
   printf("\n");
    }
   else if

(weight>0 && pos>=0){
    r[pos] = 1;
    Search(w, r, pos-1, weight-w[pos]);
    r[pos] = 0;
    Search(w, r, pos-1, weight);
    }
    return sum;
}
