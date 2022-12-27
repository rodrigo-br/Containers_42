#ifndef CONTAINER_H
#define CONTAINER_H

namespace ft {

	template < class Type, class Alloc,
			class Ref		=	typename Alloc::reference,
			class ConstRef	=	typename Alloc::const_reference,
			class Ptr		=	typename Alloc::pointer,
			class ConstPtr	=	typename Alloc::const_pointer,
			class Dif		=	typename Alloc::difference_type,
			class Size		=	typename Alloc::size_type >
	struct Container {
		typedef Type			value_type;
		typedef Alloc			allocator_type;
		typedef Ref				reference;
		typedef ConstRef		const_reference;
		typedef Ptr				pointer;
		typedef ConstPtr		const_pointer;
		typedef Dif				difference_type;
		typedef Size			size_type;
	};//struct Container

#define IMPORT_TYPE(TYPE) typedef typename CONTAINER::TYPE TYPE

};//namespace ft

#endif