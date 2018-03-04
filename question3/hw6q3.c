#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAXLINES 5000
#define ALLOCSIZE 10000 // size of available space

// globals
char *lineptr[MAXLINES]; // pointers to text lines
static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf;  // next free position

// functions
double my_atof(char s[]);
int numcmp(char *s1, char *s2);
int fldcmp(char *s1, char *s2);
int revstrcmp(char *s1, char *s2);
int revnumcmp(char *s1, char *s2);
int revfldcmp(char *s1, char *s2);
int revfldnumcmp(char *s1, char *s2);
int fldnumcmp(char *s1, char *s2);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void q_sort(void *lineptr[], int left, int right, 
           int (*comp)(void *, void *));

// sort input lines
int main(int argc, char *argv[])
{
    int nlines, i; // number of input lines read
    int numeric = 0, reverse = 0, fold = 0;

    for (i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-n") == 0)
            numeric = 1;
        if (strcmp(argv[i], "-r") == 0)
            reverse = 1;
        if (strcmp(argv[i], "-f") == 0)
            fold = 1;
    }
    printf("n: %d, r: %d, f: %d\n\n", numeric, reverse, fold);
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        if (numeric == 0 && reverse == 0 && fold == 0)
            q_sort((void **) lineptr, 0, nlines-1,
              (int (*)(void*, void*))(strcmp));

        else if (numeric == 0 && reverse == 1 && fold == 0)
            q_sort((void **) lineptr, 0, nlines-1,
              (int (*)(void*, void*))(revstrcmp));

        else if (numeric == 1 && reverse == 0 && fold == 0)
            q_sort((void **) lineptr, 0, nlines-1,
              (int (*)(void*, void*))(numcmp));

        else if (numeric == 1 && reverse == 1 && fold == 0)
            q_sort((void **) lineptr, 0, nlines-1,
              (int (*)(void*, void*))(revnumcmp));

        else if (numeric == 0 && reverse == 0 && fold == 1)
            q_sort((void **) lineptr, 0, nlines-1,
              (int (*)(void*, void*))(fldcmp));

        else if (numeric == 0 && reverse == 1 && fold == 1)
            q_sort((void **) lineptr, 0, nlines-1,
              (int (*)(void*, void*))(revfldcmp));

        else if (numeric == 1 && reverse == 1 && fold == 1)
            q_sort((void **) lineptr, 0, nlines-1,
              (int (*)(void*, void*))(revfldnumcmp));

        else if (numeric == 1 && reverse == 0 && fold == 1)
            q_sort((void **) lineptr, 0, nlines-1,
              (int (*)(void*, void*))(fldnumcmp));

        writelines(lineptr, nlines);
        return 0;
    }
    else 
    {
        printf("input too big to sort\n");
        return 1;
    }
    return 0;
}

#define MAXLEN 1000 // max length of any input line
int mygetline(char *, int);
char *alloc(int);

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
            line[len-1] = '\0'; // delete newlines
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}



char *alloc(int n) // return pointer to n characters
{
    if (allocbuf + ALLOCSIZE - allocp >= n) // it fits
    {
        allocp += n;
        return allocp - n; // old p
    }
    else // not enough room
        return 0;
}

void afree(char *p) // free storage pointed to by p
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
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

// qsort:sort v[left]...v[right] into increasing order
void q_sort(void *v[], int left, int right, 
           int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    // do nothing if array contains fewer than two elements
    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) <0)
            swap(v, ++last, i);
    swap(v, left, last);
    q_sort(v, left, last-1, comp);
    q_sort(v, last+1, right, comp);
}

// swap:interchange v[i] and v[j]
void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


// writelines: write output lines
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

// compare s1 and s2 numerically
/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

// reverse strcmp
int revstrcmp(char *s1, char *s2)
{
    return -1 * strcmp(s1, s2);
}

// reverse numcmp
int revnumcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return 1;
    else if (v1 > v2)
        return -1;
    else
        return 0;
}

// fold cmp
int fldcmp(char *s1, char *s2)
{
    for ( ; tolower(*s1) == tolower(*s2); s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return tolower(*s1) - tolower(*s2);
}

// reverse fold cmp
int revfldcmp(char *s1, char *s2)
{
    for ( ; tolower(*s1) == tolower(*s2); s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return tolower(*s2) - tolower(*s1);
}

int revfldnumcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = my_atof(s1);
    v2 = my_atof(s2);
    if (v1 < v2)
        return 1;
    else if (v1 > v2)
        return -1;
    else
        return 0;
}

int fldnumcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = my_atof(s1);
    v2 = my_atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

double my_atof(char s[])
{
    double val, power;
    int i, sign;

    for (i=0; isspace(s[i]); i++) // skip white space
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val=0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (tolower(s[i]) - '0');

    if (s[i] == '.')
        i++;

    for (power=1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (tolower(s[i]) - '0');
        power *= 10.0;
    }
    return sign * val / power;
}
