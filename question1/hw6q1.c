#include <stdio.h>

void ranges(int x[], int npts, int *max_ptr, int *min_ptr);

void ranges(int x[], int npts, int *max_ptr, int *min_ptr)
{
  int i;
  *max_ptr = *min_ptr = x[0];

  for (i = 1; i < npts; ++i)
  {
    if (x[i] > *max_ptr)
      *max_ptr = x[i];
    if (x[i] < *min_ptr)
      *min_ptr = x[i];
  }
}

int main()
{
  int x1[6] = {1, 2, 3, 4, 5, 6};
  int min1, max1;
  ranges(x1, 6, &max1, &min1);
  printf("Array 1\nMinimum = %d, Maximum = %d\n", min1, max1);

  int x2[10] = {96, 83, 21, 20, 94, 48, 53, 67, 66, 72};
  int min2, max2;
  ranges(x2, 10, &max2, &min2);
  printf("Array 2\nMinimum = %d, Maximum = %d\n", min2, max2);

  int x3[8] = {580, 564, 20, 280, 34, 722, 111, 839};
  int min3, max3;
  ranges(x3, 8, &max3, &min3);
  printf("Array 3\nMinimum = %d, Maximum = %d\n", min3, max3);

  return 0;
}
