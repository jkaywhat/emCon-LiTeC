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
// This is one implementation for creating a custom struct variable type named "homework_t"
typedef struct _homework_t {
    float average;      // The struct has a "field" for each value listed
    float stdev;        // in the "Homework Gradebook" table.
    uint8_t min;        // Note that the fields can be all different types
    uint8_t max;
    uint16_t subs;
} homework_t;

// Prototype. Add above main function, below the homework_t definition.
float remove_min_from_avg(homework_t *homework);

// Declaration. Add below main function
// This function calculates the average of a homework without the minimum grade.
// The function will return the value of the new average.
float remove_min_from_avg(homework_t *homework){
    float homework_sum = homework->average*homework->subs;
    homework_sum -= homework->min;
    return homework_sum/(homework->subs-1);
}

// Add global variables here, as needed.
homework_t hw1;
homework_t hws[5];

int main(void) /* Main Function */
{
    // Add local variables here, as needed.
    hw1.average = 94.2;
    hw1.stdev = 10.8;
    hw1.min = 55;
    hw1.max = 100;
    hw1.subs = 109;
    hws[0].average = 94.2;
    hws[0].stdev = 10.8;
    hws[0].min = 55;
    hws[0].max = 100;
    hws[0].subs = 109;
    hws[1].average = 76.7;
    hws[1].stdev = 12.6;
    hws[1].min = 40;
    hws[1].max = 100;
    hws[1].subs = 106;
    hws[2].average = 84.5;
    hws[2].stdev = 15.9;
    hws[2].min = 25;
    hws[2].max = 100;
    hws[2].subs = 101;
    // We always call the "SysInit()" first to set up the microcontroller
    // for how we are going to use it.
    SysInit();

    // Place initialization code (or run-once) code here
    uint8_t i;
    for(i = 0; i < 3; i++){
        printf("Homework %u Stats\r\n"
               "    Average: %.2f\r\n"
               "  Std. Dev.: %.2f\r\n"
               "    Minimum: %u\r\n"
               "    Maximum: %u\r\n"
               "Submissions: %u\r\n",
               i+1, hws[i].average,hws[i].stdev,hws[i].min,
               hws[i].max,hws[i].subs);

    }
    printf("\nModified homework 1 average: %.2f",remove_min_from_avg(&hw1));
    printf("\nModified homework 2 average: %.2f",remove_min_from_avg(&hws[1]));
    while(1){
        // Place code that runs continuously in here

    }
}

// Add function declarations here as needed

// Add interrupt functions last so they are easy to find
