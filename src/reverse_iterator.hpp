#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include "iterator_traits.hpp"

namespace ft{
template <typename Iterator> class reverse_iterator : public std::iterator 
						< typename ft::iterator_traits<Iterator>::iterator_category,
						typename ft::iterator_traits<Iterator>::value_type,
						typename ft::iterator_traits<Iterator>::difference_type,
						typename ft::iterator_traits<Iterator>::pointer,
						typename ft::iterator_traits<Iterator>::reference > {
	public:

		typedef Iterator													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

	protected:

		iterator_type						_current;
		typedef iterator_traits<Iterator>	_traits_type;


	public:	

/******************************************************************************/
/*					Constructors & Destructor							      */
/******************************************************************************/

		reverse_iterator() : _current() {};

		explicit reverse_iterator (iterator_type it) : _current(it) {};

		reverse_iterator (const reverse_iterator<iterator_type>& it) : _current(it._current) {};

		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& it) : _current(it.base()) {};

		~reverse_iterator() {};

/******************************************************************************/
/*					Base												      */
/******************************************************************************/

		iterator_type base(void) const { return _current; };


/******************************************************************************/
/*					Operators											      */
/******************************************************************************/

		reference operator*() const {
			iterator_type tmp = _current;
			return *tmp;
		};

		pointer operator->() const {
			iterator_type tmp = _current;
			--tmp;
			return s_to_pointer(tmp);
		};

		reverse_iterator &operator++() {
			--_current;
			return *this;
		};

		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			--_current;
			return tmp;
		};

		reverse_iterator &operator--() {
			++_current;
			return *this;
		};

		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			++_current;
			return tmp;
		};

		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(_current - n);
		};

		reverse_iterator &operator+=(difference_type n) {
			_current -= n;
			return *this;
		};

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(_current + n);
		};

		reverse_iterator &operator-=(difference_type n) {
			_current += n;
			return *this;
		};

		reference operator[](difference_type n) const {
			return *(*this - n);
		};

		private:
			template<typename Tp>
			static Tp *s_to_pointer(Tp* p) { return p; };

			template<typename Tp>
			static pointer s_to_pointer(Tp t) { return t.operator->(); };

	};

	template <typename Iterator>
	inline bool operator==(const reverse_iterator<Iterator> &x,
							const reverse_iterator<Iterator> &y) {
		return x.base() == y.base();
	};

	template <typename Iterator>
	inline bool operator<(const reverse_iterator<Iterator> &x,
							const reverse_iterator<Iterator> &y) {
		return y.base() < x.base();
	};

	template <typename Iterator>
	inline bool operator!=(const reverse_iterator<Iterator> &x,
							const reverse_iterator<Iterator> &y) {
		return !(x == y);
	};

	template <typename Iterator>
	inline bool operator>(const reverse_iterator<Iterator> &x,
							const reverse_iterator<Iterator> &y) {
		return y < x;
	};

	template <typename Iterator>
	inline bool operator<=(const reverse_iterator<Iterator> &x,
							const reverse_iterator<Iterator> &y) {
		return !(y < x);
	};

	template <typename Iterator>
	inline bool operator>=(const reverse_iterator<Iterator> &x,
							const reverse_iterator<Iterator> &y) {
		return !(x < y);
	};

	template<typename I_L, typename I_R>
	inline bool operator==(const reverse_iterator<I_L> &x,
							const reverse_iterator<I_R> &y) {
		return x.base() == y.base();
	};

	template<typename I_L, typename I_R>
	inline bool operator<(const reverse_iterator<I_L> &x,
							const reverse_iterator<I_R> &y) {
		return y.base() < x.base();
	};

	template<typename I_L, typename I_R>
	inline bool operator!=(const reverse_iterator<I_L> &x,
							const reverse_iterator<I_R> &y) {
		return !(x == y);
	};

	template<typename I_L, typename I_R>
	inline bool operator>(const reverse_iterator<I_L> &x,
							const reverse_iterator<I_R> &y) {
		return y < x;
	};

	template<typename I_L, typename I_R>
	inline bool operator<=(const reverse_iterator<I_L> &x,
							const reverse_iterator<I_R> &y) {
		return !(y < x);
	};

	template<typename I_L, typename I_R>
	inline bool operator>=(const reverse_iterator<I_L> &x,
							const reverse_iterator<I_R> &y) {
		return !(y < x);
	};

	template < typename It1, typename It2 >
	inline typename reverse_iterator<It1>::difference_type
	operator-( const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs )
	{
		return rhs.base() - lhs.base();
	}

	template < typename It1, typename It2 >
	inline reverse_iterator<It1>
	operator-( typename reverse_iterator<It1>::difference_type n,
			const reverse_iterator<It2>                    &rhs )
	{
		return reverse_iterator<It1>( rhs.base() + n );
	}

	template < typename Iterator >
	inline typename reverse_iterator<Iterator>::difference_type
	operator-( const reverse_iterator<Iterator> &rhs,
			const reverse_iterator<Iterator> &lhs )
	{
		return lhs.base() - rhs.base();
	}

	template < typename Iterator >
	inline reverse_iterator<Iterator>
	operator-( typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>                    &rhs )
	{
		return reverse_iterator<Iterator>( rhs.base() + n );
	}


};//namespace

#endif