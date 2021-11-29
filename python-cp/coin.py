import math

def solve(x):
    if x == 0: 
        return 0
    if x < 0:
        return math.inf
    best = math.inf
    for coin in coins:
        best =  min(best,solve(x-coin)+1)
    return best

coins = []
total_coins = int(input("Enter number of coins : "))
for i in range(0,total_coins):
    coin = int(input())
    coins.append(coin)

sum = int(input("Enter required sum : "))
print(solve(10))

