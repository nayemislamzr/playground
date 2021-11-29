def solve(x):
    if x == 0:
        return 1
    if x < 0:
        return 0
    ways = 0
    for coin in coins:
        ways += solve(x-coin)
    return ways

coins = []
total_coin = int(input("Enter number of coins : "))
for i in range(0,total_coin):
    coins.append(int(input()))
sum = int(input("Enter total sum : "))
print(sum)
