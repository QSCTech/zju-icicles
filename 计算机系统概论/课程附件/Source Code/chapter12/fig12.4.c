#include <stdio.h>

int main()
{
  int amount;   /* The number of bytes to be transferred  */
  int rate;     /* The average network transfer rate      */
  int time;     /* The time, in seconds, for the transfer */
		
  int hours;    /* The number of hours for the transfer   */
  int minutes;  /* The number of mins for the transfer    */
  int seconds;  /* The number of secs for the transfer    */

  /* Get input: number of bytes and network transfer rate */
  printf("How many bytes of data to be transferred?  ");
  scanf("%d", &amount);
   
  printf("What is the transfer rate (in bytes/sec)?  ");
  scanf("%d", &rate);

  /* Calculate total time in seconds                      */
  time = amount / rate;

  /* Convert time into hours, minutes, seconds            */
  hours = time / 3600;         /* 3600 seconds in an hour */
  minutes = (time % 3600) / 60; /* 60 seconds in a minute */
  seconds = ((time % 3600) % 60); /* remainder is seconds */
        
  /* Output results */
  printf("Transfer Time : %dh %dm %ds\n", hours, minutes, seconds);
}
