a = input().split()
ans = 0
for x in a:
    ans <<= 32
    ans += int(x)
print(ans)
