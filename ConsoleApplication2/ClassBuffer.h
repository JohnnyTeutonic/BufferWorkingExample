#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<class T>
class Buffer : std::vector<T>
{
	typedef T value_type;
private:
	int ctr = 0;
	void allocMem(const size_t memsize);
public:
	const size_t capacity; // sets the capacity for the buffer (in terms of number of values passed to the buffer)
	value_type buff_type; // the actual type of buffer i.e. float, int, double, long
	std::string store_type = typeid(value_type).name(); // stores the type of buffer in a string
	Buffer(int capi) : capacity((const size_t)capi) { assertType(); allocMem(capacity); } // constructor will throw an error if non-numeric type passed
	Buffer(const size_t cap) :capacity(cap) { assertType(); allocMem(capacity); } // constructor will throw an error if non-numeric type passed
	Buffer(float _f) { throw "only use integral types!"; }
	Buffer(const Buffer &p1, const size_t cap2) : capacity(cap2) { p1.assertType(); p1.allocMem(capacity); }
	Buffer(const Buffer && p2, size_t cap3) : capacity(std::move(p2.cap3)) { *p2.assertType(); *p2.allocMem(capacity); }
	~Buffer() = default;
	template<class T>
	const T operator[](const T & n)
	{
		if (!(std::is_integral<T>::value)) {
			throw std::runtime_error("Error: can only index using integral types!");
		}
		if (abs(n) > this->size()) {
			throw std::runtime_error("invalid array index");
		}
		// allow for Python-style negative indexing
		if (n < 0) {
			if (n == -1) {
				return this->back();
			}
			return this->at(capacity + n);
		}
		return this->at(n);
	}

	friend std::ostream & operator << (std::ostream & cout, const Buffer<T> &c) // overloaded cout operator
	{
		cout << "\n" << "buffer capacity is " << c.getCapacity() << std::endl;
		cout << "type of buffer is " << c.store_type << std::endl;
		for (auto &i : c) {
			cout << i << std::endl;
		}
		return cout;
	}
	void addElement(T elem);
	void addMultipleElements(T *elems, size_t len);
	void checkCapacity();
	const size_t getCapacity() const;
	bool isNumericType() const;
	void assertType();
};

