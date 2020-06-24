#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
int main( void)
{
time_t curtime;
struct tm *tmbuf;
if (time(&curtime) < 0) {
perror("time error");
exit(1);
}

printf ("Next is result of gmtime()\n\n");
tmbuf = (struct tm *) gmtime(&curtime);
printf ("Year : %4d \n", tmbuf->tm_year + 1900);
printf ("Month : %4d \n", tmbuf->tm_mon + 1);
printf ("Day : %4d \n", tmbuf->tm_mday);
printf ("Hour : %4d \n", tmbuf->tm_hour);
printf ("Min : %4d \n", tmbuf->tm_min);
printf ("Sec : %4d \n", tmbuf->tm_sec);
if (tmbuf->tm_isdst > 0)
printf ("Summer time is applied. \n");
if (tmbuf->tm_isdst == 0)
printf ("Summer time is not applied. \n");
if (tmbuf->tm_isdst < 0)
printf ("there is no information on summer time. \n");

printf ("Next is result of localtime() \n\n");
tmbuf = ( struct tm *) localtime(&curtime);
printf ("Year : %4d \n", tmbuf->tm_year + 1900);
printf ("Month : %4d \n", tmbuf->tm_mon + 1);
printf ("Day : %4d \n", tmbuf->tm_mday);
printf ("Hour : %4d \n", tmbuf->tm_hour);
printf ("Min : %4d \n", tmbuf->tm_min);
printf ("Sec : %4d \n", tmbuf->tm_sec);
if (tmbuf->tm_isdst > 0)
printf ("Summer time is applied. \n");
if (tmbuf->tm_isdst == 0)
printf ("Summer time is not applied. \n");
if (tmbuf->tm_isdst < 0)
printf ("there is no information on summer time \n");
}