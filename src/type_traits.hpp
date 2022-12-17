#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H


namespace ft {
/******************************************************************************/
/*						ENABLE_IF											  */
/******************************************************************************/

	template< bool B, class T = void > struct enable_if {};
	
	template<class T> struct enable_if<true, T> { typedef T type; };

/******************************************************************************/
/*						IS_INTEGER											  */
/******************************************************************************/

	// init

	struct false_type {};
	struct true_type {};

	// default

	template <typename T> struct is_integral {
		enum { value = 0 };
		typedef false_type type;
	};

	// 13 specializations

	template<> struct is_integral<bool> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<char> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<signed char> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<unsigned char> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<wchar_t> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<short> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<unsigned short> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<int> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<unsigned int> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<long> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<unsigned long> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<long long> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<unsigned long long> {
		enum { value = 1 };
		typedef true_type type;
	};

	// const specializations

	template<> struct is_integral<const bool> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const char> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const signed char> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const unsigned char> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const wchar_t> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const short> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const unsigned short> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const int> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const unsigned int> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const long> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const unsigned long> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const long long> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<> struct is_integral<const unsigned long long> {
		enum { value = 1 };
		typedef true_type type;
	};

}; 
//namespace ft
#endif