#include <stdio.h>


int swap(int x, int y){
    printf("x is %d \n",x);
    printf("y is %d \n",y);
    
    int temp = x;
    x = y;
    y = temp;
    printf("After Swapping: x = %d, y = %d", x, y);
    return 0;
}
int main(){
    swap(6,5);
}
