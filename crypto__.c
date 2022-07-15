#include <stdio.h>
int
main ()
{
  char c;
  //printf("Enter a character: ");
  //scanf("%c", &c);  

  // %d displays the integer value of a character
  // %c displays the actual character
  //printf("ASCII value of %c = %d", c, c);
  int otp1[6];
  
  for (int j = 0; j < 6; j++)
    {
      printf ("Enter otp %d:", j);
      scanf ("%d", &otp1[j]);
    }
  int algo[6] = { 67, 38, 97, 50 ,32 , 69};
  for (int i = 0; i < 6; i++)
    {
      printf ("%c", algo[i]);
    }
  int algo2[6] = { 35, 36, 37, 38 , 40, 39};
  int algo3[6] = { 40, 39, 37, 35, 38, 36 };
  int algo4[6] = { 38, 37, 36, 35, 37, 34 };
  int otp2[6];
  for (int k = 0; k < 6; k++)
    {
      otp2[k] = otp1[k] + algo[k];
      //printf("%d",otp2[k]);
      printf ("%c%c%c%c%c%c", otp2[k], algo3[k], algo[k], algo2[k], otp2[k],
	      algo4[k]);

    }
  return 0;
}