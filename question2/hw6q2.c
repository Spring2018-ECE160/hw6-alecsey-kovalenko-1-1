#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// tail - prints the last n lines of its input
// line storage code taken from K&R pgs. 108-109

#define MAXLINES 5000
#define ALLOCSIZE 10000
#define MAXLEN 1000

char *lineptr[MAXLINES];
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

int readlines(char *lineptr[], int maxlines);
int mygetline(char *, int);
char *alloc(int);


int main(int argc, char *argv[])
{
  int nlines, i;
  int n = 10;  // lines to print, default 10

  if (argc == 1)
    ;
  else if (--argc > 0 && (*++argv)[0] == '-')
    n = -atoi(argv[0]);
  else
  {
    printf("Error: Invalid argument\n");
    return -1;
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >= n)
  {
    for (i = nlines - n; i < nlines; ++i)
    {
      printf("%s\n", lineptr[i]);
    }
  }
  else if (nlines < n)
  {
    printf("\nWarning: Input has fewer than %d lines. Printing entire contents.\n\n\n", n);
    for (i = 0; i < nlines; ++i)
    {
      printf("%s\n", lineptr[i]);
    }
  }
  return 0;
}

// readlines: read input lines
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else
        {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

// mygetline: get line into s, return length
int mygetline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

char *alloc(int n) // return pointer to n characters
{
    if (allocbuf + ALLOCSIZE - allocp >= n)
    {
        allocp += n;
        return allocp - n;
    }
    else
        return 0;
}
