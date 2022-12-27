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
			_alloc(alloc), _size(0), _capacity(0), _data(_alloc.allocate(0)) {};


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
        		const allocator_type &alloc = allocator_type(),
				typename enable_if<!is_integral<InputIt>::value>::type* = 0) :
				_alloc(alloc), _size(0), _capacity(0), _data(_alloc.allocate(0)) {
					assign(first, last);
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

/******************************************************************************/
/*								Capacity								      */
/******************************************************************************/

		void reserve(size_type new_cap) {
			if (new_cap > max_size()) { throw std::length_error("cavalinho"); }
			if (new_cap <= _capacity) { return ; }

			pointer newData = _alloc.allocate(new_cap);
			std::uninitialized_copy(_data, _data + _size, newData);

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
			erase(begin(), end());
		};

		void push_back(const value_type& val) {
			if (_capacity == 0) { reserve(1); }
			else if (_size + 1 > _capacity) {
				reserve(_capacity * 2);
			}
			_alloc.construct(&_data[_size], val);
			_size++;
		};

		void pop_back(void) {
			if (_size == 0)
				return ;
			_size--;
			_alloc.destroy(&_data[_size]);
		};

		iterator erase(iterator position) {
			iterator return_iterator = position;
			iterator copy_iterator = position;
			size_type i = 0;
			for (; i < _size; i++) {
				if (copy_iterator == position) {
					if (!ft::is_integral<value_type>::value)
						_alloc.destroy(&_data[i]);
					break ;
				}
			}
			if (i < _size) {
				while (copy_iterator != (end() - 1)) {
					position++;
					*copy_iterator = *position;
					copy_iterator++;
				}
				_size--;
			}
			return return_iterator;
		};

		iterator erase(iterator first, iterator last) {
			if (first == end())
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

		void assign(size_type n, const value_type& val) {
			clear();
			for (size_type i = 0; i < n; i++) {
				push_back(val);
			}
		};

		template <class Iterator>
		typename enable_if<!is_integral<Iterator>::value, void>::type
		assign(Iterator first, Iterator last) {
			_assign(first, last, typename iterator_traits<Iterator>::iterator_category());
		};

		template <class Iterator>
		void _assign(Iterator first, Iterator last, std::input_iterator_tag) {
			clear();
			while (first != last) {
				push_back(*first);
				first++;
			}
		};

		void swap (vector& x) {
			size_type	temp_size = x._size;
			size_type	temp_capacity = x._capacity;
			pointer		temp_data = x._data;

			x._size = _size;
			x._capacity = _capacity;
			x._data = _data;

			_size = temp_size;
			_capacity = temp_capacity;
			_data = temp_data;
		}

		iterator insert(const_iterator pos, const T& value) {
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

		iterator insert(const_iterator pos, size_type count, const T& value) {
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
		iterator insert(const_iterator pos, InputIt first, InputIt last,
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
	};//class vector
	#undef CONTAINER

/******************************************************************************/
/*							Non-Member Functions							  */
/******************************************************************************/

		template<class T>
		bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
			return equal(lhs.begin(), lhs.end(), rhs.begin());
		};

		template<class T>
		bool operator!=(const vector<T>& lhs, const vector<T>& rhs) {
			return !equal(lhs.begin(), lhs.end(), rhs.begin());
		};

		template<class T>
		bool operator<(const vector<T>& lhs, const vector<T>& rhs) {
			return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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