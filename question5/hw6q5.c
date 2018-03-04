#include <stdio.h>

int difference(int national, int state);

struct incomes {
  char state[16];
  int income;
};

int main()
{
  struct incomes national_income = {
	"United States", 59039,
  };

  struct incomes state_incomes[] = {
	"Alabama", 47221,
	"Alaska", 75723,
	"Arizona", 57100,
	"Arkansas", 45907,
	"California", 66637,
	"Colorado", 70566,
	"Connecticut", 75923,
	"Delaware", 58046,
	"D.C.",	70982,
	"Florida", 51176,
	"Georgia", 53527,
	"Hawaii", 72133,
	"Idaho", 56564,
	"Illinois", 61386,
	"Indiana", 56094,
	"Iowa",	59094,
	"Kansas", 56810,
	"Kentucky", 45369,
	"Louisiana", 42196,
	"Maine", 50856,
	"Maryland", 73760,
	"Massachusetts", 72266,
	"Michigan", 57091,
	"Minnesota", 70218,
	"Mississippi", 41099,
	"Missouri", 55016,
	"Montana", 57075,
	"Nebraska", 59374,
	"Nevada", 55431,
	"New Hampshire", 76260,
	"New Jersey", 68468,
	"New Mexico", 48451,
	"New York", 61437,
	"North Carolina", 53764,
	"North Dakota",	60184,
	"Ohio",	53985,
	"Oklahoma", 50943,
	"Oregon", 59135,
	"Pennsylvania",	60979,
	"Rhode Island", 61528,
	"South Carolina", 54336,
	"South Dakota",	57450,
	"Tennessee", 51344,
	"Texas", 58146,
	"Utah",	67481,
	"Vermont", 60837,
	"Virginia", 66451,
	"Washington", 70310,
	"West Virginia", 44354,
	"Wisconsin", 59817,
	"Wyoming", 57829,
  };
  
  int i, entry;
  int max = 0;
  int diff[51];

  for (i = 0; i < 51; ++i)
  {
    diff[i] = difference(national_income.income, state_incomes[i].income);
    printf("%s;   Income: %d,   Deviation: %d\n", state_incomes[i].state, state_incomes[i].income, diff[i]);
  }
    for (i = 0; i < 51; ++i)
  {

  // #1: find highest income
  if (state_incomes[i].income > max)
    {
      entry = i;
      max = state_incomes[i].income;
    }
  }

  printf("\nThe highest median income is that of %s (%d).\n", state_incomes[entry].state, state_incomes[entry].income);

  return 0;
}

// #2: find deviation from median national income
int difference(int national, int state)
{
  return state - national;
}
