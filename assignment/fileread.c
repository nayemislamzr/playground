#include <stdio.h>

int main()
{
    int oc1,oc2,oc3,oc4, cidr, i, c1,c2,c3,c4;
    scanf("%d.%d.%d.%d/%d",&oc1,&oc2,&oc3,&oc4,&cidr);

    for(i=7 ; i>-1 ; i--)
        printf("%d", (oc1 & (1 << i))!= 0 );
    printf(" ");

    for(i=7 ; i>-1 ; i--)
        printf("%d", (oc2 & (1 << i))!= 0 );
    printf(" ");

    for(i=7 ; i>-1 ; i--)
        printf("%d", (oc3 & (1 << i))!= 0 );
    printf(" ");

    for(i=7 ; i>-1 ; i--)
        printf("%d", (oc4 & (1 << i))!= 0 );
    printf(" \n");

    c1=c2=c3=c4=0;

    for( i=7 ; i>-1 ; i-- ){
        if(cidr>0)
            c1 |= (1 << i);
        cidr--;
    }
    for( i=7 ; i>-1 ; i-- ){
        if(cidr>0)
            c2 |= (1 << i);
        cidr--;
    }
    for( i=7 ; i>-1 ; i-- ){
        if(cidr>0)
            c3 |= (1 << i);
        cidr--;
    }
    for( i=7 ; i>-1 ; i-- ){
        if(cidr>0)
            c4 |= (1 << i);
        cidr--;
    }
    

    printf("%d.%d.%d.%d\n",c1,c2,c3,c4);


    return 0;
}