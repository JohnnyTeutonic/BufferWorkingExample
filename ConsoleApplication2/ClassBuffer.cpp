// BufferApplication.cpp : This is example code to create a buffer class
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <list>
#include <functional>

using namespace std;

template<class T>
class Buffer : vector<T> {
	typedef T value_type;
private:
	int ctr = 0; // this global counter will be used to ensure the capacity of the buffer remains the same	
	void allocMem(const size_t memsize) {
		this->reserve(capacity); // allocates enough memory for the buffer but without initializing it
	}
	void checkCapacity() {
		if (ctr >= capacity) {
			cout << "removing first element: " << this->at(0) << endl;
			this->erase(this->begin()); // removes first element of buffer
		}
	};

public:
	const size_t capacity; // sets the capacity for the buffer (in terms of number of values passed to the buffer)
	value_type buff_type; // the actual type of buffer i.e. float, int, double, long
	string store_type = typeid(buff_type).name(); // stores the type of buffer in a string
	Buffer(const size_t cap) :capacity(cap) { this->assertType(); this->allocMem(capacity); } // constructor will throw an error if non-numeric type passed
	Buffer(const int cap) :capacity(cap) { this->assertType(); this->allocMem(capacity); } // constructor will throw an error if non-numeric type passed
	Buffer(float _f) { throw "only use integral types!"; }
	Buffer(const Buffer &p1, const size_t cap2) :capacity(cap2) { p1.assertType(); p1.allocMem(capacity); }
	Buffer(const Buffer &&p2, const size_t cap3) noexcept :capacity(move(p2.cap3)) { p2.assertType(); p2.allocMem(capacity); }

	~Buffer() = default;

	size_t getCapacity() const { // capacity getter function
		return capacity;
	}


	friend ostream & operator << (ostream &out, const Buffer &c) // overloaded cout operator
	{
		out << "\n" << "buffer capacity is " << c.getCapacity() << endl;
		out << "type of buffer is " << c.store_type << endl;
		for (auto &i : c) {
			out << i << endl;
		}
		return out;
	}

	template <class U>
	value_type& operator[](const U & n)
	{
		if (!(is_integral<U>::value)) {	
			throw runtime_error("Error: can only index using integral types!");
		}
		if (abs(n) > (this->size())+1) {
			throw runtime_error("invalid array index");
		}
		// allow for Python-style negative indexing
		if (n < 0) {
			return this->at(capacity + n);
		}
		return this->at(n);
	}
		
	template<class V>
	void addElement(const V elem) {
		if (is_same_v<V, value_type>) { // ensure that new elements are of the same type of the buffer
			checkCapacity();
			this->push_back(elem);
			ctr++;
		}
		else {
			cout << "ensure same element type is added " << endl;
		}
	}

	void addMultipleElements(T *elems, const size_t len) { // allows for adding multiple elements simultaneously
		for (auto i = 0; i < len; ++i) {
			this->addElement(*elems);
			elems++;
		}
	}


	bool isNumericType() { // only accepts arithmetic types
		return is_arithmetic<decltype(buff_type)>::value;
	}

	void assertType() { // ensures that only numeric types are accepted by the buffer constructor
		if (isNumericType() == 0) {
			cout << "must be numeric type!" << endl;
			throw invalid_argument("must be numeric!");
		}
	}

	void onNewData(T *newdata, size_t dataSize) {
		this->allocMem(capacity + dataSize);
		copy(newdata, capacity + dataSize, back_inserter(this));
		//this->assign(newdata, capacity + dataSize);
	}

	bool isOdd(T elem) {
		if (elem % 2 == 0) {
			return false;
		}
		return true;
	}

	list<T> MyListFunction(list<T> ls, std::function<bool(T)> myfunc) {
		list<T> odd_nums;
		for (auto &i : ls) {
			if (myfunc(i)) {
				odd_nums.push_back(i);
			}
		}
		return odd_nums;
	}
	template <class T>
	typedef list<T>(Buffer<T>::*MyListFunction)(list<T> ls, std::function<bool(T)> myfunc)
	
};

