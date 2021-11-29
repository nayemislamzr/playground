#include <iostream>
#include <vector>
#include <memory>

namespace Zr {

class Z{

private :
    const std::string concatinated_str ;
    const size_t pattern_len , concated_len ;
    std::unique_ptr<std::vector<unsigned int>> z_array ;

public :
    Z() = delete ;
    explicit Z(const std::string& m_text,const std::string& m_pattern)
        : concatinated_str{ m_pattern + '$' + m_text } , 
        pattern_len{m_pattern.length()} ,
        concated_len{concatinated_str.length()} { 
            z_array = std::unique_ptr<std::vector<unsigned int>> (new std::vector<unsigned int> (concated_len));
    }
    
    void construct_zarray() const {
        int l = 0 , r = 0 , k ;
        for(int i = 1 ; i < concated_len ; i++) {
            if( i > r ) {
                l = r = i ;
                while( r < concated_len && concatinated_str[r-l] == concatinated_str[r] ) {
                    r++ ;
                }
                z_array->at(i) = r - l ;
                r-- ;
            }
            else {
                k = i - l ;
                if( z_array->at(k) < r-i+1 ) {
                    z_array->at(i) = z_array->at(k) ;
                }
                else {
                    l = i ;
                    while( r < concated_len && concatinated_str[r-l] == concatinated_str[r] ) {
                        r++ ;
                    }
                    z_array->at(i) = r - l ;
                    r-- ;
                }
            }
        }
    }

    bool matched() const {
        for(auto& z_value : *z_array) {
            if( z_value == pattern_len )
                return true ;
        }
        return false ;
    }

    std::vector<unsigned int> matching_indexes() noexcept {
        std::vector<unsigned int> matched_indexes ;
        for(int i = pattern_len+1 ; i < concated_len ; i++) {
            if( z_array->at(i) == pattern_len )
                matched_indexes.emplace_back( i - pattern_len ) ;
        }
        return matched_indexes ;
    }

};

}

int main() {
    Zr::Z demo ("ababab" , "aa");
    demo.construct_zarray();
    auto a = demo.matching_indexes() ;
    for(auto& i : a)
        std::cout << i << " ";
    std::cout << " " << demo.matched() ;
}
