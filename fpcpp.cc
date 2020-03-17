#include <type_traits>
#include <iostream>


template<typename T>
struct tuple{
    T t;
    tuple(T &init):t{init}{};
};

template<typename T, int Size>
struct list:list<T, Size-1>{
    const T head;
    using super = list<T, Size-1>;
    super tail(){
        return static_cast<super>(*this);} 
    list(T h, const super & s):super(s),head{h}{}
};

template<typename T>
struct list<T, 0>{
};

template<typename T, int Size>
list<T, Size+1> operator+(const T t, const list<T,Size> &l) {
   return list<T, Size+1>(t, l);
}

template<typename T, int Size>
void print(const list<T,Size> &l) {
    std::cout << l.head << " ";
    print(static_cast<list<T, Size-1>>(l));
}

template<typename T>
void print(const list<T,1> &l) {
    std::cout << l.head << std::endl;
}

template<int size>
constexpr list<int, size>range(){
        return size + range<size-1>();
}

template<>
constexpr list<int, 0>range<0>(){
    return list<int,0>{};
}

template<bool B, typename T=void>
using enable_if_t = typename std::enable_if<B,T>::type;

template<typename T, typename F, int Size, enable_if_t<Size!=1, int> =0 >
list<T, Size> map(F f, list<T, Size> &l){
    auto a = l.tail();
    return f(l.head) + map(f, a);
} 

template<typename T, typename F, int Size, enable_if_t<Size==1, int> =0 >
list<T, 1> map(F f, list<T, Size> &l){
    return f(l.head) + list<T, 0>{};
} 

int main(){

    auto l = range<100>();
    auto f = map([](int x){return x*2;}, l);
    print(f);
}
