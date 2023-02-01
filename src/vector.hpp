#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>
#include <memory>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include "iterator_traits.hpp"
#include "Container.hpp"
#include "algorithm.hpp"

namespace ft {
#define CONTAINER Container<T, Allocator>
	template<class T, class Allocator = std::allocator<T> >
	class vector : public CONTAINER
	{
	public:
		IMPORT_TYPE(value_type);
		IMPORT_TYPE(allocator_type);
		IMPORT_TYPE(size_type);
		IMPORT_TYPE(difference_type);
		IMPORT_TYPE(reference);
		IMPORT_TYPE(const_reference);
		IMPORT_TYPE(pointer);
		IMPORT_TYPE(const_pointer);
		typedef ft::random_access_iterator<pointer>			iterator;
		typedef ft::random_access_iterator<const_pointer>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	protected:
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		pointer			_data;
		

	public:

/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

		/**
		 * @brief Empty constructor
		 * 
		 * @param alloc default
		 */
		explicit vector(const allocator_type &alloc = allocator_type()) :
			_alloc(alloc), _size(0), _capacity(0), _data(_alloc.allocate(0)) {};


		explicit vector(size_type size,
						const value_type &value = value_type(),
						const allocator_type &alloc = allocator_type()) :
			_alloc(alloc), _size(0), _capacity(size) {
				if (size > max_size()) { throw std::length_error("cavalinho"); }
				_data = _alloc.allocate(_capacity);
				if (!_data) { throw std::bad_alloc(); }
				for (size_type i = 0; i < _capacity; i++) {
					_alloc.construct(&_data[i], value);
					_size++;
				}
			};

		template<class InputIt>
		vector(InputIt first, InputIt last,
        		const allocator_type &alloc = allocator_type(),
				typename enable_if<!is_integral<InputIt>::value>::type* = 0) :
				_alloc(alloc), _size(0), _capacity(0), _data(_alloc.allocate(0)) {
					assign(first, last);
				};

		/**
		 * @brief Copy constructor
		 * 
		 * @param other another vector to be copied
		 */
		vector(const vector &other) : _alloc(other.get_allocator()),
			_size(other.size()), _capacity(other.capacity()) {
				_data = _alloc.allocate(_capacity);
				if (!_data) { throw std::bad_alloc(); }
				std::uninitialized_copy(other.begin(), other.end(), _data);
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
			if (!_data) { throw std::bad_alloc(); }
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(&_data[i], other[i]);
			}
			return *this;
		};

		const_reference operator[](size_type index) const {
			if (index >= _size) { throw std::out_of_range("cavalinho"); }
			return _data[index];
		};

		reference operator[](size_type index) {
			if (index >= _size) { throw std::out_of_range("cavalinho"); }
			return _data[index];
		};

/******************************************************************************/
/*								Capacity								      */
/******************************************************************************/

		void reserve(size_type new_cap) {
			if (new_cap > max_size()) { throw std::length_error("cavalinho"); }
			if (new_cap <= _capacity) { return ; }

			pointer newData = _alloc.allocate(new_cap);
			if (!newData) { throw std::bad_alloc(); }
			std::uninitialized_copy(begin(), end(), newData);
			for (size_type i = 0; i < _size; i++) {
				_alloc.destroy(&_data[i]);
			}
			_alloc.deallocate(_data, _capacity);
			_data = newData;
			_capacity = new_cap;
		}

		size_type size(void) const { return _size; };

		size_type capacity(void) const { return _capacity; };

		size_type max_size(void) const { return _alloc.max_size(); };

		bool empty(void) const { return _size == 0; };

		void shrink_to_fit(void) { _capacity = _size; };

