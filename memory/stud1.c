#include <stdio.h>
#include <stdlib.h>
struct student {
int id;
char name[20];
};
int main()
{
struct student *ptr;
int n, i;
printf("How many student ? ");
scanf("%d", &n);
if (n <= 0) {
fprintf(stderr, "errpr: wrong number.\n");
fprintf(stderr, "terminate program\n");
exit(1);
}

ptr = (struct student *) malloc(n * sizeof(struct student));
if (ptr == NULL) {
perror("malloc");
exit(2);
}
printf("enter student number and name for %d. students\n", n);
for (i = 0; i < n; i++)
scanf("%d %s\n", &ptr[i].id, ptr[i].name);
printf("\n* student information *\n");
for (i = n-1; i >= 0; i--)
printf("%d %s\n", ptr[i].id, ptr[i].name);
printf("\n");
exit(0);
}