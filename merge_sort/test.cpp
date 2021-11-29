#include <iostream>
#include <stack>
#include <stdlib.h>

int opPre (char curr)
{
    if (curr=='^')
        return 3;
    if (curr=='*' || curr=='/')
        return 2;
    if (curr=='+' || curr=='-')
        return 1;
    return 0;                            
}

std::string infix_to_postfix(std::string& s)
{
    std::stack<char> exp;
    std::string res;
    for(int i=0 ; i <s.size() ;i++ )
    {
        if (s[i]=='(')
            exp.push('(');
        else if (s[i]==')')
        {
            while(exp.top()!='(')
            {
                res+=exp.top();
                exp.pop();
            }
            exp.pop();
        }
        else if (opPre(s[i])==0)
        {
            res+=s[i];
        }            
        else if(exp.empty())
            exp.push(s[i]);      
        else if(!exp.empty() && opPre(s[i])>opPre(exp.top())) 
            exp.push(s[i]);
        else 
        {
            while(!exp.empty() && exp.top()!='(')
            {
                res+=exp.top();
                exp.pop();
            }
            exp.push(s[i]);
        }        
    }
    while(!exp.empty())
    {
        res+=exp.top();
        exp.pop();
    }
    return res;
}

int main()
{
    std::string s;
    std::cin >> s ;
    std::cout << infix_to_postfix(s);
}