int main()
{
	Buffer<int> g(5);
	list<int> h {3, 1, 4, 7, 9};
	auto abc = g.isOdd;
	g.MyListFunction(h, abc);
	typedef bool (Buffer<int>::*isOdd)(int elem);
	isOdd p = &Buffer<int>::isOdd;
	bool (Buffer<int>::* ptfptr) (int) = &Buffer<int>::isOdd;

	Buffer<double> bt(6);
	bt.addElement(50.3);
	bt.addElement(12.22);
	bt.addElement(15.33);
	bt.addElement(27.33);
	bt.addElement(37.33);
	bt.addElement(28.33);
	bt.addElement(38.33);
	cout << "first " << bt[0] << endl;
	cout << "second " << bt[1] << endl;
	cout << "third " << bt[2] << endl;
	cout << "fourth " << bt[3] << endl;
	cout << "last " << bt[-1] << endl; //shows how negative indexing works
	cout << "second last " << bt[-2] << endl; //shows how negative indexing works
	cout << "last " << bt[5] << endl; //shows how negative indexing works
	cout << "out " << bt[6] << endl; 
	Buffer<int> buf(4);
	buf.addElement(12);
	buf.addElement(13);
	buf.addElement(14);
	buf.addElement(15);
	buf.addElement(1666.3F);
	cout << buf << endl;
	cout << "last " << buf[-1] << endl; //shows how negative indexing works
	buf.addElement(12);
	cout << buf << endl;
	buf.addElement(22);
	cout << buf << endl;
	Buffer<float> buf2(4);
	buf2.addElement(101.33f);
	buf2.addElement(133.55f);
	buf2.addElement(1544.5553f);
	buf2.addElement(1880.44f);
	cout << buf2 << endl;
	buf2.addElement(23.55555f);
	cout << buf2 << endl;
	buf2.addElement(63.2311f);
	cout << buf2 << endl;
	cout << "last element " << buf2[-1] << endl; // more demonstrations of negative indexing
	cout << "second last element is " << buf2[-2] << endl;
	cout << "third last element is " << buf2[-3] << endl;
	cout << "fourth last element is " << buf2[-4] << endl;

	Buffer<long> buf3(12);
	for (auto i = 0; i < buf3.capacity; ++i) {
		cout << rand() % 100 << endl;
		buf3.addElement(long(rand() % 100));
	}
	cout << buf3 << endl;
	long arr[3] = { 555L, 122L, 557L };
	buf3.addMultipleElements(arr, 3); //add in multiple elements
	cout << buf3 << endl;
	buf3.addElement(1232.222F);

	Buffer<short> buf4(20);
	for (auto i = 0; i < buf4.capacity; ++i) {
		buf4.addElement(short(rand() % 100));
	}
	cout << buf4 << endl;
	cout << "second last elem of array is " << buf4[-2] << " and last elem of array is " << buf4[-1] << endl;
	short* arr2 = (short*)malloc(sizeof(short) * 2);
	*arr2 = (short)23;
	*(arr2 + short(1)) = (short)31;
	cout << "ptr 1 contains " << *arr2 << " and ptr2 contains " << *(arr2 + 1) << endl;
	buf4.addMultipleElements(arr2, 2);
	free(arr2);
	Buffer<long int> buf5(7);
	long int* arr3 = new long int[5];
	for (auto i = 0; i < 5; ++i) {
		*(arr3 + i) = (long int)(rand() % 100);
	}
	buf5.addMultipleElements(arr3, 5);
	cout << buf5 << endl;
	delete[] arr3;
	Buffer<int> buf6(150000000);
	for (auto i = 0; i < buf6.capacity; ++i) {
		buf6.addElement(rand() % 1000);
	}
	cout << buf6[0] << endl;
	cout << buf6[155535] << endl;
	cout << buf6[-165] << endl;
	cout << "elem to watch " << buf6[35555555] << endl;
	Buffer<int> copier = buf6;
	cout << "elem copied " << copier[35555555] << endl;
	Buffer<int> * bufptr = new Buffer<int>(10);
	int elems[10] = { 3,5,2,6,7,3,25,55,99,1555 };
	bufptr->addMultipleElements(elems, 10);
	cout << *bufptr << endl;
	delete bufptr;
	//********************.*******************************************************************************//
	// uncomment below line to see what happens if you index outside of the bounds of the buffer
	// buf5[-10] // calling a non-existent index will throw an error
	// uncomment below line to see what happens if you instantiate a buffer of a non-numeric type
	//Buffer<string> blong(4);
	// uncomment below line to see what happens when you try indexing with a non-integral type
	//buf5[3.333]; 
	// uncomment below line to see what happens when you try instantiating with a negative value
	//Buffer<double> btA(-3);

	//***************************************************************************************************//
}
