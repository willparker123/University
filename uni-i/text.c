#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// Store text using a dynamically allocated character array with a given
// capacity. Use strlen to find the length of the string contained in the array.
struct text {
    int capacity;
    char *content;
};

// Create a new text structure, containing a copy of the given string.
text *newText(char *s)
{
  text *t = malloc(sizeof(text));
  t->capacity = 24;
  while (strlen(s)+1>t->capacity) t->capacity*=2;
  t->content = malloc((t->capacity)*sizeof(char));
  strcpy(t->content, s);
  return t;
}

// Free up both the space for the struct and the space for the content.
// Be careful not to access anything after it has been freed.
void freeText(text *t)
{
  free(t->content);
  free(t);
}

int length(text *t)
{
  int len=0;
  char *currentTAddress = t->content;
  while (*currentTAddress!='\0')
  {
    len++;
    currentTAddress++;
  }
  return len;
}

char get(text *t, int i)
{
  char gotChar = *((t->content)+i);
  return gotChar;
}

void set(text *t, int i, char c)
{
  *((t->content)+i) = c;
}

text *copy(text *t)
{
  text *copiedText = malloc(sizeof(text));
  char *tIndex = t->content;
  for (int i=1;*(t->content)!='\0';i++)
  {
    memcpy(copiedText, tIndex, sizeof(char));
    copiedText = copiedText+1;
    tIndex = tIndex+1;
  }
  memcpy(copiedText, tIndex, sizeof(char));
  return copiedText;
}

int compare(text *t1, text *t2)
{
  for (int i=1;(*(t1->content)!='\0')&&(*t2->content!='\0');i++)
  {
    if (*t1->content>*t2->content) return 1;
    else if (*t1->content<*t2->content) return -1;
    t1->content = t1->content+1;
    t2->content = t2->content+1;
  }
  return 0;
}

void append(text *t1, text *t2)
{
  char *currentPositionT1 = t1->content;
  int i=1;
  for (i=1;*currentPositionT1=='\0';i++)
  {
    currentPositionT1 = t1->content+i;
  }
  currentPositionT1 = malloc(sizeof(t2));
  strcpy(currentPositionT1,t2->content);
}

text *slice(text *t, int i, int j)
{
  text *slice = malloc(sizeof(text));
  slice->content = malloc(sizeof(t->content));
  for (int i=0;i==j;i++)
  {
    memcpy(slice->content+i, t->content+i, sizeof(char));
  }
  return slice;
}

int find(text *t, text *p)
{
  int i=0;
  while (*t->content=='\0')
  {
    if (*t->content==*p->content)
    {
      if(*p->content=='\0')
      {
        return i;
      }
      else
      {
        p->content=p->content+1;
      }
    }
    else
    {
      i++;
      t->content=t->content+1;
      return -1;
    }
  }
  return -1;
}

//-----------------------------------------------------------------------------
// Testing. Use -Dtest_text when compiling for testing.
#ifdef test_text

// Check whether a text is like a given string, as far as can be checked
// without knowing how much memory has been allocated.
bool like(text *t, char *s) {
    if (t == NULL) return false;
    if (t->capacity < strlen(s) + 1) return false;
    if (strcmp(t->content, s) != 0) return false;
    return true;
}

// Test that new allocates 24 bytes if the string fits, or doubles the capacity
// until it does fit, taking the final null character into account.
void testNew() {
    text *t = newText("");
    assert(like(t, ""));
    assert(t->capacity == 24);
    freeText(t);
    t = newText("cat");
    assert(like(t, "cat"));
    assert(t->capacity == 24);
    freeText(t);
    char *s = "supercalifragilisticexpialidocious";
    t = newText(s);
    assert(like(t, s));
    assert(t->capacity == 48);
    freeText(t);
    s = "12345678901234567890123";
    t = newText(s);
    assert(like(t, s));
    assert(t->capacity == 24);
    freeText(t);
    s = "123456789012345678901234";
    t = newText(s);
    assert(like(t, s));
    assert(t->capacity == 48);
    freeText(t);
    s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    t = newText(s);
    assert(like(t, s));
    assert(t->capacity == 96);
    freeText(t);
}

void testLength() {
    text *t = newText("cat");
    assert(length(t) == 3);
    freeText(t);
}

void testGet() {
    text *t = newText("cat");
    assert(get(t,0) == 'c');
    assert(get(t,1) == 'a');
    assert(get(t,2) == 't');
    assert(get(t,3) == '\0');
    freeText(t);
}

void testSet() {
    text *t = newText("cat");
    set(t, 0, 'b');
    set(t, 2, 'r');
    assert(like(t, "bar"));
    freeText(t);
}

void testCopy() {
    text *t = newText("cat");
    text *t2 = copy(t);
    assert(t2 != t);
    assert(t2->content != t->content);
    assert(like(t2, "cat"));
    freeText(t);
    freeText(t2);
}

void testCompare() {
    text *t = newText("cat");
    text *t2 = newText("cat");
    assert(compare(t, t2) == 0);
    text *t3 = newText("car");
    assert(compare(t, t3) > 0);
    text *t4 = newText("caw");
    assert(compare(t, t4) < 0);
    text *t5 = newText("catch");
    assert(compare(t, t5) < 0);
    freeText(t);
    freeText(t2);
    freeText(t3);
    freeText(t4);
    freeText(t5);
}

void testAppend() {
    text *t = newText("car");
    text *t2 = newText("pet");
    append(t, t2);
    assert(like(t, "carpet"));
    assert(t->capacity == 24);
    text *t3 = newText("789012345678901234");
    append(t, t3);
    assert(like(t, "carpet789012345678901234"));
    assert(t->capacity == 48);
    freeText(t);
    freeText(t2);
    freeText(t3);
}

void testSlice() {
    text *t = newText("carpet");
    text *t2 = slice(t, 0, 3);
    assert(like(t2, "car"));
    text *t3 = slice(t, 3, 6);
    assert(like(t3, "pet"));
    freeText(t);
    freeText(t2);
    freeText(t3);
}

void testFind() {
    text *t = newText("carpet");
    text *t2 = newText("car");
    assert(find(t, t2) == 0);
    text *t3 = newText("pet");
    assert(find(t, t3) == 3);
    text *t4 = newText("cat");
    assert(find(t, t4) == -1);
    freeText(t);
    freeText(t2);
    freeText(t3);
    freeText(t4);
}

// Test the library.
int main() {
    testNew();
    testLength();
    testGet();
    testSet();
    testCopy();
    testCompare();
    testAppend();
    testSlice();
    testFind();
    printf("Tests all pass.");
    return 0;
}

#endif
