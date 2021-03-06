#include<stdio.h>
#include<stdlib.h>
enum GridStatus{
    Active , Removed, Empty
};
typedef enum GridStatus Status;
struct HashTable
{
    int *key ;
    Status *status;
    int size ;
    int remain;
};
typedef struct HashTable* HT;
HT initHashTable(int size){
    HT h; 
    h=(HT)malloc(sizeof(struct HashTable));
    if(!h ) return NULL;
    h->size=size;
    h->remain=size;
    h->key=(int*)malloc(sizeof(int)*size);
    if(!h->key){ free(h);return NULL; }
    h->status=(Status*)malloc(sizeof(Status)*size);
    if(!h->status){free(h->key);free(h);return NULL;}
    for(int i=0;i<size;i++){
        h->status[i]=Empty;
    }
    return h;
}
int hash(int x,int p){
    return x%p;
}
int isFull(const HT h){
    return h->remain==0;
}
int insertX(int x,HT h){
    if(isFull(h)) return 0;
    int pos=hash(x,h->size);
    while(h->status[pos]==Active){
        pos=(pos+1)%h->size;
    }
    h->key[pos]=x;
    h->status[pos]=Active;
    h->remain--;
    return 1;
}
void printHT(const HT h){
    for(int i=0;i<h->size;i++){
        printf("%4d",i);
    }
    putchar('\n');
    for(int i=0;i<h->size;i++){
        if(h->status[i]==Active) printf("%4d",h->key[i]);
        else if(h->status[i]==Removed) printf("   x");
        else printf("   -");
    }
    putchar('\n');
}
int findX(int x,HT h){
    int pos,index;
    index=pos=hash(x,h->size);
    while(h->status[pos]!=Empty){
        if(h->key[pos]==x&&h->status[pos]==Active) return pos;
        pos=(pos+1)%h->size;
        if(pos==index) break;
    }
    return -1;
}
int removeX(int x,HT h){
    int pos=findX(x,h);
    if(pos==-1) return 0;
    h->status[pos]=Removed;
    h->remain++;
    return 1;
}
int main(){
    HT h=initHashTable(11);
    insertX(5,h);
    insertX(16,h);
    insertX(10,h);
    insertX(21,h);
    insertX(33,h);
    insertX(9,h);
    insertX(20,h);
    removeX(21,h);
    printHT(h);
    int i;
    i=findX(33,h);
    printf("%d",i);
    return 0;
}