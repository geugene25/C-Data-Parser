//“I Greg Eugene (2663504) afﬁrm that this program is entirely my own work and that I have neither
//developed my code together with any another person, nor copied any code from any other person,
//nor permitted my code to be copied or otherwise used by any other person, nor have I copied,
//modiﬁed, or otherwise used program code that I have found in any external source,
//including but not limited to, online sources. I acknowledge that any violation of the above
//terms will be treated as academic dishonesty.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airPdata.h"

void printData(airPdata *airport);

int main(int argc, char**argv)  {

  char *filename = argv[1];
  char *temp, buf[1024], *ptr;

  FILE *ifp;//Creates a pointer to a file //looks for an input to store in filename
  ifp = fopen(filename, "r");//opens file for reading

  if ((ifp = fopen(filename, "r")) == NULL)//checks to if the filename exists
    {
      fprintf(stderr, "\n etl ERROR: %s not found\n", filename);
    }
  else
    {
      printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s Tower\n",
      "FAA Site", "Short Name", "Airport Name", "City", "ST", "Latitude", "Longitude");
      printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s =====\n", "========", "==========",
      "============", "====", "==", "========", "=========");

    while(fgets(buf, 1024, ifp)!= NULL)//begins to read each line up to
      {
      ptr = malloc(sizeof(char)*2048);//allocates space for 150 chars
      strcpy(ptr, buf);

      airPdata *airport = malloc(sizeof(airPdata));//allocates
      airport->siteNumber = malloc(sizeof(char)*51);//allocates space for 51 chars
      airport->LocID = malloc(sizeof(char)*51);//allocates space for 51 chars
      airport->fieldName = malloc(sizeof(char)*51);//allocates space for 51 chars
      airport->city = malloc(sizeof(char)*51);//allocates space for 51 chars
      airport->state = malloc(sizeof(char)*51);//allocates space for 51 chars
      airport->latitude = malloc(sizeof(char)*51);//allocates space for 51 chars
      airport->longitude = malloc(sizeof(char)*51);//allocates space for 51 chars

      airport->siteNumber = strsep(&ptr, ",");//reads up to delim "," and returns pointer to specified member
      airport->LocID = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      airport->fieldName = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      airport->city = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      airport->state = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      temp = strsep(&ptr, ",");//used to parse unecessary fields
      temp = strsep(&ptr, ",");
      temp = strsep(&ptr, ",");
      airport->latitude = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      airport->longitude = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      temp = strsep(&ptr, ",");
      temp = strsep(&ptr, ",");
      temp = strsep(&ptr, ",");
      temp = strsep(&ptr, ",");
      temp = strsep(&ptr, ","); //reads from final field and stores in temp to be assigned to controlTower
      airport->controlTower = *temp; //assigns temp value to controlTower

      printData(airport); //calls 'printData' function
      free(airport);//free the struct pointer
      }
    fclose(ifp);
    }
   //closes file
return(0);
}
void printData(airPdata *airport) //passes a pointer to the function
{
  if(airport==NULL)//if no data is found
  {
    fprintf(stderr, "%s", "etl ERROR: File not found\n\n");
  }
  else
  {
  printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s %c\n",airport->siteNumber,airport->LocID,airport->fieldName,
          airport->city, airport->state, airport->latitude, airport->longitude, airport->controlTower);
  }
}
