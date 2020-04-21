#include <stdio.h>

int main(){

    double pi=0, temp=1, p=-1, num=1;
    while (num<1000000000)
    {
        p *=-1;
        pi += p*1.0/temp;
        temp +=2;
        num++;
    }
}