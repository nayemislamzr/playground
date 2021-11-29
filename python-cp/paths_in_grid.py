import math

def solve(x,y,grid):
    if x < 0 or y < 0 :
        return -math.inf
    if x == 0 and y == 0 :
        return grid[x][y]
    return max(solve(x-1,y,grid),solve(x,y-1,grid))+grid[x][y]

n = int(input("n*n : "))
grid = [[0]*n]*n

for i in range(0,n):
    for j in range(0,n):
        grid[i][j] = i+j

print(solve(n-1,n-1,grid))
