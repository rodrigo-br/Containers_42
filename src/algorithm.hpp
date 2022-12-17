#ifndef ALGORITHM_H
#define ALGORITHM_H

namespace ft {
	template <class Iterator1, class Iterator2>
	bool equal (Iterator1 first1, Iterator1 last1, Iterator2 first2) {
		while (first1 != last1) {
			if (*first1 != *first2) { return false; };
			first1++;
			first2++;
		}
	};

	template <class Iterator1, class Iterator2, class BinaryPredicate>
	bool equal (Iterator1 first1, Iterator1 last1, Iterator2 first2, BinaryPredicate pred) {
		while (first1 != last1) {
			if (!pred(*first1, *first2)) { return false; };
			first1++;
			first2++;
		}
	};

}; //namespace ft

#endif