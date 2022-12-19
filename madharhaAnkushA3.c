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

void readFromFile(char fName[30], int country[COUNTRIES][MEDALCAT], char countryNames[COUNTRIES][MAX_LENGTH_CNAME]) {
    // Create a file and open it for reading
    FILE * inputFile;
    inputFile = fopen(fName, "r");

    char temp[MAX_LENGTH_CNAME];
    int i = 0;

    // Read the file until end
    while (!feof(inputFile))
    {
        // Store the whole line in current iteration
        fgets(temp, MAX_LENGTH_CNAME, inputFile);
        // Split up the stored line into specified variables
        sscanf(temp, "%s %d %d %d", countryNames[i], &country[i][0], &country[i][1], &country[i][2]);
        i++;
    }

    // Close file
    fclose(inputFile);
}

void findTotalPerCountry (int country[COUNTRIES][MEDALCAT], int totalAllCountries[COUNTRIES]) {
    // Cycle through countries 
    for (int i = 0; i < COUNTRIES; i++) {
        // Add all the medals the current country has and store it in totalAllCountries
        totalAllCountries[i] = country[i][0] + country[i][1] + country[i][2];
    }
}

int findTotalPerMedal (int country[COUNTRIES][MEDALCAT], int totalAllMedals[MEDALCAT], int *whichMedal) {
    int max;
    
    // Reset totalAllMedals values
    for(int i = 0; i < MEDALCAT; i++) {
        totalAllMedals[i] = 0;
    }

    // Fill totalAllMedals with total bronze, silver, and gold medals of all countries
    for(int i = 0; i < COUNTRIES; i++) {
        totalAllMedals[0] += country[i][0];
        totalAllMedals[1] += country[i][1];
        totalAllMedals[2] += country[i][2];
    }

    max = -1;
    // Store max value in totalAllMedals and store its index
    for(int i = 0; i < MEDALCAT; i++) {
        if(totalAllMedals[i] > max) {
            max = totalAllMedals[i];
            *whichMedal = i;
        }
    }

    // Return max in totalAllMedals
    return max;
}

void hHistogram (char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES]) {
    // Cycle through the countries
    for (int i = 0; i < COUNTRIES; i++) {
        // Output the country name
        printf("%-10s: ", countryNames[i]);

        // Output amount of medals the country has in stars
        for (int j = 0; j < totalMedals[i]; j++) {
            printf("*");
        }
        // Ouput amount of medals
        printf(" (%d)\n", totalMedals[i]);
    }
}

int searchCountry (char countryName [MAX_LENGTH_CNAME], char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalAllCountries [COUNTRIES]) {
    // Cycles through the countries
    for (int i = 0; i < COUNTRIES; i++) {
        // If specified country is found, return amount of medals the country has
        if (strcmp(countryName, countryNames[i]) == 0) {
            return totalAllCountries[i];
        }
    }
    // Return -1 if the country was not found
    return -1;
}

void rankTopThreeByTotal (int totalMedals[COUNTRIES], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]) {
    int temp[COUNTRIES];
    int indicies[MEDALCAT];
    int x;
    for(int i = 0; i < COUNTRIES; i++) {
        temp[i] = totalMedals[i];
    }

    for(int i = 0; i < COUNTRIES; i++) {
        for(int j = i + 1; j < COUNTRIES; j++) {
            if(temp[i] < temp[j]) {
                x = temp[i];
                temp[i] = temp[j];
                temp[j] = x;
            }
        }
    }

   
    for(int j = 0; j < COUNTRIES; j++) {
        if(temp[0] == totalMedals[j]) {
            printf("%s (%d)", countryNames[j], totalMedals[j]);
            indicies[0] = j;
            for(int l = 0; l < COUNTRIES; l++) {
                if(temp[1] == totalMedals[l] && l != indicies[0]) {
                    printf("%s (%d)", countryNames[l], totalMedals[l]);
                    indicies[1] = l;
                    for(int i = 0; i < COUNTRIES; i++) {
                        if(temp[2] == totalMedals[i] && i != indicies[0] && i != indicies[1]) {
                            printf("%s (%d)", countryNames[i], totalMedals[i]);
                        }
                        break;
                    }
                }
                break;
            }
        }
        break;
    }
    
    

}

void rankTopThreeByMedal (int country [COUNTRIES] [MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]) {
    int firstGold = 0, secondGold = 0, thirdGold = 0, index = 0;

    printf("Rank top three Based on Gold medals\n");

    // Find the first max gold medal and store its index
    for (int i = 0; i < COUNTRIES; i++) {
        if (country[i][0] > firstGold) {
            firstGold = country[i][0];
            index = i;
        }
    }
    // Output the first max gold medals
    printf("%s (%d)\n", countryNames[index], firstGold);
    index = 0;

    //Find the second max gold medal and store its index
    for (int i = 0; i < COUNTRIES; i++) {
        if (country[i][0] > secondGold && country[i][0] != firstGold) {
            secondGold = country[i][0];
            index = i;
        }
    }
    // Output the second max gold medals
    printf("%s (%d)\n", countryNames[index], secondGold);
    index = 0;

    //Find the third max gold medal and store its index
    for (int i = 0; i < COUNTRIES; i++) {
        if (country[i][0] > thirdGold && country[i][0] != firstGold && country[i][0] != secondGold) {
            thirdGold = country[i][0];
            index = i;
        }
    }
    // Output the third max gold medals
    printf("%s (%d)\n", countryNames[index], thirdGold);
}

