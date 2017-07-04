#include <stdio.h>
#include <time.h>

#include "temps.h"


/* http://linux.die.net/man/3/ctime */

struct template { /*les valeurs de la structure TM*/
    int tm_sec;         /* seconds */
    int tm_min;         /* minutes */
    int tm_hour;        /* hours */
    int tm_mday;        /* day of the month */
    int tm_mon;         /* month (0 pour janvier)*/
    int tm_year;        /* year */
    int tm_wday;        /* day of the week (0 dim, 5 ven)*/
    int tm_yday;        /* day in the year */
    int tm_isdst;       /* daylight saving time */
};

// int main ()
// {
//   time_t rawtime;
//   struct tm * timeinfo;
//
//   time ( &rawtime );
//   timeinfo = localtime ( &rawtime );
//   //printf ( "Current local time and date: %s", asctime (timeinfo) );
//
//   printf("Jour du mois : %d\n", getTime('D'));
//
//   return 0;
// }


int getTime(const char c)
{
  // D : jour du mois (1-31)
  // M : mois (1-12)
  // Y : annee (2015)
  // d : jour de la semaine (0 dimanche, 6 samedi)
  //
  // h : Heure
  // m : minutes
  // s : secondes

  time_t rawtime;
  struct tm * timeinfo;

  time( &rawtime);
  timeinfo = localtime (&rawtime);

  switch(c) /*on analyse l'entree*/
  {
    case 'D': /*si l'on envoie le jour (d)*/
      return timeinfo->tm_mday;
    break;

    case 'M':
      return timeinfo->tm_mon;
    break;

    case 'Y':
      return timeinfo->tm_year +1900;
    break;

    case 'd':
      return timeinfo->tm_wday;
    break;

    case 'h':
      return timeinfo->tm_hour;
    break;

    case 'm':
      return timeinfo->tm_min;
    break;

    case 's':
      return timeinfo->tm_sec;
    break;

    default:
      printf("\nCaractere non conforme; verifier si bien D M Y d h m s\n");
  }
}
