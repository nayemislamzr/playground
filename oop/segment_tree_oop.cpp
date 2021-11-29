#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <functional>

namespace cp
{
    enum class query_option
    {
        greater,
        lesser,
        sum
    };

    template <typename T, cp::query_option Q>
    class segtree
    {
    private :
        struct node
        {
            T query_field{0};
            T propagation{0};
        };
        size_t size{0};
        std::unique_ptr<std::vector<node>> m_segtree;
        std::vector<T> m_array;

    public :
        segtree() = default;
        // constructor
        segtree(const std::initializer_list<T>& list);
        segtree(const std::vector<T>& I_arr);

        template<size_t SIZE>
        segtree(const std::array<T,SIZE>& I_arr)
        {
            size = I_arr.size();
            m_array.reserve(size);
            for(size_t i = 0 ; i < size ; i++)
            {
                m_array[i] = I_arr[i];
            }
            m_segtree = std::unique_ptr<std::vector<node>> (new std::vector<node>(size*3));
            init(1,0,size-1);
        }
        segtree<T,Q>& operator=(const std::vector<int>& R_vec);
        template<size_t SIZE>
        segtree<T,Q>& operator=(const std::array<T,SIZE>& R_arr)
        {
            size = R_arr.size();
            m_array.clear();
            m_segtree.reset();
            m_array.reserve(size);
            for(size_t i = 0 ; i < size ; i++)
            {
                m_array[i] = R_arr[i];
            }
            m_segtree = std::unique_ptr<std::vector<node>> (new std::vector<node>(size*3));
            init(1,0,size-1);
            return *this;
        }
        segtree<T,Q>& operator=(const std::initializer_list<T>& I_list);
        // copy_constructor
        segtree(segtree<T,Q>& right);
        // move constructor
        segtree(segtree<T,Q>&& right);
        // copy operator
        segtree<T,Q>& operator=(segtree<T,Q>& right);
        // move operator
        segtree<T,Q>& operator=(segtree<T,Q>&& right);
        // destructor
        ~segtree() = default;
        void assign(const std::initializer_list<T>& list);
    private :
        // helper functions
        inline constexpr size_t left_of(size_t i) noexcept {return 2*i;}
        inline constexpr size_t right_of(size_t i) noexcept {return 2*i+1;}
        inline constexpr size_t middle_of(size_t b, size_t e) noexcept {return b + (e-b)/2 ;}
        inline constexpr size_t length_of(size_t b, size_t e) noexcept {return e-b+1;}
        // segment tree operations
        void constexpr init(size_t curr_node, size_t segment_begin, size_t segment_end) noexcept;
        void constexpr update_by_range(size_t query_begin, size_t query_end, T new_val, size_t curr_node , size_t segment_begin , size_t segment_end);
        T constexpr query_with_args(size_t query_begin, size_t query_end, size_t curr_node , size_t segment_begin , size_t segment_end, T carry);
    public :
        void constexpr update(size_t query_begin, size_t query_end, T new_val) noexcept;
        T constexpr query(size_t query_begin, size_t query_end) noexcept;
    };

    template <typename T, cp::query_option Q>
    segtree<T,Q>::segtree(const std::initializer_list<T>& list)
        : size{list.size()}, m_array{list}
    {
        m_segtree = std::unique_ptr<std::vector<node>>(new std::vector<node> (size*3));
        init(1,0,size-1);
    }

    template <typename T, cp::query_option Q>
    segtree<T,Q>::segtree(const std::vector<T>& I_arr)
        : size{I_arr.size()} , m_array{I_arr}
    {
        m_segtree = std::unique_ptr<std::vector<node>>(new std::vector<node> (size*3));
        init(1,0,size-1);
    }

    template <typename T, cp::query_option Q>
    segtree<T,Q>::segtree(segtree<T,Q>& right)
        : size{right.size} , m_array{right.m_array} , m_segtree{ new std::vector<node> (*right.m_segtree)}
    {   
        
    }

    template <typename T, cp::query_option Q>
    segtree<T,Q>::segtree(segtree<T,Q>&& right)
        : size{right.size} , m_array{std::move(right.m_array)} , m_segtree{std::move(right.m_segtree)}
    {
        right.size = 0;
    }

