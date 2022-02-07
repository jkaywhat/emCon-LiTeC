/**********************************************************************/
// ENGR-2350 Template Project
// Name: Kaylin Rackley
// RIN: 661810734
// This is the base project for several activities and labs throughout
// the course.  The outline provided below isn't necessarily *required*
// by a C program; however, this format is required within ENGR-2350
// to ease debugging/grading by the staff.
/**********************************************************************/

// We'll always add this include statement. This basically takes the
// code contained within the "engr_2350_msp432.h" file and adds it here.
#include "engr2350_msp432.h"

// Add function prototypes here, as needed.


// Add global variables here, as needed.
uint32_t array1[] = {1,2,3,4,5,6,7,8,9,10};
uint32_t array2[15];
uint32_t array3[10][10];
int main(void) /* Main Function */
{

    // Add local variables here, as needed.
    // We always call the "SysInit()" first to set up the microcontroller
    // for how we are going to use it.
    SysInit();

    // Place initialization code (or run-once) code here
    uint8_t i,j;
    // rand array value assignment
    for(i=0;i<15;i++){
        array2[i] = rand() % (20 + 1);
    }
    // multiplication table value assignment
    for(i=0;i<10;i++){  // Outer loop
        for(j=0;j<10;j++){  // Inner loop
            array3[i][j] = (i+1)*(j+1);
        }
    }
    // rand array value printing
    for(i=0;i<15;i++){ // Loop through the indices of the array
            printf("Element %u is:\t%u\r\n",i+1,array2[i]);
        }
    // multiplication table value printing
    printf("\n\n\t");
    for(i=0;i<10;i++){
        printf("\t%u",i+1); // horizontal column of factors
    }
    printf("\r\n");
    for(i=0;i<10;i++){
        printf("\t%u",i+1); // vertical column of factors
        for(j=0;j<10;j++){
            printf("\t%u",array3[i][j]); // products of factors
        }
        printf("\r\n");
    }
    while(1){
        // Place code that runs continuously in here

    }
}

// Add function declarations here as needed

// Add interrupt functions last so they are easy to find
