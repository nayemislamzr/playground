#include <iostream>
#include <vector>
#include <string>

int32_t editDistance(std::string& firstString, std::string& secondString)
{
	int32_t secondStringIndex = 0, toBeDeleted = 0;
	for(int firstStringIndex = 0 ; firstStringIndex < firstString.length() ; firstStringIndex++)
	{
    	if(firstString[firstStringIndex] != secondString[secondStringIndex])
    	{
    		while (firstString[firstStringIndex] != secondString[secondStringIndex++])
    		{
    			secondStringIndex;
    			toBeDeleted++;
    		}
    	}
    	else 
    	{
    		secondStringIndex++;
    	}
	}
	return toBeDeleted + (secondString.length() - secondStringIndex);
}

int main()
{
	std::string str1 = "sust";
	std::string str2 = "sussstaa";
	std::cout << editDistance(str1,str2);
}