		/**
		 * @brief Resizes the container so that it contains n elements.
		 * If n is smaller than the current container size, the content is reduced
		 * to its first n elements, removing those beyond (and destroying them).
		 * If n is greater than the current container size, the content is expanded
		 * by inserting at the end as many elements as needed to reach a size of n.
		 * If n is also greater than the current container capacity,
		 * an automatic reallocation of the allocated storage space takes place.
		 * Notice that this function changes the actual content of the container
		 * by inserting or erasing elements from it.
		 * 
		 * @param n new number of elements in the container
		 * @param val If val is specified, the new elements are initialized as
		 * copies of val, otherwise, they are value-initialized.
		 */
		void resize (size_type n, value_type val = value_type()) {
			value_type *newData;
			newData = _alloc.allocate(n);
			if (!newData) { throw std::bad_alloc(); }
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

		/**
		 * @brief Destroy all the elements of the vector and set the size to 0.
		 * 
		 */
		void clear(void) {
			for (iterator it = begin(); it != end(); it++) {
				_alloc.destroy(it.base());
			}
			_size = 0;
		};

		/**
		 * @brief Inserts a new element at the end of the vector, after its current
		 * last element.
		 * 
		 * @param val Value to be copied (or moved) to the new element.
		 */
		void push_back(const value_type& val) {
			insert(end(), val);
		};

		/**
		 * @brief Removes the last element in the vector
		 * 
		 */
		void pop_back(void) {
			erase(end() - 1);
		};

		/**
		 * @brief Moves the contents from position + 1, end() to position, end() -1
		 * and destroys the last element.
		 * 
		 */
		iterator erase(iterator position) {
			if (position == end())
				return position;
			std::copy(position + 1, end(), position);
			_alloc.destroy(end().base());
			_size--;
			return position;
		};

		iterator erase(iterator first, iterator last) {
			if (first == end() || first == last)
				return first;
			iterator return_iterator = first;
			std::copy(last.base(), end().base(), first.base());
			if (!ft::is_integral<value_type>::value) {
				while (first != end()) {
					_alloc.destroy(first.base());
					_size--;
					first++;
				}
			}
			return return_iterator;
		};

		/**
		 * @brief assigns new contents to the vector, replacing its current contents,
		 * and modifying its size accordingly.
		 * 
		 */
		void assign(size_type n, const value_type& val) {
			clear();
			for (size_type i = 0; i < n; i++) {
				push_back(val);
			}
		};

		/**
		 * @brief Assigns new contents to the vector, replacing its current contents,
		 * and modifying its size accordingly.
		 * The use of enable_if is to avoid the function to be called when the
		 * iterator is an integral type.
		 * 
		 */
		template <class Iterator>
		typename enable_if<!is_integral<Iterator>::value, void>::type
		assign(Iterator first, Iterator last) {
			_assign(first, last, typename iterator_traits<Iterator>::iterator_category());
		};

		/**
		 * @brief Auxiliar assign' function for random access iterators.
		 * 
		 */
		template <class Iterator>
		void _assign(Iterator first, Iterator last, std::input_iterator_tag) {
			clear();
			while (first != last) {
				push_back(*first);
				first++;
			}
		};

		/**
		 * @brief If the allocators are the same, swap the attributes of the vectors.
		 * Use trivial swap otherwise.
		 * 
		 */
		void swap (vector& x) {
			if (this == &x) { return ;}
			if (_alloc == x._alloc) {
				std::swap(_size, x._size);
				std::swap(_capacity, x._capacity);
				std::swap(_data, x._data);
			}
			else { std::swap(*this, x); }
		};

		iterator insert(iterator pos, const T& value) {
			size_type index = pos - begin();
			if (_size + 1 > _capacity) {
				reserve(_size + 1);
			}
			for (size_type i = _size; i >= index && i-- > 0;) {
				_alloc.construct(&_data[i + 1], _data[i]);
				_alloc.destroy(&_data[i]);
			}
			_alloc.construct(&_data[index], value);
			_size++;
			return begin() + index;
		};

		iterator insert(iterator pos, size_type count, const T& value) {
			size_type index = pos - begin();
			if (_size + count > _capacity) {
				reserve(_size + count);
			}
			for (size_type i = _size; i >= index && i-- > 0;) {
				_alloc.construct(&_data[i + count], _data[i]);
				_alloc.destroy(&_data[i]);
			}
			for (size_type i = index; i < index + count; i++) {
				_alloc.construct(&_data[i], value);
			}
			_size += count;
			return begin() + index;
		};

		template<class InputIt>
		iterator insert(iterator pos, InputIt first, InputIt last,
						typename enable_if<!is_integral<InputIt>::value>::type* = 0) {
			size_type index = pos - begin();
			if (_size + (last - first) > _capacity) {
				reserve(_size + (last - first));
			}
			for (size_type i = _size; i >= index && i-- > 0;) {
				_alloc.construct(&_data[i + (last - first)], _data[i]);
				_alloc.destroy(&_data[i]);
			}
			while (first != last) {
				_alloc.construct(&_data[index], *first);
				first++;
				index++;
				_size++;
			}
			return begin() + index;
		};


/******************************************************************************/
/*								Allocator								      */
/******************************************************************************/

		allocator_type get_allocator(void) const { return _alloc; };

/******************************************************************************/
/*								Element access								  */
/******************************************************************************/

		reference at (size_type n) { 
			if (n >= _size) { throw std::out_of_range("cavalinho"); }
			return _data[n]; 
		};

		const_reference at (size_type n) const {
			if (n >= _size) { throw std::out_of_range("cavalinho"); }
			return _data[n]; 
		};

		reference front(void) {
			if (_size == 0) { throw std::out_of_range("cavalinho"); }
			return _data[0];
		};
		
		const_reference front(void) const { 
			if (_size == 0) { throw std::out_of_range("cavalinho"); }
			return _data[0]; 
		};

		reference back(void) {
			if (_size == 0) { throw std::out_of_range("cavalinho"); }
			return _data[_size - 1];
		};
		
		const_reference back(void) const {
			if (_size == 0) { throw std::out_of_range("cavalinho"); }
			return _data[_size - 1];
		};

		value_type* data(void) { return _data; };
		
		const value_type* data(void) const { return _data; };

/******************************************************************************/
/*								Iterators								      */
/******************************************************************************/

		iterator begin() { return iterator(_data); };

		const_iterator begin() const { return const_iterator(_data); };

		iterator end() { return iterator(_data + _size); };

		const_iterator end() const { return const_iterator(_data + _size); };

		reverse_iterator rbegin(void) {	return reverse_iterator(end()); };

		const_reverse_iterator rbegin(void) const {	return const_reverse_iterator(end()); };

		reverse_iterator rend(void) { return reverse_iterator(begin()); };

		const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); };
	};//class vector
	#undef CONTAINER

/******************************************************************************/
/*							Non-Member Functions							  */
/******************************************************************************/

		template<class T>
		bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		};

		template<class T>
		bool operator!=(const vector<T>& lhs, const vector<T>& rhs) {
			return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		};

		template<class T>
		bool operator<(const vector<T>& lhs, const vector<T>& rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		};

		template<class T>
		bool operator>(const vector<T>& lhs, const vector<T>& rhs) {
			return rhs < lhs;
		};

		template<class T>
		bool operator<=(const vector<T>& lhs, const vector<T>& rhs) {
			return !(rhs < lhs);
		};

		template<class T>
		bool operator>=(const vector<T>& lhs, const vector<T>& rhs) {
			return !(lhs < rhs);
		};

		template<class T>
		void swap(vector<T>& lhs, vector<T>& rhs) { lhs.swap(rhs); };


}; // namespace ft

#endif