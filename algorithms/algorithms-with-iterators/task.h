#include <cstdlib>
#include <iterator>
/*
 * Нужно написать функцию, которая принимает на вход диапазон, применяет к каждому элементу данную операцию и затем складывает результат применения операции в новый диапазон
 * Входной диапазон задан итераторами [firstIn; lastIn)
 * Выходной диапазон начинается с firstOut и имеет такую же длину как входной диапазон
 * Операция является функцией с одним аргументом (унарная функция), возвращающая результат такого типа, который можно положить в OutputIt
 */

template<class InputIt, class OutputIt, class UnaryOperation>
void Transform(InputIt firstIn, InputIt lastIn, OutputIt firstOut, UnaryOperation op) {
    OutputIt result = firstOut;
    while (firstIn!=lastIn) {
        *result++ = op(*firstIn);
        firstIn++;
    }

}

/*
 * Нужно написать функцию, которая принимает на вход диапазон и переставляет элементы в нем таким образом, чтобы элементы,
 * которые удовлетворяют условию p, находились ближе к началу диапазона, чем остальные элементы.
 * Входной диапазон задан итераторами [first; last)
 * p является функцией с одним аргументом (унарная функция), возвращающая результат типа bool
 */
template<class BidirIt, class UnaryPredicate>
void Partition(BidirIt first, BidirIt last, UnaryPredicate p) {
    bool is_okay=false;
    BidirIt i=first;
    BidirIt j=++i;
    i--;
    for(auto i=first;i!=last;i++){
        if(!p(*i)){
            is_okay=true;
        }
    }
    if (is_okay){
        while(j!=last and i!=last) {
            if(p(*j)){
                if(!p(*i)){
                    std::swap(*i,*j);
                    i++;
                }
                else {
                    while(p(*i))
                        i++;
                    std::swap(*i,*j);
                    i++;
                }

            }
            j++;

        }}
}
/*
 * Нужно написать функцию, которая принимает на вход два отстотированных диапазона и объединяет их в новый отсортированный диапазон, содержащий все элементы обоих входных диапазонов.
 */
template<class InputIt1, class InputIt2, class OutputIt>
void Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt firstOut) {
    OutputIt result =firstOut;
    while(first1!=last1 and first2!=last2){
        if (*first1<*first2){
            *result++= *first1++;

        }
        else
            *result++= *first2++;

    }
    while(first1!=last1)
        *result++=*first1++;
    while(first2!=last2)
        *result++=*first2++;

}


/*
 * Напишите класс "диапазон чисел Фибоначчи"
 * Экземпляр класса представляет из себя диапазон от первого до N-го числа Фибоначчи (1, 2, 3, 5, 8, 13 и т.д.)
 * С помощью функций begin и end можно получить итераторы и пробежать по диапазону или передать их в STL-алгоритмы
 */
class FibonacciRange {
public:

    class Iterator {
        friend class FibonacciRange;
    public:
        using value_type = uint64_t;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::input_iterator_tag;
        Iterator(pointer m_ptr):m_ptr(m_ptr){}
        value_type operator *() const {
            // разыменование итератора -- доступ к значению
            return *m_ptr;

        }

        Iterator& operator ++() {
            // prefix increment
            m_ptr++;
            return *this;
        }

        Iterator operator ++(int) {
            // postfix increment
            Iterator copy = *this;
            operator++();
            return copy;

        }

        bool operator ==(const Iterator& rhs) const {
            return rhs.m_ptr==m_ptr;
        }
        bool operator !=(const Iterator& rhs) const {
            return rhs.m_ptr!=m_ptr;
        }

        bool operator <(const Iterator& rhs) const {
            return rhs.m_ptr<m_ptr;
        }

    private:
        pointer m_ptr;

    };

    FibonacciRange(size_t amount): Size_(amount){
        Elements_ = new uint64_t[amount];
        if (amount==1)
            Elements_[0]=1;
        else if (amount==2){
            Elements_[0]=1;
            Elements_[1]=2;
        }
        else{Elements_[0]=1;
            Elements_[1]=2;
            for(size_t i=2;i< amount;i++){
                Elements_[i]=Elements_[i-1]+Elements_[i-2];
            }}
    }

    Iterator begin() const {
        return Iterator(Elements_);
    }

    Iterator end() const {
        return Iterator(Elements_+Size_);
    }

    size_t size() const {
        return Size_;

    }

private:
    uint64_t *Elements_;
    uint64_t Size_;
};
