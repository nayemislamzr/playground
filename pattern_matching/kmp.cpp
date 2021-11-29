#include <iostream>
#include <vector>

namespace cp
{
    class kmp
    {
        private:
            std::vector<int64_t>* lps;
            std::string text,pattern ;
        public:
            kmp() = delete;
            kmp(const std::string& I_text,const std::string& I_pattern)
                : text{I_text} , pattern{I_pattern} , lps{new std::vector<int64_t> (I_pattern.size())}
            {

            }
            ~kmp()
            {
                delete lps;
            }
        private:
            void build_lps();
        public:
            int64_t match();
    };

    void kmp::build_lps()
    {
        int64_t i = 1 , j = 0;
        while(i < pattern.size())
        {
            if(pattern[i] == pattern[j])
            {
                lps->at(i)=++j;
                i++;
            }
            else if(j>0 && pattern[i] != pattern[j])
            {
                j = lps->at(j-1);
            }
            else
            {
                lps->at(i) = 0;
                i++;
            }
        }
    }

    int64_t kmp::match()
    {
        int64_t i = 0 , j = 0 ;
        while(i < text.size())
        {
            if(text[i] != pattern[j])
            {
                if(j == 0)
                {
                    i++;
                }
                else
                {
                    j=lps->at(j-1);
                }
            }
            else
            {
                i++;
                j++;
                if(j == pattern.size())
                    return i-pattern.size();
            }
        }
        return -1;
    }
}

int main()
{
    std::string text = "aaaabaaad";
    std::string ptrn = "aaabaaa";
    std::cout << cp::kmp(text,ptrn).match();
}