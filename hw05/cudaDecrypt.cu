#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"

__global__ void find(unsigned int p, unsigned int g, unsigned int h, unsigned int x)
{
unsigned int threadID = threadId.x;
unsigned int blockID = blockID.x;
unsigned int nBlocks = blockDim.x;
unsigned int curr = threadID + nBlocks*blockID;

if (modExp(g, curr, p) == h)
{
x = curr;
}

}

int main (int argc, char **argv) {

  /* Q4 Make the search for the secret key parallel on the GPU using CUDA. */

//declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */
  FILE *pk = fopen("public_key.txt", "r");
  FILE *mes = fopen("public_key.txt", "r");

  fscanf(pk, "%d %d %d %d", n, p, g, h);
  fscanf(mes, "%d", Nints);

// where the secret key will be stored when it's found
unsigned int *sk;
cudaMalloc(%sk, sizeof(unsigned int));

// how the find method will iterate through
int Nthreads = 32; 
int Nblocks = (p + Nthreads - 2)/Nthreads;

  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();
   find<<<Nthreads, Nblocks>>>(p, g, h, sk);
   cudaMemcpy(x, sk, sizeof(unsigned int), cudaMemcpyDeviceToHost);
cudaDeviceSynchronize();
    double endTime = clock();
    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }
cudaFree(sk);

  /* Q3 After finding the secret key, decrypt the message */
  int y;
  unsigned char *foundMes = (unsigned char *) malloc(Nints * sizeof(unsigned char)); // will contain the message once it is decrypted
  unsigned int c1, c2; // will select each ciphertext pair
  
  for (y = 0; y < Nints; y++)
    {
      fscanf(mes, "%d %d", c1, c2);
      foundMes[y] = ( pow(c1, p-2) * c2 ) % mod p; // convert back to 
    }

  fclose(pk);
  fclose(mes);

  return 0;

  return 0;
}
