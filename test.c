     
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	for (unsigned int i = 0; i < k; i++){
		r=myAdd(myMult(2,r), myMult(a, ((b >> k-1-i) & 1)));
		if(r>=n){
			r=myAdd(r,mytwo(n));
		}
		if(r>=n){
			r=myAdd(r,mytwo(n));

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
		c=blakley(c,c,n);
		if ((e >> i) & 1){
			c=blakley(c,m,n);
		}
	}
	return c;
}



unsigned int mont(unsigned int x, unsigned int y, unsigned int m){
	unsigned int s=0;
	unsigned int c=0;
	unsigned int j=0;
	unsigned int r = myAdd(y,m);
	unsigned int k=findbit(x);
	for (int i=0; i<k; i++) {

		if (!(x >> i & 1)){
			if(!((s ^ c) & 1)) {
				
				j=0;
				printf("j=0 \n");
			}
			else{
				j=m;
				printf("j=m \n");

			}
			
		}
		else{
			if(!((s ^ c ^ y) & 1)){
				
				j=y;
				printf("j=y \n");
			}
			else{
				j=r;
				printf("j=r \n");
			}
		}

		printf("j=%i \n", j);
		s=myAdd(s,c);
		s=myAdd(s,j);
		c=myAdd(s,c);
		c=myAdd(c,j);
		s=s >> 1;
		c=c >> 1;
	}
	unsigned p=myAdd(s,c);
	if (p>=m){
		p=myAdd(p,mytwo(m));
	}

	return p;
}


unsigned int mont2(unsigned int x, unsigned int y, unsigned int m){
	unsigned int n=findbit(x);
	unsigned int xi=0;
	unsigned int p0=0;
	unsigned int p=0;
	for (int i=0; i<n-1; i++){
		if (x >> i & 1){
			p=myAdd(p,y);
		}
		if (p & 1){
			p=myAdd(p,m);
		}		
		p=p>>1;
	}
	if(p>=m){
		p=p-m;
	}
	return p;
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



int main (int argc, char *argv[]){
	


	unsigned int m = atoi(argv[1]);
	unsigned int e = atoi(argv[2]);
	unsigned int d = atoi(argv[3]);
	unsigned int n = atoi(argv[4]);


	unsigned int c = binMethod(m,e,n);
	
	//printf("blakley = %i \n", blakley(50,50,143,findbit(50)));
  
  	printf("m= %i \n", binMethod(c,d,n));
	printf("\n");
  	printf("c= %i \n", c);
  	//printf("#bit = %i \n", findbit(5));
  
  //printbitwise(argv[1]);
  
	

  printf("\n");

  return 0;
}