    template <typename T, cp::query_option Q>
    segtree<T,Q>& segtree<T,Q>::operator=(const std::vector<int>& R_vec)
    {
        size = R_vec.size();
        m_array = R_vec;
        m_segtree = std::unique_ptr<std::vector<node>> (new std::vector<node> (size*3));
        init(1,0,size-1);
        return *this;
    }
    
    template <typename T, cp::query_option Q>
    segtree<T,Q>& segtree<T,Q>::operator=(const std::initializer_list<T>& I_list)
    {
        size = I_list.size();
        m_array.clear();
        m_array.assign(I_list);
        m_segtree.reset();
        m_segtree = std::unique_ptr<std::vector<node>> (new std::vector<node> (size*3));
        init(1,0,size-1);
        return *this;
    }

    template <typename T, cp::query_option Q>
    segtree<T,Q>& segtree<T,Q>::operator=(segtree<T,Q>& right)
    {
        size = right.size ;
        m_array = right.m_array;
        m_segtree = std::unique_ptr<std::vector<node>> (new std::vector<node> (*right.m_segtree));
        return *this;
    }

    template <typename T, cp::query_option Q>
    segtree<T,Q>& segtree<T,Q>::operator=(segtree<T,Q>&& right)
    {
        size = right.size ;
        right.size = 0;
        m_array = std::move(right.m_array);
        m_segtree = std::move(right.m_segtree);
        return *this;
    }

    template <typename T, cp::query_option Q>
    void segtree<T,Q>::assign(const std::initializer_list<T>& list)
    {
        size = list.size();
        m_array(list);
        m_segtree = std::unique_ptr<std::vector<node>>(new std::vector<node> (size*3));
        init(1,0,size-1);
    }

    template <typename T, cp::query_option Q>
    void constexpr segtree<T,Q>::init(size_t curr_node, size_t segment_begin, size_t segment_end) noexcept
    {
        if(segment_begin == segment_end)
        {
            m_segtree->at(curr_node).query_field = m_array[segment_begin];
            return;       
        }
        size_t left_node = left_of(curr_node);
        size_t right_node = right_of(curr_node);
        size_t segment_middle = middle_of(segment_begin,segment_end);
        init(left_node,segment_begin,segment_middle);
        init(right_node,segment_middle+1,segment_end);
        if constexpr (Q == query_option::sum) m_segtree->at(curr_node).query_field = m_segtree->at(left_node).query_field + m_segtree->at(right_node).query_field;
        if constexpr (Q == query_option::greater) m_segtree->at(curr_node).query_field = std::max(m_segtree->at(left_node).query_field,m_segtree->at(right_node).query_field);
        if constexpr (Q == query_option::lesser) m_segtree->at(curr_node).query_field = std::min(m_segtree->at(left_node).query_field,m_segtree->at(right_node).query_field);
    }

    template <typename T, cp::query_option Q>
    void constexpr segtree<T,Q>::update_by_range(size_t query_begin, size_t query_end, T new_val, size_t curr_node , size_t segment_begin , size_t segment_end)
    {
        std::function<void()> sum_ = [=]()
        {
            m_segtree->at(curr_node).query_field += (length_of(segment_begin,segment_end)*new_val);
            m_segtree->at(curr_node).propagation += new_val; 
            return;
        };

        std::function<void()> max_or_min = [=]()
        {
            m_segtree->at(curr_node).query_field = new_val;
            return;
        };

        if(query_begin > segment_end || query_end < segment_begin)
        {
            return;
        }
        if(segment_begin >= query_begin && segment_end <= query_end)
        {
            switch(Q)
            {
                case query_option::sum :
                    sum_();
                    return;
                case query_option::greater :
                case query_option::lesser :
                    max_or_min();
                    return;
                default :
                    return;
            }
        }
        size_t left_node = left_of(curr_node);
        size_t right_node = right_of(curr_node);
        size_t segment_middle = middle_of(segment_begin,segment_end);
        update_by_range(query_begin,query_end,new_val,left_node,segment_begin,segment_middle);
        update_by_range(query_begin,query_end,new_val,right_node,segment_middle+1,segment_end);
        if constexpr (Q == query_option::sum) m_segtree->at(curr_node).query_field = m_segtree->at(left_node).query_field + m_segtree->at(right_node).query_field + (length_of(segment_begin,segment_end)*(m_segtree->at(curr_node).propagation));
        if constexpr (Q == query_option::greater) m_segtree->at(curr_node).query_field = std::max(m_segtree->at(left_node).query_field , m_segtree->at(right_node).query_field);
        if constexpr (Q == query_option::lesser) m_segtree->at(curr_node).query_field = std::min(m_segtree->at(left_node).query_field , m_segtree->at(right_node).query_field);
    }

