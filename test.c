     
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

#define debug
  


unsigned int myAdd(unsigned int a, unsigned int b)
{
    unsigned int carry = a & b;
    unsigned int result = a ^ b;
    while(carry != 0)
    {
        unsigned int shiftedcarry = carry << 1;
        carry = result & shiftedcarry;
        result ^= shiftedcarry;
    }
    return result;
}

unsigned int mytwo(unsigned int a)
{
    a=~a;
    a=myAdd(a,1);
    return a;
}

unsigned int myMult (unsigned int a, unsigned int b){
	unsigned int result = 0;
    while (b != 0)               // Iterate the loop till b == 0
    {
        if (b & 01)               // Bitwise & of the value of b with 01
        {
            result = result + a;  // Add a to result if b is odd .
        }
        a<<=1;                    // Left shifting the value contained in 'a' by 1
                                  // Multiplies a by 2 for each loop
        b>>=1;                    // Right shifting the value contained in 'b' by 1.
    }
    return result;
}

unsigned int modolo (unsigned long int t, unsigned int n, unsigned int k){
	//unsigned int k =6;
	if (n>t){
		return t;
	}
	unsigned int n2 =n;
	unsigned long int a=t;
	a = a >> k;
	
	//
	unsigned int r = 0;
	for (int i = 1; i<k; i++){
		#ifdef debug
		for (int l=14; l>=0; l--){
			if (! (a >> l & 1))
		      printf("0");
		    else
		      printf("1");
		}
		
		printf("   a = %li \n", a);
		#endif
		if((a >> k-i+2) & 1){
			
			a=myAdd(a,n);
		}
		else{
			
		a=myAdd(a,mytwo(n));			
		}
		n=n >> 1;
		//a = a >> 1;
		
	}
	#ifdef debug
	for (int l=14; l>=0; l--){
			if (! (a >> l & 1))
		      printf("0");
		    else
		      printf("1");
		}
	#endif
	if(a >> k & 1){
			a=myAdd(a,n2);
		}
		return a;
}

unsigned int findbit(unsigned int x){
	for (int i=31; i>=0; i--){
		if(x >> i & 1){
			return i+1;
		}
	}
}
unsigned int blakley(unsigned int a, unsigned int b, unsigned int n){

	unsigned r = 0;
	unsigned int k = findbit(a);
	unsigned int k2 = findbit(b);
	if (k2>k){
		unsigned int temp=a;
		a=b;
		b=temp;
		k=k2;
	}
	for (unsigned int i = 0; i < k; i++){
		//r=myAdd(myMult(2,r), myMult(a, ((b >> k-1-i) & 1)));
		r=2*r;
		if((b >> k-1-i) & 1){
			r=r+a;
		}
		if(r>=n){
			r=r-n;
		}
		if(r>=n){
			//r=myAdd(r,mytwo(n));
			r=r-n;
		}
	}
	return r;
}


unsigned int binMethod(unsigned int m, unsigned int e, unsigned int n){
	unsigned int c=1;
	unsigned int k=findbit(e);

	if ((e >> k-1) & 1){
		c=m;
	}
		

	for (int i = k-2; i >=0; i--){
		//printf("c1_%i= %i\n", i,c);
		c=blakley(c,c,n);
		//printf("c2_%i= %i\n", i,c);
		if ((e >> i) & 1){
			c=blakley(c,m,n);
		//	printf("ei");
		}
		

	}
	return c;
}

unsigned int modinv(unsigned int u, unsigned int v)
{
    unsigned int inv, u1, u3, v1, v3, t1, t3, q;
    int iter;
    /* Step X1. Initialise */
    u1 = 1;
    u3 = u;
    v1 = 0;
    v3 = v;
    /* Remember odd/even iterations */
    iter = 1;
    /* Step X2. Loop while v3 != 0 */
    while (v3 != 0)
    {
        /* Step X3. Divide and "Subtract" */
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        /* Swap */
        u1 = v1; v1 = t1; u3 = v3; v3 = t3;
        iter = -iter;
    }
    /* Make sure u3 = gcd(u,v) == 1 */
    if (u3 != 1)
        return 0;   /* Error: No inverse exists */
    /* Ensure a positive result */
    if (iter < 0)
        inv = v - u1;
    else
        inv = u1;
    return inv;
}









void printbitwise(unsigned int x){
	for (int i=31; i>=0; i--){
		if(x >> i & 1){
			printf("1");;
		}
		else{
			printf("0");
		}
	}
}

unsigned int monpro(unsigned int x,unsigned int y, unsigned int n, unsigned int n2,unsigned int  r){
	unsigned int t = x*y;
	unsigned int m = t*n2 % r;
	unsigned int u = (t+m*n)/r;
	if(u>=n){
		return (u-n);
	}
	else{
		return u;
	}
}

unsigned int modexp(unsigned int m, unsigned int e, unsigned int n){
	unsigned int r = 2 << (findbit(n)-1);
	unsigned int r2 = modinv(r,n);
	unsigned int n2=((r*r2)-1)/n;
	//printf("r = %i, r^ = %i, n = %i, n^ = %i \n", r,r2,n,n2);
	unsigned int m2=m*r % n;
	unsigned int x = r%n;
	unsigned int k = findbit(e);
	for (int i = k-1; i>=0; i--){
		x=monpro(x,x,n,n2,r);
		if(e >> i & 1){
			x=monpro(m2,x,n,n2,r);
		}
	}
	x=monpro(x,1,n,n2,r);

	return x;
}

unsigned int evenModExp(unsigned int a, unsigned int e, unsigned int n){
	unsigned int q = n;
	unsigned int j = 1;
	while(1){
		//printf("q = %i\n", q);
		q = q >> 1;
		if(q & 1){
			break;
		}
		j++;
	}
	//printf("j = %i, q = %i \n", j,q);
	unsigned int a1=a%q;
	unsigned int x1=modexp(a1,e,q);
	unsigned int a3=a % (2<<j-1);
	unsigned int e2 = e % (2<<j-2);
	unsigned int x2 = binMethod(a3,e2,(2<<j-1));
	unsigned int q2 = modinv(q,(2<<j-1));
	unsigned int y = (x2-x1)*q2 % (2<<j-1);
	unsigned int x = x1+q*y;
	//printf("x = %i\n", x);
	return x;
}

unsigned int montgomery(unsigned int m, unsigned int e, unsigned int n){
	unsigned int x;
	if(n & 1){
		x = modexp(m,e,n);
	}
	else{
		x = evenModExp(m,e,n);
	}
	return x;
}



int main (int argc, char *argv[]){
	
	

 //evenModExp(375,249,388);
	unsigned int x = montgomery(66,77,119);
	printf("C = %i \n", x);
  return 0;
}



