// BufferApplication.cpp : This is example code to create a buffer class for Ideas At Sea by Jonathan Reich
#include "ClassBuffer.h"
using namespace std;

template<class T>
void Buffer<T>::allocMem(const size_t memsize) {
	Buffer<T>::reserve(memsize);
}
template<class T>
void Buffer<T>::checkCapacity() {
	if (Buffer<T>::ctr >= Buffer<T>::capacity) {
		cout << "removing first element: " << this->at(0) << endl;
		Buffer<T>::erase(Buffer<T>::begin()); // removes first element of buffer
	}
}

template<class T>
void Buffer<T>::addElement(const T elem) {
	if (is_same_v<T, value_type>) { // ensure that new elements are of the same type of the buffer
		this->checkCapacity();
		this->push_back(elem);
		ctr++;
	}
	else {
		cout << "ensure same element type is added " << endl;
	}
}

template <class T>
void Buffer<T>::addMultipleElements(T *elems, const size_t len) { // allows for adding multiple elements simultaneously
	for (auto i = 0; i < len; ++i) {
		addElement(*elems);
		elems++;
	}
}

template <class T>
bool Buffer<T>::isNumericType() const { // only accepts arithmetic types
	return is_arithmetic<decltype(buff_type)>::value;
}


template <class T>
void Buffer<T>::assertType() { // ensures that only numeric types are accepted by the buffer constructor
	if (this->isNumericType() == 0) {
		cout << "must be numeric type!" << endl;
		throw invalid_argument("must be numeric!");
	}
}

template<class T>
const size_t Buffer<T>::getCapacity() const
{
	return capacity;
}

int main()
{

	Buffer<double> bt(3);
	bt.addElement(50.3);
	bt.addElement(12.22);
	bt.addElement(15.33);
	cout << "first " << bt[0] << endl;
	cout << bt << endl;
	bt.addElement(222.333);
	cout << bt << endl;
	vector<Buffer<double>> vec;
	vec.push_back(Buffer<double>{10});
	Buffer<double> b_copy = bt;
	cout << bt << endl;
	cout << b_copy << endl;
	bt.addElement(17.55);
	cout << bt << endl;
	cout << "first " << bt[0] << endl;
	cout << "second " << bt[1] << endl;
	cout << "last " << bt[-1] << endl; //shows how negative indexing works
	Buffer<long> buf(4);
	buf.addElement(12);
	buf.addElement(13);
	buf.addElement(14);
	buf.addElement(15);
	buf.addElement(1666.3F);
	cout << buf << endl;
	cout << "last " << buf[-1] << endl; //shows how negative indexing works
	cout << "second last " << buf[-2] << endl; //shows how negative indexing works
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
	cout << "first element " << buf2[0] << endl; // more demonstrations of negative indexing
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
