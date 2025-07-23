n = int(input())
a = [0] * (n + 1)
b = [0] * (n + 1)
idx = [0] * n
for i in range(0, n + 1):
    x, y = input().split()
    a[i] = int(x)
    b[i] = int(y)
for i in range(1, n + 1):
    idx[i - 1] = i
idx.sort(key = lambda i : a[i] * b[i])
pi = a[0]
ans = 0
for i in idx:
    ans = max(ans, pi // b[i])
    pi *= a[i]
print(ans)
