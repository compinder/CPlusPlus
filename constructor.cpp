#include<iostream>
using namespace std;

class base{
private:
int *ii;
string ss;
public:
base() = default;
base(const base &other) = delete; 
base operator=(const base &other) = delete;

void assign_pelm(int d1){
  ii = new int;
  *ii = d1+2;
}

void print()
{
  cout << "ii = "<<*ii << endl;
}
};

int main()
{
base obj1;
obj1.assign_pelm(2);
obj1.print();
base obj2 = obj1; // error: copy constructure has delete keyword, 
                  // it means can not create object having copy const.
base obj3;
obj3 = obj1; // error: type has delete keyword for assignment operator.
return 0;
}


