//Jhad Katerji
//CS520 Lab2
//9/05/2018

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    
//Variable Declarations
int endian;
int bomCheck1;
int bomCheck2;
int primeRead1;
int primeRead2;
int primeRead3;
int primeRead4;
int val;
int newVal;
int lead;
int trail;
int leader;
int trailer;
int temp;
int temp1;
int temp2;
int addingZero;
//    int counterVariable;
    int temper;
    
FILE * checkFile;
FILE * outFile;
    temp1 = 0;
    temp2 = 0;
    temper = 0;
    temp1++;
    temp2++;
    temper++;

    
//Check to make sure there are the right amount of arguments
if (argc != 3){
  printf("INCORRECT ARGUMENTS");
  exit (-1);
}

//We are opening the file, and checking to see if it can be read.
checkFile = fopen (argv[1], "r");
outFile = fopen (argv[2], "w");
    
addingZero = 0x00;

    
if (checkFile == NULL) {
  printf (" cannot open %s\n", argv[1]);
  exit (-1);
}
//Check the BOM, decide if it's little Endian or big Endian or neither.
bomCheck1 = getc(checkFile);
bomCheck2 = getc(checkFile);
    
    if (bomCheck1 == 0xfe && bomCheck2 == 0xff){
    endian = 1;
putc (addingZero, outFile);
putc (addingZero, outFile);
putc (bomCheck1, outFile);
putc (bomCheck2, outFile);
    //printf("Big Endian");
    }
    
    else if (bomCheck1 == 0xff && bomCheck2 == 0xfe){
    endian = 0;
        putc (bomCheck1, outFile);
        putc (bomCheck2, outFile);
        putc (addingZero, outFile);
        putc (addingZero, outFile);
    //printf("Little Endian");
    }
    
    else{
    printf("File is NOT VALID");
    exit (-1);
	}

    
    
//BIG ENDIAN OUTSIDE OF PLANE 0
if (endian==1){
    
    primeRead1 = getc(checkFile);
//    printf ("Leading surrogate 1: %d\n", primeRead1);
    
    while (primeRead1 != EOF){  
        primeRead2 = getc(checkFile);
 //       printf ("Leading surrogate 2: %d\n", primeRead2);
        leader = ( (primeRead1 <<8) | (primeRead2) );
//        printf ("Total Leading Surrogate: %d\n", leader);
        
        if (leader>=0xd800 && leader<=0xdbff)
        {
            primeRead3 = getc(checkFile);
            primeRead4 = getc(checkFile);
            trailer = ( (primeRead3 <<8) | (primeRead4) );
 //           printf ("Total Trailing Surrogate: %d\n", trailer);
            
            if (trailer >= 0xdc00 && trailer <= 0xdfff)
            {
                lead = (leader - 0xd800);
 //               printf ("Leader before 10000: %d\n", lead);
                trail = (trailer - 0xdc00);
 //               printf ("trailer before 10000: %d\n", trail);
                val = ( (lead <<10) | (trail) );
//                printf ("the two combined with eachother: %d\n", val);
                newVal = (val + 0x10000) ;
 //               printf ("Final Value %d\n", newVal);
        
putc (newVal>>24, outFile);
putc (newVal>>16, outFile);
putc (newVal>>8, outFile);
putc (newVal, outFile);               
            }
        primeRead1 = getc(checkFile);
    }
       else{


    
    //Making sure that the output matches the Endianess of the input
    if (endian == 1){
        temp= primeRead1;
        primeRead1=primeRead2;
        primeRead2=temp;
val = ((primeRead2<<8)|primeRead1);
putc (val>>24, outFile);
putc (val>>16, outFile);
putc (val>>8, outFile);
putc (val, outFile);
    }
           fclose (outFile);
outFile = fopen (argv[2], "r");
           temper = getc(outFile);
           temper = getc(outFile);
           temper = getc(outFile);
           temper = getc(outFile);
           fclose (outFile);

       } 
    }
    }


    //////////// LITTLE ENDIAN OUTSIDE OF PLANE 0
    if (endian ==0){
        primeRead1 = getc(checkFile);
//    printf ("Leading surrogate 1: %d\n", primeRead1);
        int temp1 = primeRead1;
    
    while (primeRead1 != EOF){  
        primeRead2 = getc(checkFile);
        primeRead1 = primeRead2;
        primeRead2 = temp1;
//       printf ("Leading surrogate 2: %d\n", primeRead2);
        leader = ( (primeRead1 <<8) | (primeRead2) );
//        printf ("Total Leading Surrogate: %d\n", leader);
        
        if (leader>=0xd800 && leader<=0xdbff)
        {
            primeRead3 = getc(checkFile);
            primeRead4 = getc(checkFile);
            int temp2 = primeRead3;
            primeRead3 = primeRead4;
            primeRead4 = temp2;
            trailer = ( (primeRead3 <<8) | (primeRead4) );
//            printf ("Total Trailing Surrogate: %d\n", trailer);
            
            if (trailer >= 0xdc00 && trailer <= 0xdfff)
            {
                lead = (leader - 0xd800);
//                printf ("Leader before 10000: %d\n", lead);
                trail = (trailer - 0xdc00);
//                printf ("trailer before 10000: %d\n", trail);
                val = ( (lead <<10) | (trail) );
//                printf ("the two combined with eachother: %d\n", val);
                newVal = (val + 0x10000) ;
//                printf ("Final Value %d\n", newVal);
        
putc (newVal, outFile);
putc (newVal>>8, outFile);
putc (newVal>>16, outFile);
putc (newVal>>24, outFile);               
            }
        primeRead1 = getc(checkFile);
    }
       else{
if (endian ==0){
val = ((primeRead2<<8)|primeRead1);
putc (val>>8, outFile);
putc (val, outFile);

putc (val>>16, outFile);
putc (val>>24, outFile);
}
fclose (outFile);
outFile = fopen (argv[2], "r");
           temper = getc(outFile);
           temper = getc(outFile);
           temper = getc(outFile);
           temper = getc(outFile);
           fclose (outFile);
        

       } 
    }
    }
    

    fclose (outFile);
    fclose (checkFile);


return 0;
 }
