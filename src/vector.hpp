#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
#include <iostream>

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

		typedef	T											value_type;
		typedef	Allocator									allocator_type;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		// typedef ft::random_access_iterator<pointer>			iterator;
		// typedef ft::random_access_iterator<const_pointer>	const_iterator;
		// typedef ft::reverse_iterator<iterator>				reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

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

		const_reference operator[](size_type index) const {
			return _data[index];
		};

		reference operator[](size_type index) {
			return _data[index];
		};

		template<value_type, Allocator>
		bool operator==(const ft::vector<value_type,Allocator>& lhs, const ft::vector<value_type,Allocator>& rhs) {
			if (lhs.size() != rhs.size())
				return (false);
			return (true);
		}

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

/******************************************************************************/
/*								Modifiers								      */
/******************************************************************************/

	};
};


#endif