int findAllWithNoXMedals(int country[COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries[COUNTRIES])
{
    int index = 0;
    // Cycle through the countries
    for (int i = 0; i < COUNTRIES; i++) {
        // If a country is found with no medal of specified type, store its index and increment index variable
        if (country[i][indexMedal - 1] == 0) {
            indexOfCountries[index] = i;
            index++;
        }
    }
    // Return index, the amount of countries with no medal of specified type
    return index;
}

int findAllWithOnlyXMedals(int country[COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries[COUNTRIES])
{
    int index = 0, i, i2;
    // Depending on specified medal, determine the indicies in which we are looking for no medals
    switch (indexMedal) {
    case 1:
        i = 1;
        i2 = 2;
        break;
    case 2:
        i = 0;
        i2 = 2;
        break;
    case 3:
        i = 0;
        i2 = 1;
        break;
    }
    // Cycle through the countries
    for (int j = 0; j < COUNTRIES; j++) {
        // If a country is found with medals of the specified type and NO medals in the other types
        // then store its index and increment index
        if (country[j][indexMedal-1] > 0 && country[j][i] == 0 && country[j][i2] == 0) {
            indexOfCountries[index] = j;
            index++;
        }
    }
    // Return index, the amount of countries with ONLY medals of the specified type
    return index;
}

int findCountryIndexWithMinOrMaxLength(int minOrMax, char countryNames[COUNTRIES][MAX_LENGTH_CNAME])
{
    int length = strlen(countryNames[0]);
    int index = 0;
    // Run for loop depending on looking for min or max
    switch (minOrMax) {
        case 1:
            // Cycle through countries
            for (int i = 0; i < COUNTRIES; i++) {
                // If a length is found that is shorter than the current min, update min length and store its index
                if (strlen(countryNames[i]) < length) {
                    length = strlen(countryNames[i]);
                    index = i;
                }
            }
            break;
        case 2:
            // Cycle through countries
            for (int i = 0; i < COUNTRIES; i++) {
                // If a length is found that is bigger than the current max, update max length and store its index
                if (strlen(countryNames[i]) > length) {
                    length = strlen(countryNames[i]);
                    index = i;
                }
            }
            break;
    }
    // return index, the index in which the min or max country was found
    return index;
}

void vHistogram (char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES]) {
    // Find largest country length for padding purposes
    int indexOfLargestCountry = findCountryIndexWithMinOrMaxLength(2, countryNames);
    int totalWidth = strlen(countryNames[indexOfLargestCountry]);
    // If the largest country length is even, make it odd for centering purposes
    if(totalWidth % 2 == 0) {
        totalWidth += 1;
    }
    // Calculate padding, declare variables
    int padding = totalWidth/2;
    int max = totalMedals[0];
    char temp[MAX_LENGTH_CNAME];

    // Cycle through the countries
    for(int i = 0; i < COUNTRIES; i++) {
        // If totalMedals is two digits then print the number with one less padding on the left
        if(totalMedals[i]/10 >= 1) {
            printf("%*s%d%*s", padding-1, "", totalMedals[i], padding, "");
        }
        // else print with normal padding (one digit number)
        else {
            printf("%*s%d%*s", padding, "", totalMedals[i], padding, "");
        }
        // Store max in totalMedals
        if(totalMedals[i] > max) {
            max = totalMedals[i];
        }
    }
    printf("\n");

    // Creating hitogram
    // Going from max - 0 in order to determine if outputting "*" or " "
    for(int i = max; i > 0; i--) {
        for(int j = 0; j < COUNTRIES; j++) {
            // If the current countries medals is less than i output " "
            if(totalMedals[j] < i) {
                printf("%*s%s%*s", padding, "", " ", padding, "");
            }
            // else output "*"
            else {
                printf("%*s%s%*s", padding, "", "*", padding, "");
            }
        }
        printf("\n");
    }

    for(int i = 0; i < COUNTRIES; i++) {
        // Store currnet country in a temp variable
        strcpy(temp, countryNames[i]);
        // If the current country stored in temp is even length, make it odd for centering purposes
        if(strlen(temp) % 2 == 0) {
            strcat(temp, " ");
        }
        // Calculate padding depending on current country length, output country name
        padding = (totalWidth - strlen(temp))/2;
        printf("%*s%s%*s", padding, "", temp, padding, "");
    }
}