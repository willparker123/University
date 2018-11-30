#include <stdio.h>
#include <stdlib.h>

int gradenum = 0;
int askGrade();
int tryAgain();
int printGrade();

int tryAgainLogic(char choice)
{
  if (choice == 'Y')
  {
    gradenum = 0;
    askGrade();
  }
  else if (choice == 'y')
  {
    gradenum = 0;
    askGrade();
  }
  else if (choice == 'N')
  {
    exit(EXIT_SUCCESS);
  }
  else if (choice == 'n')
  {
    exit(EXIT_SUCCESS);
  }
  else
  {
    printf("Invalid input: Enter 'Y' or 'N'.\n");
    tryAgain();
  }
  return 0;
}

int tryAgain()
{
  char choice;
  printf("Try again? [Y/N]: \n");
  scanf("%c", &choice);
  tryAgainLogic(choice);
  return choice;
}

int printGrade(int a)
{
    printf("%d\n", a);
    tryAgain();
    return 0;
}

int askGrade()
{
  printf("Please input your grade (integer, percentage): ");
  scanf("%d", &gradenum);

  if (gradenum<0 || gradenum>100)
  {
    printf("Error: Integer out of range\n");
    tryAgain();
    return 1;
  }
  else
  {
    printGrade(gradenum);
    return 0;
  }
}

int main()
{
  setbuf(stdout, NULL);
  askGrade();
  return 0;
}
