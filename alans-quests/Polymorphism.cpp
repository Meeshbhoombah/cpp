// Polymorphism.cpp: Test polymorphic method overriding and calling in C++

#include <iostream>

using namespace std;

class Base {
public:
	virtual void method() {
		cout << "Base::method (should not be called)" << endl;
	}
};

class Child : public Base {
public:
	// override is a C++11 keyword: compile with g++ -std=c++11
	virtual void method() { // override {
		cout << "Child::method" << endl;
	}
};

class HasCopy {
private:
	Base m_base;
public:
	HasCopy(Base base) : m_base(base) {}
	void callMethod() {
		m_base.method();
	}
};

class HasRef {
private:
	Base& m_base;
public:
	HasRef(Base& base) : m_base(base) {}
	void callMethod() {
		m_base.method();
	}
};

class HasPtr {
private:
	Base *m_base;
public:
	HasPtr(Base *base) : m_base(base) {}
	void callMethod() {
		m_base->method();
	}
};

void testCopy() {
	cout << "Testing calling Child::method via HasCopy (by copying):" << endl;
	Child child;
	child.method();       // prints "Child::method" (as expected)
	HasCopy hasCopy(child);
	hasCopy.callMethod(); // prints "Base::method" (NOT expected)
	// child and hasCopy will be deleted when exiting this function scope
}

void testRef() {
	cout << "Testing calling Child::method via HasRef (by reference):" << endl;
	Child child;
	child.method();       // prints "Child::method" (as expected)
	HasRef hasRef(child);
	hasRef.callMethod();  // prints "Child::method" (as expected)
	// child and hasRef will be deleted when exiting this function scope
}

void testPtr() {
	cout << "Testing calling Child::method via HasPtr (by pointer):" << endl;
	Child *child = new Child();
	child->method();      // prints "Child::method" (as expected)
	HasPtr hasPtr(child);
	hasPtr.callMethod();  // prints "Child::method" (as expected)
	delete child;
	// hasPtr will be deleted when exiting this function scope
}

void testUnsafePtr() {
	cout << "Testing calling Child::method via HasPtr (by unsafe pointer):" << endl;
	Child child;
	child.method();        // prints "Child::method" (as expected)
	HasPtr hasPtr(&child); // this stack memory address is unsafe to use
	hasPtr.callMethod();   // prints "Child::method" (as expected)
	// child and hasPtr will be deleted when exiting this function scope
}

int main() {
	testCopy();
	testRef();
	testPtr();
	testUnsafePtr();
	return 0;
}
