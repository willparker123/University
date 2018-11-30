#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

int cardInHandValue[10];
char cardInHandSuit[10];
char cardInHandName[10];
int cardInHandValueAI[10];
char cardInHandSuitAI[10];
char cardInHandNameAI[10];
int x=-1;
int z=-1;
int d[0];
int y=0;
bool duplicate=false;
int cCardAI=0;
int cCard=0;
int handV=0;
int handVAI=0;
bool aiStopped=false;

bool checkDeck()
{
  int found=1,i,j;
  for (i=0;i<y;i++)
  {
    for (j=i+1;j<y;j++) if (d[i]==d[j])
    {
      found=0;
      duplicate=true;
      break;
    }
    if (!found) break;
  }
  if (found) return false;
}

int dealCardAI(int x)
{
  int rV,rS;

    srand ( time(NULL) );
    rS = rand() % 3;
    rV = rand() % 12;

    if (rV==0) {handVAI=handVAI+2; cardInHandNameAI[z] = '2';}
    else if (rV==1) {handVAI=handVAI+3; cardInHandNameAI[z] = '3';}
    else if (rV==2) {handVAI=handVAI+4; cardInHandNameAI[z] = '4';}
    else if (rV==3) {handVAI=handVAI+5; cardInHandNameAI[z] = '5';}
    else if (rV==4) {handVAI=handVAI+6; cardInHandNameAI[z] = '6';}
    else if (rV==5) {handVAI=handVAI+7; cardInHandNameAI[z] = '7';}
    else if (rV==6) {handVAI=handVAI+8; cardInHandNameAI[z] = '8';}
    else if (rV==7) {handVAI=handVAI+9; cardInHandNameAI[z] = '9';}
    else if (rV==8) {handVAI=handVAI+10; cardInHandNameAI[z] = 'T';}
    else if (rV==9) {handVAI=handVAI+10; cardInHandNameAI[z] = 'J';}
    else if (rV==10) {handVAI=handVAI+10; cardInHandNameAI[z] = 'Q';}
    else if (rV==11) {handVAI=handVAI+10; cardInHandNameAI[z] = 'K';}
    else if (rV==12) {handVAI=handVAI+11; cardInHandNameAI[z] = 'A';}
    else printf("Error card: %d\n", rV);

    if (rS==0) {cardInHandSuitAI[z] = 'H';d[y]=100+rV;}
    else if (rS==1) {cardInHandSuitAI[z] = 'D';d[y]=200+rV;}
    else if (rS==2) {cardInHandSuitAI[z] = 'C';d[y]=300+rV;}
    else if (rS==3) {cardInHandSuitAI[z] = 'S';d[y]=400+rV;}
    else printf("Error card: %d\n", rS);

    if (duplicate==true)
    {
      printf("duplicate found\n");
      dealCardAI(z);
      duplicate=false;
    }
    else
    {
      printf("AI's card is: %c%c\n", cardInHandNameAI[z], cardInHandSuitAI[z]);
      //printf("%d",d[y]);
      y=y+1;
      return z;
    }
}

int dealCard(int x)
{
  int rV,rS;

    srand ( time(NULL) );
    rS = rand() % 3;
    rV = rand() % 12;

    if (rV==0) {handV=handV+2; cardInHandName[x] = '2';}
    else if (rV==1) {handV=handV+3; cardInHandName[x] = '3';}
    else if (rV==2) {handV=handV+4; cardInHandName[x] = '4';}
    else if (rV==3) {handV=handV+5; cardInHandName[x] = '5';}
    else if (rV==4) {handV=handV+6; cardInHandName[x] = '6';}
    else if (rV==5) {handV=handV+7; cardInHandName[x] = '7';}
    else if (rV==6) {handV=handV+8; cardInHandName[x] = '8';}
    else if (rV==7) {handV=handV+9; cardInHandName[x] = '9';}
    else if (rV==8) {handV=handV+10; cardInHandName[x] = 'T';}
    else if (rV==9) {handV=handV+10; cardInHandName[x] = 'J';}
    else if (rV==10) {handV=handV+10; cardInHandName[x] = 'Q';}
    else if (rV==11) {handV=handV+10; cardInHandName[x] = 'K';}
    else if (rV==12) {handV=handV+11; cardInHandName[x] = 'A';}
    else printf("Error card: %d\n", rV);

    if (rS==0) {cardInHandSuit[x] = 'H';d[y]=100+rV;}
    else if (rS==1) {cardInHandSuit[x] = 'D';d[y]=200+rV;}
    else if (rS==2) {cardInHandSuit[x] = 'C';d[y]=300+rV;}
    else if (rS==3) {cardInHandSuit[x] = 'S';d[y]=400+rV;}
    else printf("Error card: %d\n", rS);

    if (duplicate==true)
    {
      printf("duplicate found\n");
      dealCard(x);
      duplicate=false;
    }
    else
    {
      printf("Your cards are: ");
      for (int i=0;i<=x;i++)
      {
        printf("%c%c ", cardInHandName[i], cardInHandSuit[i]);
      }
      //printf("%d",d[y]);
      printf("\n");
      y=y+1;
      return x;
    }
}

