/*  Andrew Borgan, Monday September 26th 2016
 *  aborgan@mail.uoguelph.ca
 *
 *  See carbon.h (assignment1/docs folder) for details on overall function usage
 */

#include <stdio.h>

void carbon()
{
    char carbon [6] = "carbon";
    int count = 0; //used to track how many permutations of carbon are printed

    for (int i = 0; i < 6; i+=1) //6 for loops, one for each position in "carbon" ("r" would be position 3) to iterate each space through all 6 letters
    {
        for (int j = 0; j < 6; j+=1)
        {
            while (j == i) //Each while loop is a check to ensure that multiple instances of a letter can't occur ("CCRBON" is not allowed because it contains 2 C)
            {
                j+=1;
            }
            for (int k = 0; k < 6; k+=1)
            {
                while (k == j || k == i) //another while loop checking previous two positions for no instances of same letter.  Same idea for other while loops
                {
                    k+=1;
                }
                for (int l = 0; l < 6; l+=1)
                {
                    while (l == j || l == i || l == k)
                    {
                        l+=1;
                    }
                    for(int m = 0; m < 6; m+=1)
                    {
                        while (m == j || m == k || m == l || m == i)
                        {
                            m+=1;
                        }
                        for (int n = 0; n < 6; n+=1)
                        {
                            while (n == i || n == j || n == k || n == l || n == m)
                            {
                            	n+=1;
                            }
                            if (i < 6 && j < 6 && k < 6 && l < 6 && m < 6 && n < 6) //catch for if for loop variables are pushed too far (>5).  Only prints if all variables are within appropriate range (appropriate output)
                            {
                                count+=1; //found a valid output
                                printf("%d %c%c%c%c%c%c\n", count, carbon[i], carbon[j], carbon[k], carbon[l], carbon[m], carbon[n]); //prints permutation
                            }
                        }
                    }
                }
            }
        }
    }
}
