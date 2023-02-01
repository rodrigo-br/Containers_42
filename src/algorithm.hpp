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
		return true;
	};

	template <class Iterator1, class Iterator2, class BinaryPredicate>
	bool equal (Iterator1 first1, Iterator1 last1, Iterator2 first2, BinaryPredicate pred) {
		while (first1 != last1) {
			if (!pred(*first1, *first2)) { return false; };
			first1++;
			first2++;
		}
		return true;
	};

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1) { return false; };
			if (*first1 < *first2) { return true; };
			first1++;
			first2++;
		}
		return (first2 != last2);
	};

	template <typename InputIt1, typename InputIt2, typename Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
			if (comp(*first1, *first2)) {
				return (true);
		}
    if (comp(*first2, *first1)) {
      return (false);
    }
  }
  return ((first1 == last1) && (first2 != last2));
};

}; //namespace ft

#endif