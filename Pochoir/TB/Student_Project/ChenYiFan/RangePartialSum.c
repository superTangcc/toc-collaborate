/*  imply sum  */

#include <stdio.h>

#define MAX(a, b) ( (a>b)?a:b )
#define LEVEL 10
int val[1025];
int num2order[1025];
int order2num[1025];
int dist[1025][12];
int valid[1025][12];
int count=0;


/*  return the binary lenth of int x */
int tLength(int x) {  
    int mask1 = 17;
    int mask2 = 15;
    mask1 += mask1 << 8;
    mask1 += mask1 << 16;
    mask2 += mask2 << 8;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    x = (x & mask1) + ((x >> 1) & mask1) + ((x >> 2) & mask1) + ((x >> 3) & mask1);
    x = x + (x >> 16);
    x = (x & mask2) + ((x >> 4) & mask2);
    x += x >> 8;
    x = x & 255;        
    return x + ~0 + 1;
}


/*  return the length of the longest common prefix */
int LCP(int a, int b){
    int tmp,l1,l2;
    if (a < b){
        tmp = a;
        a = b;
        b = tmp;
    }
    l1 = tLength(a);
    l2 = tLength(b);
    if (l1 > l2)
        b = b << (l1 - l2);
    l1 = l1 - tLength(a^b);
    if (l1 > l2)
        l1 = l2;
    return l1;
    
}


/*  set pointer  */
void setNum(int n){
    if (n >= 1024/2){
        count++;
        num2order[count]=n;
        order2num[n]=count;
        return;
    }
    setNum(n*2);
    count++;
    num2order[count]=n;
    order2num[n]=count;
    setNum(n*2+1);
}


/*  define plus*/
int plus(int a,int b){
    return a+b;
}


/*  find sum between a certain number n and it's father at level lvl in the tree*/
int findDist(int n, int lvl){
    if (valid[n][lvl] == 1)
        return dist[n][lvl];
    int num1 = order2num[n];
    int num2 = order2num[n>>(tLength(n)-lvl)];
    if (num1 == num2){
        valid[n][lvl] = 0;
        dist[n][lvl] = 0;
        return 0;
    }
    int result;
    if (abs(num1 - num2 )<=1){
        result = 0;
    }else if (num1 < num2){
        result = plus(val[num1+1], findDist(num2order[num1+1], lvl));
    }else if (num1 > num2){
        result = plus(findDist(num2order[num1-1], lvl), val[num1-1]);
    }
    valid[n][lvl]=1;
    dist[n][lvl]=result;
    return result;
    
}

/*  calculate the sum from NO.a to NO.b*/
int cal(int a, int b){
    int level = LCP(num2order[a], num2order[b]);
    int result;
    int lvla = tLength(num2order[a]);
    int r = num2order[a] >>(lvla - level);
    result = plus(findDist(num2order[a],level) ,  val[order2num[r]]);
    result = plus(result,findDist(num2order[b],level));
    if (num2order[a]!=r)
        result = plus(val[a],result);
    if (num2order[b]!=r)
        result = plus(result,val[b]);
    return result;
}


/*  set valid[][] to 0*/
void setDist(){
    int i,j;
    for (i=0; i<1025; i++)
        for (j=0; j<1025; j++)
            valid[i][j]=0;    
}


/*  set value of each number.  To help us check the correctness of this program, we set the value of every number to 1, so the sum from Number a to Number b should be (b-a+1) */
void init(){
    int i,j;
    for (i=0; i<1025; i++)
        val[i]=1;
    setNum(1);
    setDist();
}

/*  some examples*/
void main(){
    init();
    printf("from %d to %d is %d\n",1,1,cal(1,1));
    printf("from %d to %d is %d\n",1,1023,cal(1,1023));
    printf("from %d to %d is %d\n",4,8,cal(4,8));
    printf("from %d to %d is %d\n",555,666,cal(555,666));
}
