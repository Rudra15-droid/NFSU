#include<stdio.h>
void main(){
    int sum=0;
    for(int i=101;i<200;i++){
        if(i%5==0){
            sum+=i;
        }
    }
    printf("The required sum is %d",sum);
}