int askInput()
{
  char input;
  printf("Press enter to get dealt your cards:\n");
  getchar();
}

int cardOption()
{
  char input;
  printf("\nDo you want to hit or stick? [h/s]: \n");
  scanf(" %c",&input);
  if (input=='h' || input=='H') {cCard=cCard+1;dealCard(cCard);sleep(1);}
  else if (input=='s' || input=='S')
  {
    return 0;
  }//cardLogic()
  else {printf("Invalid input");cardOption();return -1;}
}

int intro()
{
  printf("----------------\nWelcome to the card game 21!\n\nThe aim of the game is to get as close to (but not exceeding)\nthe number '21' with your cards as possible, and to get higher\nthan your opponent.\n----------------\n");
  printf("The suits are denoted [A,B] where A/B are the value and suit\nof the card respectively.\n\n");
  printf("Suits: C=Clubs, D=Diamonds, H=Hearts, S=Spades\n");
  printf("Value: T=10, J=Jack, Q=Queen, K=King, A=Ace\n\n");
  return 0;
}

int cardLogic()
{
  if (aiStopped==false)
  {
    srand ( time(NULL) );
    int r = rand() % 1;
    if (r<=0 && aiStopped==false) {dealCardAI(cCardAI);cCardAI=cCardAI+1;sleep(1);}
    else if (r>0) aiStopped=true;
    else return 0;
      //printf("%d",handV);
      if (handV>21)
      {
        printf("Bust! The AI wins!\n");
        exit(0);
        return true;
      }
      else if (aiStopped==true)
      {
        if (handV>handVAI) {printf("You won!\n");return true;exit(0);}
        else if (handV==handVAI) {printf("You drew!\n");return true;exit(0);}
        else {printf("You lost!\n");return true;exit(0);}
      }
      else if (handVAI>21)
      {
        printf("You won! The AI bust!\n");
        exit(0);
        return true;
      }
      else
      {
        cardOption();
        return false;
      }
  }
  else
  {
    if (handV>21)
    {
      printf("Bust! The AI wins!\n");
      exit(0);
      return true;
    }
    else if (aiStopped==true)
    {
      if (handV>handVAI) {printf("You won!\n");return true;exit(0);}
      else if (handV==handVAI) {printf("You drew!\n");return true;exit(0);}
      else {printf("You lost!\n");return true;exit(0);}
    }
    else if (handVAI>21)
    {
      printf("You won! The AI bust!\n");
      exit(0);
      return true;
    }
    else
    {
      cardOption();
      return false;
    }
  }
}

int main()
{
  printf("%lu",sizeof(int));
  printf("%lu",sizeof(char*));
  printf("%lu",sizeof(char));
  setbuf(stdout, NULL);
  intro();
  askInput();
  dealCard(cCard);sleep(1); //deals first card
  cCard=cCard+1;
  dealCard(cCard);sleep(1); //deals second card
  dealCardAI(cCardAI);sleep(1); //deals first card
  cCardAI=cCardAI+1;
  dealCardAI(cCardAI);sleep(1); //deals second card
  cardOption();
  while (cardLogic()==false) {cardLogic();}
}
