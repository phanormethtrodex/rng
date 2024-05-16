#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* rng.c
 * #####
 * author: austin stewart (phanormethtrodex)
 *   date: 30/12/2023
 *  descr: the latest and greatest iteration of the rng
 *         finally a version controlled sorcery
 *         hereby putting an end to endless mutations rumaging
 * #####
 *
 *    log: -------------------------------------------------------------------
 *    
 *         1.00 -- 30.12.23
 *         initial version
 *
 *         1.01 -- 31.12.23
 *         fixed bug 'newline-terminating' the rngstring; now null-terminating
 *
 *         1.02 -- 17.01.24
 *         added this changelog
 *
 *         1.03 -- 16.05.24
 *         updated this changelog
 *
 * #####
 *
 */

int isnum(char);
int ischr(char);
int rgen(int);
int rout(int,int,char *);

int main(int argc, char *argv[])
{
  struct timespec TIME;
  float nsec;
  clock_gettime(CLOCK_MONOTONIC,&TIME);
  nsec = (double) (TIME.tv_nsec);
 
	int i = 0;
  
  /*
  int seed = 0;
	char strseed[8];
	FILE *fp = popen("date +%N","r");
	fscanf(fp,"%s",&strseed);
	pclose(fp);
	while (isnum(strseed[i]))
		seed=seed*10+strseed[i++]-'0';
  */

  unsigned int seed;
  seed = (unsigned int)time(NULL)+(unsigned int)nsec;
	//srand48((unsigned int)time(NULL)+seed);
  srandom(seed);
  //printf("seed: %u\n",seed);

	//printf("now: %i nnow: %i exactly now: %g\n",(unsigned int)time(NULL),seed,(unsigned int)time(NULL)+seed);
	//srand(seed);

	int type;
  int carg,ret,count=0;
  char *rstr;

	if (argc>1) {
		//printf("ARGC=%i ; ARGV[1]=%c ; ischr=%s ; isask=%s\n",argc,*(argv[1]),ischr(*(argv[1]))?"YES":"NO",isask(*(argv[1]))?"YES":"NO");
		if ( (argc==3 || argc==2) && ischr(*(argv[1])) ) {
			type = *(argv[1]);
			carg=argc-1;
			//printf("HIT IF\n");
		}
		else if (argc==2 && isnum(*(argv[1]))) {
			type='d';
			carg=1;
			//printf("HIT ELSE IF\n");
		}
		else {
			printf("\nUsage: rng [bondxluazcys] [#]\n\n# - number of characters\n\n[bondxluazcys] - character class:\nb - binary \no - octal\nn - \"nonal\" (1-9)\nd - decimal\nx - hexadecimal\nl - lower\nu - upper\na - alpha\nz - alphanumeric\nc - \"printable\" ascii\ny - non-alphanumeric \"printable\" ascii\ns - any ascii\nno args - random number of chars from random class\n\n");
			//printf("HIT ELSE\n");
			return 1;
		}
		i=0;
		while (isnum(*(argv[carg]+i)))
			count=count*10+*(argv[carg]+i++)-'0';
		if (count==0) count=1;
    rstr = (char *)malloc(sizeof(char)*(count+1));
		ret = rout(type,count,rstr);
	}
	else {
		count=rgen(15)+1;
		type=rgen(11);
		char sets[]="bondxluazcys";
    rstr = (char *)malloc(sizeof(char)*(count+1));
    ret = rout(sets[type],count,rstr);
	}
  if (ret==0)
    printf("%s",rstr);
	return ret;
}

int isnum(char c) {return (c>='0'&&c<='9');}

int ischr(char c) {return (c>='a'&&c<='z');}

/* rgen: generates number [0-arg) */
//int rgen (int range) {return (lrand48()%range);}
int rgen (int range) {return (int)(random()%range);}

