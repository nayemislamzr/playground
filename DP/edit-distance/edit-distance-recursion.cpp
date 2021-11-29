#include <iostream>
#include <vector>
#include <algorithm>

int editDistance(std::string& firstString, std::string& secondString, int firstStringIndex, int secondStringIndex)
{
	if (firstStringIndex == 0)
		return secondStringIndex;
	if (secondStringIndex == 0)
		return firstStringIndex;
	if (firstString[firstStringIndex] == secondString[secondStringIndex])
		return editDistance(firstString, secondString, firstStringIndex - 1, secondStringIndex - 1);
	return 1 + std::min(std::min(editDistance(firstString,secondString,firstStringIndex-1,secondStringIndex),editDistance(firstString,secondString,firstStringIndex,secondStringIndex-1)),
		editDistance(firstString,secondString,firstStringIndex-1,secondStringIndex-1));
}

int main()
{
 	std::string str1 = "sunday";
 	std::string str2 = "saturday";
 	std::cout << editDistance(str1, str2, str1.length(), str2.length());
}
