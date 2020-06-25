// Below is the solution by using vector<Based*> vect,
// Base *pBase , and initialized pBase with
// with the address of derived which is
// of type Derived

#include <iostream>
#include <vector>

using namespace std;

struct TestC {
	int x;
};

class Base
{

public:

virtual void identify ()
{
    cout << "BASE" << endl;
}
};

class Derived: public Base
{
	TestC * _test;
public:
Derived(TestC * test) {
	_test = test;
}
virtual void identify ()
{
    cout << "DERIVED" << endl;
}
};

class Derived2: public Base
{
	TestC * _test;
public:
Derived2(TestC * test) {
	_test = test;
}
virtual void identify ()
{
    cout << "DERIVED2" << endl;
}
};

int main ()

{
TestC * myTest = new TestC;
Derived * derived1 = new Derived(myTest);
Derived2 * derived2 = new Derived2(myTest);
// PBase is initialized with the address of derived which is
// of type Derived

// Store pointer to object of Base class in the vector:
vector<Base*> vect;
// Add an element to vect using pBase which is initialized with the address
// of derived
vect.push_back(derived1);
vect.push_back(derived2);
vect[0]->identify();
vect[1]->identify();
delete vect[0];
delete vect[1];
delete myTest;
return 0;
}
