#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int box[], int n) {
    int a = box[0] / n, b = box[1] / n, c = box[2] / n;

    int answer = a * b * c;

    return answer;
}

int main()
{
    int box1[] = { 1, 1, 1 };
    int n1 = 1;
    printf("%d\n", solution(box1, n1));

    return 0;
}