int rout (int rtype, int rcount, char *rchars) {
	int i,k,ret;
  //char *rchars;

  //try to dynamalloc an empty string to hold the generated random chars
  //then oneshot printf the entire string instead of one char at a time 
  //rchars = (int *)malloc(sizeof(int)*(rcount+1));
  //malloc before calling and just pass the rstr pointer

	switch (rtype) {
	case 'b':
    for (i=0;i<rcount;i++) {k=rgen(2); *(rchars+i) = k+'0';}
    //*(rchars+rcount) = '\n';
    //printf("%s",rchars);
    //caller shall spit out the generated string
		ret = 0; break;
	case 'o':
		//for (i=0;i<rcount;i++) {k=rgen(8); printf("%i",k);}
 		for (i=0;i<rcount;i++) {k=rgen(8); *(rchars+i) = k+'0';}
		ret = 0; break;
	case 'n':
		//for (i=0;i<rcount;i++) {k=rgen(9); printf("%i",k+1);}
 		for (i=0;i<rcount;i++) {k=rgen(9); *(rchars+i) = k+'0'+1;}
		ret = 0; break;
	case 'd':
		//for (i=0;i<rcount;i++) {k=rgen(10); printf("%i",k);}
 		for (i=0;i<rcount;i++) {k=rgen(10); *(rchars+i) = k+'0';}
		ret = 0; break;
	case 'x':
		//for (i=0;i<rcount;i++) {k=rgen(16); printf("%c",k<10?k+'0':k-10+'a');}
 		for (i=0;i<rcount;i++) {k=rgen(16); *(rchars+i) = k<10?k+'0':k-10+'a';}
		ret = 0; break;
	case 'l':
		//for (i=0;i<rcount;i++) {k=rgen(26); printf("%c",k+'a');}
 		for (i=0;i<rcount;i++) {k=rgen(26); *(rchars+i) = k+'a';}
		ret = 0; break;
	case 'u':
		//for (i=0;i<rcount;i++) {k=rgen(26); printf("%c",k+'A');}
 		for (i=0;i<rcount;i++) {k=rgen(26); *(rchars+i) = k+'A';}
		ret = 0; break;
	case 'a':
		//for (i=0;i<rcount;i++) {k=rgen(52); printf("%c",k<26?k+'a':k-26+'A');}
 		for (i=0;i<rcount;i++) {k=rgen(52); *(rchars+i) = k<26?k+'a':k-26+'A';}
		ret = 0; break;
	case 'z':
		//for (i=0;i<rcount;i++) {k=rgen(62); printf("%c",k<10?k+'0':k<36?k-10+'a':k-36+'A');}
 		for (i=0;i<rcount;i++) {k=rgen(62); *(rchars+i) = k<10?k+'0':k<36?k-10+'a':k-36+'A';}
		ret = 0; break;
	case 'c':
		//for (i=0;i<rcount;i++) {k=rgen(94); printf("%c",k+33);}
 		for (i=0;i<rcount;i++) {k=rgen(94); *(rchars+i) = k+33;}
		ret = 0; break;
	case 'y':
		//for (i=0;i<rcount;i++) {k=rgen(32); printf("%c",k<15?k+'!':k<22?k-15+':':k<28?k-22+'[':k-28+'{');}
 		for (i=0;i<rcount;i++) {k=rgen(32); *(rchars+i) = k<15?k+'!':k<22?k-15+':':k<28?k-22+'[':k-28+'{';}
		ret = 0; break;
	case 's':
		//for (i=0;i<rcount;i++) {k=rgen(128); printf("%c",k);}
 		for (i=0;i<rcount;i++) {k=rgen(128); *(rchars+i) = k;}
		ret = 0; break;
	default:
		//printf("\nUsage: rng [bondxluazcys] [#]\n\n");
		printf("\nUsage: rng [bondxluazcys] [#]\n\n# - number of characters\n\n[bondxluazcys] - character class:\nb - binary \no - octal\nn - \"nonal\" (1-9)\nd - decimal\nx - hexadecimal\nl - lower\nu - upper\na - alpha\nz - alphanumeric\nc - \"printable\" ascii\ny - non-alphanumeric \"printable\" ascii\ns - any ascii\nno args - random number of chars from random class\n\n");
		ret = 99;
		break;
	}
  if (ret==0)
    *(rchars+rcount) = '\0';
  return ret;
}