    template <typename T, cp::query_option Q>
    void constexpr segtree<T,Q>::update(size_t query_begin, size_t query_end, T new_val) noexcept
    {
        switch(Q)
        {
            case query_option::sum :
                update_by_range(query_begin,query_end,new_val,1,0,size-1);
                return;
            case query_option::greater :
            case query_option::lesser :
                for(size_t i = query_begin ; i <= query_end ; i++)
                {
                    update_by_range(i,i,new_val,1,0,size-1);
                }
                return;
            default :
                return;
        }
    }

    template <typename T, cp::query_option Q>
    T constexpr segtree<T,Q>::query_with_args(size_t query_begin, size_t query_end, size_t curr_node , size_t segment_begin , size_t segment_end, T carry)
    {
        if(query_begin > segment_end || query_end < segment_begin)
        {
            switch(Q)
            {
                case query_option::sum :
                    return 0;
                case query_option::greater :
                    return INT_MIN;
                case query_option::lesser :
                    return INT_MAX;
                default :
                    return INT_MAX;
            }
        }
        if(segment_begin >= query_begin && segment_end <= query_end)
        {
            switch(Q)
            {
                case query_option::sum :
                    return m_segtree->at(curr_node).query_field + (length_of(segment_begin,segment_end)*carry);
                case query_option::greater :
                case query_option::lesser :
                    return m_segtree->at(curr_node).query_field;
                default:
                    return INT_MAX;
            }
        }
        size_t left_node = left_of(curr_node);
        size_t right_node = right_of(curr_node);
        size_t segment_middle = middle_of(segment_begin,segment_end);

        T query_on_left,query_on_right;

        switch(Q)
        {
            case query_option::sum :
                query_on_left = query_with_args(query_begin,query_end,left_node,segment_begin,segment_middle,carry+(m_segtree->at(curr_node).propagation));
                query_on_right = query_with_args(query_begin,query_end,right_node,segment_middle+1,segment_end,carry+(m_segtree->at(curr_node).propagation));
                return query_on_left + query_on_right + (length_of(segment_begin,segment_end)*(m_segtree->at(curr_node).propagation));
            case query_option::greater :
                query_on_left = query_with_args(query_begin,query_end,left_node,segment_begin,segment_middle,0);
                query_on_right = query_with_args(query_begin,query_end,right_node,segment_middle+1,segment_end,0);
                return std::max(query_on_left,query_on_right);
            case query_option::lesser :
                query_on_left = query_with_args(query_begin,query_end,left_node,segment_begin,segment_middle,0);
                query_on_right = query_with_args(query_begin,query_end,right_node,segment_middle+1,segment_end,0);
                return std::min(query_on_left,query_on_right);
            default:
                return INT_MAX;     
        }
    }

    template <typename T, cp::query_option Q>
    T constexpr segtree<T,Q>::query(size_t query_begin, size_t query_end) noexcept
    {
        return query_with_args(query_begin,query_end,1,0,size-1,0);
    }
}

int main()
{
    // cp::segtree<int64_t,cp::query_option::sum> a{1,2,3,4};
    // cp::segtree<int64_t,cp::query_option::greater> b{1,2,3,4};
    // cp::segtree<int64_t,cp::query_option::lesser> c{1,2,3,4};
    // std::cout << a.query(0,3) << " " <<  b.query(0,3) << " " << c.query(0,3) << " ";
    // a.update(0,3,3);
    // b.update(1,3,2);
    // c.update(1,3,2);
    // std::cout << a.query(0,3) << " " <<  b.query(0,3) << " " << c.query(0,3);

    std::vector<int> a{1,2,3,4};
    std::array<int,4> b{1,2,3,4};
    cp::segtree<int,cp::query_option::sum> d;
    d = cp::segtree<int,cp::query_option::sum> ({1,2,3});
    std::cout << d.query(0,3) << " ";
    d.update(0,3,2);
    std::cout << d.query(0,3) ;
    return 0;
}