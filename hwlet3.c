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

typedef struct lListAirPdata
{
  airPdata *airportPtr;
  struct lListAirPdata *nextAirport;
}lListAirPdata;

void parseLine(char *line, airPdata *apd);
void deleteStruct(airPdata *apd);
float sexag2decimal(char *degreeString);
void sortLocID(lListAirPdata *airports, int length);
void sortLatitude(lListAirPdata *airports, int length);
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
      airport->latitude = sexag2decimal(ptr);
      airport->longitude = sexag2decimal(ptr);

      lListAirPdata *newairport = malloc(sizeof(lListAirPdata));
      newairport->LocID = malloc(sizeof(char)*51);
      newairport->fieldName = malloc(sizeof(char)*51);
      newairport->city = malloc(sizeof(char)*51);


      airport->siteNumber = strsep(&ptr, ",");//reads up to delim "," and returns pointer to specified member
      airport->LocID = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      strcpy(newairport->LocID, airport->LocID)  ;
      airport->fieldName = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      strcpy(newairport->fieldName, airport->fieldName);
      airport->city = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      strcpy(newairport->city, airport->city)
      airport->state = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      temp = strsep(&ptr, ",");//used to parse unecessary fields
      temp = strsep(&ptr, ",");
      temp = strsep(&ptr, ",");
      airport->latitude = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      strcpy(newairport->latitude, airport->latitude);
      airport->longitude = strsep(&ptr, ",");//reads up to delim "," and returns pointer
      strcpy(newairport->longitude, airport->longitude);
      temp = strsep(&ptr, ",");
      temp = strsep(&ptr, ",");
      temp = strsep(&ptr, ",");
      temp = strsep(&ptr, ",");
      temp = strsep(&ptr, ","); //reads from final field and stores in temp to be assigned to controlTower
      airport->controlTower = *temp; //assigns temp value to controlTower

      printData(newairport); //calls 'printData' function
      free(airport);//free the struct pointer
      free(newairport);
      }
    fclose(ifp);
    }
   //closes file
return(0);
}

float sexag2decimal(char *degreeString)
{

    char *tok;
    char *tmpInBuffer = degreeString;
    float degrees, minutes, seconds;
    float degreeDecimal;

    if (degreeString == NULL)
    {
        return 0.0;
    }

    tok = strsep(&tmpInBuffer, "-");
    degrees = atof(tok);
    tok = strsep(&tmpInBuffer, "-");
    minutes = atof(tok);
    tok = strsep(&tmpInBuffer, "NESW");
    seconds = atof(tok);

    if (degrees > 99.00 || degrees < 0.00 || minutes > 59.00 || minutes < 0.00 || seconds > 59.9999 || seconds < 0.00)
        return 0.0;


    if (degreeString[0] == '0')
    {
        degreeDecimal = (-degrees) - (minutes/60.00) - (seconds/3600.00);
    }
    else
    {
        degreeDecimal = degrees + (minutes/60.00) + (seconds/3600.00);
    }

    return degreeDecimal;

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
