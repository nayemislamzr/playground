#include <iostream>
#include <vector>

int32_t coinCount(std::vector<int32_t>& coins, int32_t totalCoins, int32_t totalAmount)
{
	if (totalAmount == 0) // we got an answer
		return 1;
	if (totalAmount <= 0 )
		return 0;
	if (totalCoins <=0 && totalAmount >= 1)
		return 0;
	return coinCount(coins, totalCoins - 1, totalAmount) +
		coinCount(coins, totalCoins, totalAmount - coins[totalCoins-1]);
}

int main()
{
	int32_t totalAmount , totalCoins;
	std::cin >> totalCoins >> totalAmount;
	std::vector<int32_t> coins(totalCoins);
	for(int i = 0 ; i < totalCoins ; i++)
	{
		std::cin >> coins[i];
	}
	std::cout << coinCount(coins, totalCoins, totalAmount);
}