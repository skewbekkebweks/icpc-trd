def is_good(sss):
    n = len(sss)
    i = 0
    while i < n:
        if sss[i] == '0' and i + 1 < n and sss[i + 1].isdigit(): 
            return False
        if not sss[i].isdigit():
            return False
        cnt = 0
        while i < n and sss[i].isdigit():
            i += 1
            cnt += 1
        if cnt > 10:
            return False
        if i == n:
            return True
        i += 1
        if i == n:
            return False

def check(sss):
    s1, s2 = sss.split('=')
    return eval(s1) == eval(s2)

s = input()

if check(s):
    print("Correct")
    exit(0)

for i in range(len(s)):
    if not s[i].isdigit():
        continue
    for j in range(i):
        ss = s[:j] + s[i] + s[j:i] + s[i + 1:]
        if is_good(ss) and check(ss):
            print(ss)
            exit(0)
    for j in range(i + 1, len(s)):
        ss = s[:i] + s[i + 1:j + 1] + s[i] + s[j + 1:] 
        if is_good(ss) and check(ss):
            print(ss)
            exit(0)
print("Impossible")