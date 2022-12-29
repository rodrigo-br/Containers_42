#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

/*
	x = valor do tipo T
	i = escalar
	m = membro de T
    p & q = iterator<x>

	Categoria / Operação | Leitura | Escrita | Acesso | Iteração | Comparação
	-------------------- | ------- | ------- | ------ | -------- | ----------
	Output			     |		   | *p = x  |		  | p++ ++p  |
	-------------------- | ------- | ------- | ------ | -------- | ----------
	Input				 | x = *p  |		 | p->m   | p++ ++p  | p == q p!=q
	-------------------- | ------- | ------- | ------ | -------- | ----------
	Unidierecional		 | x = *p  | *p = x  | p->m   | p++ ++p  | p == q p!=q
	-------------------- | ------- | ------- | ------ | -------- | ----------
	Bidirectional 	   	 | x = *p  | *p = x  | p->m   | p++ ++p  | p == q p!=q
	                     |         |  	 	 |        | --p --p  | 
	-------------------- | ------- | ------- | ------ | -------- | ----------
	Random Access        | x = *p  | *p = x  | p->m   | p++ ++p  | p==q p!=q p>q
	                     |         |         | p[i]   | --p --p  | p<q p<=q p>=q
						 |		   |         |    	  | p+i p-i  | 
						 |		   |         |		  | p+q p-q  |

Hierarquia:
	            Iterador
				^      ^
			   /        \
		    Input	  Output
			   ^        ^
			    \      /
			  Unidierecional
			  	   ^
				   |
			  Bidirecional
			       ^
			  	   |
			 Acesso Aleatório

	
*/

namespace ft {

	struct output_iterator_tag {};

	struct input_iterator_tag {};

	struct forward_iterator_tag : public input_iterator_tag {};

	struct bidirectional_iterator_tag : public forward_iterator_tag {};

	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/*
		Template Global para Classes de Iteradores
*/
	template <typename Category,
			typename T,
			typename Distance = std::ptrdiff_t,
			typename Pointer = T*,
			typename Reference = T&>
	struct iterator {
		typedef Category								iterator_category;
		typedef T										value_type;
		typedef Distance								difference_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
	};

/*
		Iterator Traits para classes iteradoras
*/
#define IMPORT_ITERATOR(TYPE) typedef typename Iterator::TYPE TYPE
	template <typename Iterator>
	struct iterator_traits {
		IMPORT_ITERATOR(iterator_category);
		IMPORT_ITERATOR(value_type);
		IMPORT_ITERATOR(difference_type);
		IMPORT_ITERATOR(pointer);
		IMPORT_ITERATOR(reference);
	};

/*
		Template Specializations pointer e const pointer
*/
	template <typename T>
	struct iterator_traits<T*> {
		typedef std::random_access_iterator_tag 		iterator_category;
		typedef T 										value_type;
		typedef std::ptrdiff_t 							difference_type;
		typedef T* 										pointer;
		typedef T& 										reference;
	};

	template <typename T>
	struct iterator_traits<const T*> {
		typedef std::random_access_iterator_tag 		iterator_category;
		typedef T 										value_type;
		typedef std::ptrdiff_t 							difference_type;
		typedef const T* 								pointer;
		typedef const T& 								reference;
	};

/*
		Function dispatch
*/
	template <class Iterator>
	inline unsigned distance(Iterator first, Iterator last) {
		return _distance(first, last, typename iterator_traits<Iterator>::iterator_category());
	};

/*
		Functions
*/
	template <class Iterator>
	inline unsigned _distance(Iterator first, Iterator last, input_iterator_tag) {
		unsigned dist = 0;
		while (first != last) {
			++first;
			++dist;
		}
		return dist;
	};

	template <class Iterator>
	inline unsigned _distance(Iterator first, Iterator last, random_access_iterator_tag) {
		return last - first;
	};

#define IMPORT_TRAIT(TYPE) typedef typename TRAITS::TYPE TYPE

};//namespace ft 

#endif