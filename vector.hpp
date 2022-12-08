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
		value_type		_data;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;

	public:

		explicit vector(const allocator_type &alloc = allocator_type()) :
			_data(NULL), _size(0), _capacity(0), _alloc(alloc) {
			};

		explicit vector(size_type size, const value_type &value = value_type(),
						const allocator_type &alloc = allocator_type()) :
			_size(size), _capacity(size), _alloc(alloc), _data(_alloc.allocate(_capacity)) {
				if (_data == NULL) { throw std::bad_alloc(); }
				for (size_type i = 0; i < _size; i++) {
					_alloc.construct(_data[i], value);
				}
		};

		void	push_back(const value_type &value) {
			_alloc.construct(&_data[_size], value);
			_size++;
		};

		size_type size() const { return _size; };

		const_reference operator[](size_type index) const { return _data[index]; }

		reference operator[](size_type index) { return _data[index]; }

		~vector() {};

	private:


	};
};


#endif