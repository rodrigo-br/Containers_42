#ifndef STUDIES_ITERATOR_BINARY_H
#define STUDIES_ITERATOR_BINARY_H

#include "studies_binary_tree.hpp"
 
namespace ft {
	template <class T, class A>
	template<class NodePtr, class PTR, class REF>
	class TreeBase<T, A>::IT : 	public iterator<std::bidirectional_iterator_tag, T,
												typename A::difference_type, PTR, REF> {

	protected:
		NodePtr current;

		void inc() {
			if (current->right == NULL) {
				NodePtr ptr = current;
				while ((current = current->parent)->right == ptr) {
					ptr = current;
				}
			}
			else
				current = TreeBase<T, A>::leftMost(current->right);
		};

		void dec() {
			if (current->left == NULL) {
				NodePtr ptr = current;
				while ((current = current->parent)->left == ptr) {
					ptr = current;
				}
			}
			else {
				if (current->parent  == current)
					current = current->right;
				else
					current = TreeBase<T, A>::rightMost(current->left);
			}
		};
		
		IT(NodePtr node) : current(node) {};

	public:
		IT() {};

		template<class NP, class P, class R>
		IT(const IT<NP, P, R> it) : current(it.current) {};

		IT& operator++() {
			inc();
			return *this;
		};

		IT operator++(int) {
			IT tmp(*this);
			inc();
			return tmp;
		};

		IT& operator--() {
			dec();
			return *this;
		};

		IT operator--(int) {
			IT tmp(*this);
			dec();
			return tmp;
		};

		REF operator*() const {
			return current->value;
		};

		PTR operator->() const {
			return &(current->value);
		};

		bool operator==(IT it) const {
			return current == it.current;
		};

		bool operator!=(IT it) const {
			return !(*this == it);
		};

	}; // class TreeBase<T, A>::IT

}; // namespace ft	

#endif