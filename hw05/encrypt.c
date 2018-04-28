#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed = clock(); //this will make your program run differently everytime
  //double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  printf("Enter a message to encrypt: ");
  int stat = scanf (" %[^\n]%*c", message); //reads in a full line from terminal, including spaces

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h;

  printf("Reading file.\n");

  /* Q2 Complete this function. Read in the public key data from public_key.txt,
    convert the string to elements of Z_p, encrypt them, and write the cyphertexts to 
    message.txt */

  // reads information from public_key
  FILE *fp = fopen("public_key.txt", "r");

  fscanf(fp,"%d %d %d %d", n, p, g, h);

  fclose(fp);

  // uses methods from functions.c
  unsigned int CPI = (n-1)/8;
  padString(message, CPI); // must be padded before the final length is determined
  
  unsigned int nInts = strlen(message)/CPI;
  unsigned int *numMes = (unsigned int *) malloc(nInts * sizeof(unsigned int));
  convertStringToZ(message, strlen(message), numMes, nInts);

  // now we have an unsigned int array that needs to be turned into the ciphertext pairs
	ElGamalEncrypt(message, numMes, nInts, strlen(message)); // encrypts

  FILE *ptr = fopen("message.txt", "w");
  fprintf(ptr, "%d", nInts); // how many ciphertext pairs there will be

  // for loop for each of the ciphertext pairs
  int x;
  for (x = 0; x < nInts; x++)
    {
        fprintf(ptr,"%d %d\n", numMes[x], a[x]); // prints it to file
    }

  fclose(ptr);
  
  return 0;
}
