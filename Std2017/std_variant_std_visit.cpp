#include <iostream>
#include <variant>
#include <string>
using namespace std;

struct TimesTwoVisitor {
  void operator()(int& n)
  {
    n *= 3;
  }

  void operator()(std::string& s)
  {
    s += s;
  }
};

class T1 {
};
class T2 {
};
class T3 {
};

struct Visitor {
  int operator()(T1) { return 0; }
  int operator()(T2) { return 1; }
  int operator()(T3) { return 2; }
  int operator()(T1,T1) { return 3; }
  int operator()(T1,T2) { return 4; }
  int operator()(T1,T3) { return 5; }
  int operator()(T2,T2) { return 6; }
  int operator()(T2,T1) { return 7; }
  int operator()(T2,T3) { return 8; }
  int operator()(T3,T3) { return 9; }
  int operator()(T3,T1) { return 10; }
  int operator()(T3,T2) { return 11; }
};

//  Copied from, /usr/local/include/c++/7.3.0/variant 
  template<typename _Visitor, typename... _Variants>
    constexpr decltype(auto)
    Visit(_Visitor&& __visitor, _Variants&&... __variants)
    {
      if ((__variants.valueless_by_exception() || ...))
        __throw_bad_variant_access("Unexpected index");

      using _Result_type =
        decltype(std::forward<_Visitor>(__visitor)(
            get<0>(std::forward<_Variants>(__variants))...));

      constexpr auto& __vtable = __detail::__variant::__gen_vtable<
        _Result_type, _Visitor&&, _Variants&&...>::_S_vtable;

      auto __func_ptr = __vtable._M_access(__variants.index()...);
      return (*__func_ptr)(std::forward<_Visitor>(__visitor),
                           std::forward<_Variants>(__variants)...);
    }


int main()
{
  std::variant<int, std::string> v = 2;
  std::visit(TimesTwoVisitor{}, v);
  std::visit([](const auto& x) { std::cout << x << std::endl; }, v);

  v = std::string{"Hello"};
  std::visit(TimesTwoVisitor{}, v);
  std::visit([](const auto& x) { std::cout << x << std::endl; }, v);


 std::variant<T1, T2, T3> v1;
 std::variant<T1, T2, T3> v2;
 int result;
 T2 obj2;
 T3 obj3;

 v1 = obj2;
 //result = std::visit(Visitor{}, v1);
 result = Visit(Visitor{}, v1);
 std::cout << result<< std::endl;

 v1 = obj3;
 result = std::visit(Visitor{}, v1);
 std::cout << result<< std::endl;

/*
It is also possible to call the corresponding function with each value held by multiple objects as an argument. In that case, all possible combinations must be defined as overloads. This is because the instantiation that calls the overload is done at compile time.*/
 v1 = obj2;
 v2 = obj3;
 result = std::visit(Visitor{},v1,v2);
 std::cout << result<< std::endl;

  return 0;
}
