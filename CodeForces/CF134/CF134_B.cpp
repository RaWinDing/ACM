// CF 134
// B. Airport
// by A Code Rabbit

#include <cstdio>
#include <queue>
using namespace std;

int n, m;
int a[1002];
int num_max, num_min;
priority_queue<int, vector<int>, greater<int> > pq_min;
priority_queue<int> pq_max;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
        pq_max.push(a[i]);
        pq_min.push(a[i]);
    }

    num_max = num_min = 0;
    int num;
    for (int i = 0; i < n; i++) {
        num = pq_max.top(); 
        pq_max.pop();
        num_max += num--;
        if (num) pq_max.push(num);

        num = pq_min.top();
        pq_min.pop();
        num_min += num--;
        if (num) pq_min.push(num);
    }

    printf("%d %d\n", num_max, num_min);

    return 0;
}
