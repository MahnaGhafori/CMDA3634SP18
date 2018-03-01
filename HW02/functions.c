#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "functions.h"

//compute a*b mod p safely
long modprod(long a, long  b, long p) {
  /* Q1.2: Complete this function */
  if (a == 0 || b == 0) {
		return 0;
  }
  if (a == 1) {
		return a;
  }
  if (b == 1) {
		return a; 
  }

  // Returns: (a * b/2) mod p 
  long a2 = modprod(a, b / 2, c);

  //Even factor 
  if ((b & 1) == 0) { 
  	return (a2 + a2) % c;
	} else {
	return ((a & p) + (a2 + a2)) % p;
	}
}

//compute a^b mod p safely
unsigned int modExp(unsigned num, unsigned pow, unsigned mod) {
  /* Q1.3: Complete this function */
  unsigned long long test;
  unsigned long long n = num; 
  for(test = 1; pow; pow >>= 1) 
  {
	if (pow & 1) 
		test = ((test % mod) * (n % mod)) % mod;
	n = ((n % mod) * (n % mod)) % mod; 
  }

  return test; 
}

//returns either 0 or 1 randomly
unsigned int randomBit() {
  return rand()%2;
}

//returns a random integer which is between 2^{n-1} and 2^{n}
unsigned int randXbitInt(unsigned int n) {
  unsigned int r = 1;
  for (unsigned int i=0; i<n-1; i++) {
    r = r*2 + randomBit();
  }
  return r;
}

//tests for primality and return 1 if N is probably prime and 0 if N is composite
unsigned int isProbablyPrime(unsigned int N) {

  if (N%2==0) return 0; //not interested in even numbers (including 2)

  unsigned int NsmallPrimes = 168;
  unsigned int smallPrimeList[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 
                                37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 
                                79, 83, 89, 97, 101, 103, 107, 109, 113, 
                                127, 131, 137, 139, 149, 151, 157, 163, 
                                167, 173, 179, 181, 191, 193, 197, 199, 
                                211, 223, 227, 229, 233, 239, 241, 251, 
                                257, 263, 269, 271, 277, 281, 283, 293, 
                                307, 311, 313, 317, 331, 337, 347, 349, 
                                353, 359, 367, 373, 379, 383, 389, 397, 
                                401, 409, 419, 421, 431, 433, 439, 443, 
                                449, 457, 461, 463, 467, 479, 487, 491, 
                                499, 503, 509, 521, 523, 541, 547, 557, 
                                563, 569, 571, 577, 587, 593, 599, 601, 
                                607, 613, 617, 619, 631, 641, 643, 647, 
                                653, 659, 661, 673, 677, 683, 691, 701, 
                                709, 719, 727, 733, 739, 743, 751, 757, 
                                761, 769, 773, 787, 797, 809, 811, 821, 
                                823, 827, 829, 839, 853, 857, 859, 863, 
                                877, 881, 883, 887, 907, 911, 919, 929, 
                                937, 941, 947, 953, 967, 971, 977, 983, 
                                991, 997};

  //before using a probablistic primality check, check directly using the small primes list
  for (unsigned int n=1;n<NsmallPrimes;n++) {
    if (N==smallPrimeList[n])   return 1; //true
    if (N%smallPrimeList[n]==0) return 0; //false
  }

  //if we're testing a large number switch to Miller-Rabin primality test
  /* Q2.1: Complete this part of the isProbablyPrime function using the Miller-Rabin pseudo-code */
  unsigned int r,d;
	d = (N-1)/2;
	r = 1;

	while (d % 2 ! = 0) {
		d/=2;
		r++;
	}

  for (unsigned int n=0;n<NsmallPrimes;n++) {
  
  unsigned int x;
  x = modExp(smallPrimeList[n],d,N);

  if (x == 1 || x == N - 1) {
	continue;
  }
	for ( i = 1; i <= r-1; i++) {
	x = modProd(x,x,N);

	if (x == 1) {
	return 0;
	}
	if (x == N-1) {
	continue; 
	}
	return 0;
	}

	return 1; 
  }
  return 1; //true
}

//Finds a generator of Z_p using the assumption that p=2*q+1
unsigned int findGenerator(unsigned int p) {
  /* Q3.3: complete this function and use the fact that p=2*q+1 to quickly find a generator */
	int g = 2; 
	for (int g = 2; g < p; g++);
	{
		if (modExp(g,p-1,p) == 1)
		{
			if (modExp(g,2,p) != 1 && (modExp(g,q,p)))
			{
				return g; 
			}
			else 
			{
				continue; 
			}
		}
		else 
		{
			continue; 
		}
	}
}
