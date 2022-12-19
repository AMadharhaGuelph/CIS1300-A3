/************************madharhaAnkushA2.c**************
Student Name: Ankush Madharha     Email Id: amadharh@uoguelph.ca
Due Date: November 25th           Course Name: CIS 1300

I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
1) I have read and understood the University policy on academic integrity. 
2) I have completed the Computing with Integrity Tutorial on Moodle; and 
3) I have achieved at least 80% in the Computing with Integrity Self Test.

I assert that this work is my own. I have appropriately acknowledged any and
all material that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for
this course.
********************************************************/

/********************************************************
Compiling the program
The program should be compiled using the following flags: -std=c99 -Wall

compiling:
gcc -std=c99 -Wall madharhaAnkushA3Main.c madharhaAnkushA3.c
Running: ./a.out
OR
gcc -std=c99 -Wall madharhaAnkushA3Main.c madharhaAnkushA3.c -o assn2
Running the Program: ./assn2
********************************************************/

#include "givenA3.h"

int main (int argc, char * argv[]) {

    // Declare variables
    int choice;
    int country[COUNTRIES][MEDALCAT];
    char countryNames[COUNTRIES][MAX_LENGTH_CNAME];
    int totalAllCountries[COUNTRIES];
    int totalAllMedals[MEDALCAT];
    int whichMedal;
    char countryName [MAX_LENGTH_CNAME];
    int indexMedal;
    int indexOfCountries[COUNTRIES];
    int minOrMax;

    // My Variables (separate from assignment)
    char tempMedalType[MAX_LENGTH_CNAME];
    int maxInTotalAllMedals;
    int amountOfMedals;
    int tempNumCountries;
    int minOrMaxIndex;
    
    
    // Call function readFromFile and findTotalPerCountry
    readFromFile(argv[1], country, countryNames);
    findTotalPerCountry(country, totalAllCountries);
   
    do {
        // Display Menu
        printf ("\nHere is the menu \n\n");
        printf ("1.    Display all country names read from file and the total number of medals won by each\n");
        printf ("2.    Function 2 - Find total number of medals won by each country\n");
        printf ("3.    Function 3 - Finds total number of medals in each category (Gold, Silver, Bronze)\n");
        printf ("4.    Function 4 – Display horizontal histogram\n");
        printf ("5.    Function 5 – Search for a country and return the total number of medals won by it\n");
        printf ("6.    Function 6 – Rank and display top three countries in order of total medals won\n");
        printf ("7.    Function 7 – Rank and display top three countries in order of total gold medals won\n");
        printf ("8.    Function 8 – Find and display all countries that won no X medals, given X as either Gold, Silver or Bronze\n");
        printf ("9.    Function 9 – Find and display all countries that won ONLY X medals, given X as either Gold, Silver or Bronze\n");
        printf ("10.   Function 10 – Find and display name of the country that has minimum or maximum length among all countries read in option 1\n");
        printf ("11.   Function 11 – Display vertical histogram\n");
        printf ("12.   Exit\n");
        printf ("Enter your choice: ");
        scanf ("%d", &choice);
        printf("\n");
        
        switch (choice) {
            case 1:
                // Cycle through country names
                for(int i = 0; i < COUNTRIES; i++) {
                    // Output country name
                    printf("Country: %s", countryNames[i]);

                    // Cycle through medal types
                    for(int j = 0; j < MEDALCAT; j++) {
                        // Store medal type depending on iteration
                        switch(j) {
                            case 0:
                                strcpy(tempMedalType, "Gold");
                                break;
                            case 1:
                                strcpy(tempMedalType, "Silver");
                                break;
                            case 2:
                                strcpy(tempMedalType, "Bronze");
                                break;
                        }
                        // Output medal type and amount of medals
                        printf(", %s = %d", tempMedalType, country[i][j]);
                    }
                    printf("\n");
                }
                break;
            case 2:
                // Cycle through the countries
                for(int i = 0; i < COUNTRIES; i++) {
                    // Output country name with total amount of medals
                    printf("Country %s = %d\n", countryNames[i], totalAllCountries[i]);
                }
                break;
            case 3:
                // Store the max value in totalAllMedals
                maxInTotalAllMedals = findTotalPerMedal(country, totalAllMedals, &whichMedal);

                // Cycle through medal types
                for(int i = 0; i < MEDALCAT; i++) {
                    // Store medal type depending on iteration
                    switch(i) {
                        case 0:
                            strcpy(tempMedalType, "Gold");
                            break;
                        case 1:
                            strcpy(tempMedalType, "Silver");
                            break;
                        case 2:
                            strcpy(tempMedalType, "Bronze");
                            break;
                    }
                    // Output medal type with total medals
                    printf("Medal = %s, Total = %d\n", tempMedalType, totalAllMedals[i]);
                }

                // Store medal type depending on whichMedal value
                switch(whichMedal) {
                    case 0:
                        strcpy(tempMedalType, "Gold");
                        break;
                    case 1:
                        strcpy(tempMedalType, "Silver");
                        break;
                    case 2:
                        strcpy(tempMedalType, "Bronze");
                        break;
                }
                // Output the maximum number of medals and it's category
                printf("Maximum number of medals = %d in category (%s)", maxInTotalAllMedals, tempMedalType);
                break;
            case 4:
                // Call hHistogram function
                hHistogram(countryNames, totalAllCountries);
                break;
            case 5:
                // Prompt user for country input
                printf("Searching for which country? ");
                scanf("%s", countryName);

                // Store the amount of medals a specified country has
                amountOfMedals = searchCountry(countryName, countryNames, totalAllCountries);

                // If specified country then output message
                if(amountOfMedals == -1) {
                    printf("Not Found\n");
                }
                // else output the countries medals
                else {
                    printf("Found it - %s has a total of %d medals\n", countryName, amountOfMedals);
                }
                break;
            case 6:
                // Call rankTopThreeByTotal function
                rankTopThreeByTotal(totalAllCountries, countryNames);
                break;
            case 7:
                // Call rankTopThreeByMedal function
                rankTopThreeByMedal(country, countryNames);
                break;
            case 8:
                // Prompt user for medal type
                printf("Which medal do you want to look for - Type 1 for Gold, 2 for Silver, 3 for Bronze? ");
                scanf("%d", &indexMedal);
                // Store the number of countries with no medal of specified type
                tempNumCountries = findAllWithNoXMedals(country, indexMedal, indexOfCountries);

                // Store the medal type the user inputted
                switch(indexMedal-1) {
                    case 0:
                        strcpy(tempMedalType, "Gold");
                        break;
                    case 1:
                        strcpy(tempMedalType, "Silver");
                        break;
                    case 2:
                        strcpy(tempMedalType, "Bronze");
                        break;
                }
                printf("Number of countries with no %s medals = %d\n", tempMedalType, tempNumCountries);
                // Output all the countries with no medal of the specified type
                for(int i = 0; i < tempNumCountries; i++) {
                    printf("%s\n", countryNames[indexOfCountries[i]]);
                }
                break;
            case 9:
                // Prompt user for 
                printf("Which medal do you want to look for - Type 1 for Gold, 2 for Silver, 3 for Bronze? ");
                scanf("%d", &indexMedal);
                tempNumCountries = findAllWithOnlyXMedals(country, indexMedal, indexOfCountries);
                // Store the specified medal type
                switch(indexMedal-1) {
                    case 0:
                        strcpy(tempMedalType, "Gold");
                        break;
                    case 1:
                        strcpy(tempMedalType, "Silver");
                        break;
                    case 2:
                        strcpy(tempMedalType, "Bronze");
                        break;
                }
                printf("Number of countries with ONLY %s medals = %d\n", tempMedalType, tempNumCountries);
                // Ouput the countries with ONLY the specified medal
                for(int i = 0; i < tempNumCountries; i++) {
                    printf("%s\n", countryNames[indexOfCountries[i]]);
                }
                break;
            case 10:
                // Prompt user for min or max
                printf("Do you want min (enter 1) or max (enter 2)? ");
                scanf("%d", &minOrMax);
                // Store the index in which the max or min word was found
                minOrMaxIndex = findCountryIndexWithMinOrMaxLength(minOrMax, countryNames);

                // Output the country with min or max length
                switch(minOrMax) {
                    case 1:
                        printf("The country name with minimum length = %s\n", countryNames[minOrMaxIndex]);
                        break;
                    case 2:
                        printf("The country name with maximum length = %s\n", countryNames[minOrMaxIndex]);
                        break;
                }
                break;
            case 11:
                // Call vHistogram function
                vHistogram(countryNames, totalAllCountries);
                break;
            case 12:
                printf("Ok Bye for now\n");
                break;
            default: printf ("That is an invalid choice\n");
                
        }
    } while (choice != 12);
    
   return 0;
}