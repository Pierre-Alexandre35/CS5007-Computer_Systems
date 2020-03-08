#include <stdio.h>
#include<string.h>

int main() {
    int i; 
    FILE * fPointer;

    fPointer = fopen("barebones.s", "r");
    char singleLine[150];

    int addCount = 0;
    int addLatency = 0;
    
    int subCount = 0;
    int subLatency = 0;

    int mulCount = 0;
    int mulLatency = 0;

    int divCount = 0;
    int divLatency = 0;

    int movCount = 0;
    int movLatency = 0;
    
    int leaCount = 0;
    int leaLatency = 0;

    int pushCount = 0;
    int pushLatency = 0;

    int popCount = 0;
    int popLatency = 0;

    int retCount = 0;
    int retLatency = 0;

    int totalInstructions = 0;
    int totalCycles = 0;
    
    while(!feof(fPointer)){
        fgets(singleLine, 150, fPointer);
            if(strstr(singleLine, "ADD")){
                addCount++;
                addLatency ++;
            }
            if(strstr(singleLine, "sub")){
                subCount++;
                subLatency = subLatency + 3;

            }
            if(strstr(singleLine, "mul")){
                mulCount++;
                mulLatency = mulLatency + 3;

            }
            if(strstr(singleLine, "div")){
                divCount++;
                divLatency = divLatency + 27;

            }
            if(strstr(singleLine, "mov")){
                movCount++;
                movLatency = movLatency + 4;
            }
            if(strstr(singleLine, "lea")){
                leaCount++;
                leaLatency ++;

            }
            if(strstr(singleLine, "push")){
                pushCount++;
                pushLatency ++;

            }
            if(strstr(singleLine, "pop")){
                popCount++;
                popLatency++;
            }
            if(strstr(singleLine, "ret")){
                retCount++;
            }
        }
    
    totalInstructions = addCount + subCount + mulCount + divCount + movCount + leaCount + pushCount + popCount + retCount;
    
    totalCycles = addLatency + subLatency + mulLatency + divLatency + movLatency + leaLatency + pushLatency + popLatency + retLatency;
    fclose(fPointer);
    
    printf("add count %d\n",addCount);
    printf("sub count %d\n",subCount);
    printf("mul count %d\n",mulCount);
    printf("div count %d\n",divCount);
    printf("mov count %d\n",movCount);
    printf("lea count %d\n",leaCount);
    printf("push count %d\n",pushCount);
    printf("pop count %d\n",popCount);
    printf("ret count %d\n",retCount);
    printf("total instruc count %d\n",totalInstructions);
    printf("total cycles %d\n",totalCycles);
    return 0;

}
