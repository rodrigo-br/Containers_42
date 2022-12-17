#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

		typedef	T												value_type;
		typedef	Allocator										allocator_type;
		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename ft::random_access_iterator<value_type>	iterator;
		typedef
		typename ft::random_access_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	protected:
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		pointer			_data;

	public:

/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

		explicit vector(const allocator_type &alloc = allocator_type()) :
			_alloc(alloc), _size(0), _capacity(0), _data(NULL) {};

		explicit vector(size_type size,
						const value_type &value = value_type(),
						const allocator_type &alloc = allocator_type()) :
			_alloc(alloc), _size(0), _capacity(size), _data(_alloc.allocate(_capacity)) {
				for (size_type i = 0; i < _capacity; i++) {
					_alloc.construct(&_data[i], value);
					_size++;
				}
			};

		template<class InputIt>
		vector(InputIt first, InputIt last,
        		const allocator_type &alloc = allocator_type()) :
			_alloc(alloc), _size(0), _capacity(last - first), _data(_alloc.allocate(_capacity)) {
				for (size_type i = 0; i < _capacity; i++) {
					_alloc.construct(&_data[i], *(first + i));
					_size++;
				}
			};

		~vector() { _alloc.deallocate(_data, _capacity); };

/******************************************************************************/
/*								Operators								      */
/******************************************************************************/

		vector& operator=(const vector& other) {
			this->clear();
			_alloc = other.get_allocator();
			_alloc.deallocate(_data, _capacity);
			_size = other.size();
			_capacity = other.capacity();
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(&_data[i], other[i]);
			}
			return *this;
		};

		const_reference operator[](size_type index) const {
			return _data[index];
		};

		reference operator[](size_type index) {
			return _data[index];
		};

		// template<value_type, Allocator>
		// bool operator==(const ft::vector<value_type,Allocator>& lhs, const ft::vector<value_type,Allocator>& rhs) {
		// 	if (lhs.size() != rhs.size())
		// 		return (false);
		// 	return (true);
		// }

/******************************************************************************/
/*								Capacity								      */
/******************************************************************************/

		void reserve(size_type new_cap) {
			if (new_cap > max_size()) { throw std::length_error(""); }
			if (new_cap <= _capacity) { return ; }
			value_type *newData;
			newData = _alloc.allocate(new_cap);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(&newData[i], _data[i]);
			}
			_alloc.deallocate(_data, _capacity);
			_data = newData;
			_capacity = new_cap;
		};

		size_type size(void) const { return _size; };

		size_type capacity(void) const { return _capacity; };

		size_type max_size(void) const { return _alloc.max_size(); };

		bool empty(void) const { return static_cast<bool>(!_size); };

		void shrink_to_fit(void) {
			_capacity = _size;
		};

		void resize (size_type n, value_type val = value_type()) {
			value_type *newData;
			newData = _alloc.allocate(n);
			size_type max_size = n > _size ? _size : n;
			_size = 0;
			for (size_type i = 0; i < max_size; i++) {
				_alloc.construct(&newData[i], _data[i]);
				_size++;
			}
			if (_size < n) {
				for (size_type i = _size; i < n; i++) {
					_alloc.construct(&newData[i], val);
					_size++;
				}
			}
			_alloc.deallocate(_data, _capacity);
			_data = newData;
			if (n > _capacity)
				_capacity = n;
		};

/******************************************************************************/
/*								Modifiers								      */
/******************************************************************************/

		void clear(void) {
			_alloc.destroy(_data);
			_size = 0;
		};

		void push_back(const value_type& val) {
			if (_size + 1 > _capacity) {
				_capacity ? _capacity *= 2 : _capacity++;
				pointer tmp = _alloc.allocate(_capacity);
				if (tmp == NULL) {
					throw std::bad_alloc();
				}
				for (size_t i = 0; i < _size; i++) {
					_alloc.construct(tmp + i, _data[i]);
					_alloc.destroy(_data + i);
				}
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
			}
			_alloc.construct(_data + _size, val);
			_size++;
		}

/******************************************************************************/
/*								Allocator								      */
/******************************************************************************/

		allocator_type get_allocator(void) const { return _alloc; };

/******************************************************************************/
/*								Element access								  */
/******************************************************************************/

		reference at (size_type n) { return _data[n]; };

		const_reference at (size_type n) const { return _data[n]; };

		reference front(void) { return _data[0]; };
		
		const_reference front(void) const { return _data[0]; };

		reference back(void) { return _data[_size - 1]; };
		
		const_reference back(void) const { return _data[_size - 1]; };

		value_type* data(void) { return _data; };
		
		const value_type* data(void) const { return _data; };

/******************************************************************************/
/*								Iterators								      */
/******************************************************************************/

		iterator begin() { return iterator(_data); };

		const_iterator begin() const { return iterator(_data); };

		iterator end() { return iterator(_data + _size); };

		const_iterator end() const { return iterator(_data + _size); };

		reverse_iterator rbegin(void) {	return reverse_iterator(end()); };

		const_reverse_iterator rbegin(void) const {	return const_reverse_iterator(end()); };

		reverse_iterator rend(void) {	return reverse_iterator(begin()); };

		const_reverse_iterator rend(void) const {	return const_reverse_iterator(begin()); };
	};
};//namespace ft


#endif