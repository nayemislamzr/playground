import math

def solve(x):
    if(x == 0):
        return 0
    if(x < 0):
        return math.inf
    if(sol[x] != math.inf):
        return sol[x]
    best = math.inf
    for coin in coins:
        best =  min(best,solve(x-coin)+1)
    sol[x] = best
    return sol[x]

total_coins = int(input("Enter total number of coins : "))
coins = [0]*total_coins

for i in range(0,total_coins):
    coins[i] = int(input())

sum = int(input("Enter total sum : "))
sol = [math.inf]*1000
print(solve(sum))


