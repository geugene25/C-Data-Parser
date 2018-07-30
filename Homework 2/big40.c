//“I Greg Eugene afﬁrm that this program is entirely my own work and that I have neither
//developed my code together with any another person, nor copied any code from any other person,
//nor permitted my code to be copied or otherwise used by any other person, nor have I copied,
//modiﬁed, or otherwise used program code that I have found in any external source,
//including but not limited to, online sources. I acknowledge that any violation of the above
//terms will be treated as academic dishonesty.

#include "big40.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

Integer40 *big40Add(Integer40 *p, Integer40 *q)
{

    int i, k = 0;

    if(p == NULL || q == NULL)
        return NULL;

    Integer40 *sum = malloc(sizeof(Integer40)*MAX40); //creates pointer for sum
    sum->digits = calloc(MAX40, sizeof(int)); //initialized space with in sum digits

    if(sum == NULL) //checks to see if it can create sum Struct
        return NULL;//returns NULL

    for(i = 0; i < MAX40; i++)
    {
        k = p->digits[i]+q->digits[i]; //adds the digits of the struct pointer p and q
        if(k <= 15) //as long as the value of the q+p(digits) <= 15
        {
            sum->digits[i] = k; //sum digits of the relative [i] = p + q

        }
        else
        {
            while( k > 9 && i < MAX40) //if it is greater the 9
            {
                sum->digits[i] = k % 16;//we do mod 16 to set sum[i]
                i++; //increment position

                if(i < MAX40)
                {
                    k = p->digits[i]+q->digits[i]+1; //returns the carry
                    if(k < 9)
                    {
                        sum->digits[i] = k;
                        i++;
                    }
                }
            }
        }
    }
    return(sum);
};

Integer40 *big40Destroyer(Integer40 *p) //frees the allocated space of struct p
{
    free (p);
    return(NULL);
};

int convertValue(char x) //checks to see where the ascii value falls based on the result returns decimal value
{
    if((x >= 48) && (x <= 57))
    {
        x = x - 48;
    }
    else if((x >= 65) && (x <= 78))
    {
        x = x - 55;
    }
    else if((x >= 97) && (x <= 102))
    {
        x = x - 87;
    }


    return(x);
}

Integer40 *parseString(char *str)
{
    int j = 0;
    int parse_length;
    Integer40 *parse = malloc(sizeof(Integer40)*MAX40 + 1); //mallocs space for struct with one extra position

    if(str == NULL)
    {
        return NULL;
    }
    else if(parse == NULL)
    {
        fprintf(stderr, "ERROR: parseString failed to allocate memory.\n"); //if the parsing does not work then print message
        return (NULL);
    }

    parse_length = strlen(str); //sets the length to the length of the pointer

    parse->digits = calloc(MAX40, sizeof(int)); //creates space for digits member

    if(parse_length > MAX40)
    {
        int stp = 39;
        for (j = 0; j < MAX40; j++)
        {
            parse->digits[j] = convertValue(str[stp--]); //because of the orientation of the array we input from the opposite end of array
        }
    }
    else if(parse_length == MAX40)
    {
        for(j = 0; j < MAX40; j++)
        {
            parse->digits[j] = convertValue(str[39 - j]); //prints from opposite end up to 40
        }
    }
    else if(parse_length < MAX40)
    {
        for(j = 0; j < MAX40; j++)
        {
            parse->digits[j] = convertValue(str[parse_length - 1 - j]); //if less than 40 we need to set the posion that were printing from to the length of string decremented by 1 and position output
            if(parse_length - 1 - j <= 0)
                break;
        }
        //fprintf(stderr, "This number is under 40 digits!\n");
    }
    return(parse);
};





Integer40 *loadHWConfigVariable(int doSeed)
{
    Integer40 *temp = malloc(sizeof(Integer40)*MAX40);
    temp->digits = (int *)malloc(sizeof(int) * 40);
    int i, j, randValue;

    if (doSeed == 0){
        int randValue = 0;
        int tmpArr[5];
        srand(time(NULL));

        for(i = 0; i < 5; i++) //creates 5 random values
        {
            randValue = rand()%10;
            tmpArr[i] = randValue; //puts random generation in tempArr
        }

        for(j = 0; j<MAX40; j++)
        {
            temp->digits[j] = tmpArr[j%5]; //repeats length 8 times
        }
    }
    else if(doSeed == 1)
    {
        for(i = 0 ; i<MAX40 ; i++)
            randValue = rand()%16;
    }
    return temp;
};

Integer40 *loadCryptoVariable(char *inputString)
{
    Integer40 *CrypVal = malloc(sizeof(Integer40)); //creates a struct pointer for string
    CrypVal->digits = calloc(MAX40, sizeof(int)); //creates space in CrypVal->digits
    char buff[1024]; //buffer will be used to hold read string
    if(CrypVal == NULL){
        return NULL;
    }

    FILE *ifp = fopen(inputString, "r"); //pointer set to open file name on inputeString

    if(fopen(inputString, "r") == NULL) //if not possible return NULL
    {
        printf("The file 'cryptoVarFile' could not be found\n"); //if it fails then print message
    }
    else{
        fgets(buff, 256, ifp); //reads content and puts in buff
        CrypVal = parseString(buff); //sets struct to returned val of parseString
        fclose(ifp); //closes file on pointer ifp
    }
    return (CrypVal);
};

void big40Rating(void)
{
  fprintf(stderr, "\n2663504, 5, 170+\n\n"); //NID, Difficulty, Hours
};


Integer40 *fibBig40(int n, Integer40 *first, Integer40 *second)
{

    Integer40 *Fcryp = malloc(sizeof(Integer40)); //creates a struct to pass the first parameter
    Integer40 *Fload = malloc(sizeof(Integer40)); //creates a struct to pass the second parameter
    Integer40 *fibOut = malloc(sizeof(Integer40)); //creates a struct for the out put of the addition
    Fcryp->digits = first->digits; //sets this created struct to the value of first
    Fload->digits = second->digits;//sets this created struct to the value of second

    int i = 0;

    for (i = 0; i < n - 2; i++)
    {
        fibOut = big40Add(Fcryp, Fload); //sums the value and set output
        Fcryp = Fload; //f[0] = f[1]
        Fload = fibOut; //f[1]=fibOut
    }
    return fibOut;
}
