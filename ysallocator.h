#pragma once
#ifndef _YSALLOCATOR_
#define _YSALLOCATOR_
#include<new>
#include<cstddef>
#include<cstdlib>
#include<iostream>
//此处部分仿照侯捷老师所著的《stl源码剖析》中实现的一个简单空间配置器
using namespace std;
namespace ys {
template<typename T>
inline T* _allocate(ptrdiff_t size, T*) {
	set_new_handler(0);//默认分配内存失败不采取动作，此处安全性有所欠缺
	T* tem = (T*)(::operator new((size_t)(size * sizeof(T))));
	if (tem == nullptr) {
		cerr << "out of range!" << endl;
		exit(0);
	}
	return tem;
}
template<typename T>
inline T* _deallocate(T* buffer) {
	::operator delete(buffer);
}
template<typename T1,typename T2>
inline void _construct(T1* p, const T2& value) {
	new(p) T1(value);
}
template<typename T>
inline void _destroy(T* ptr) {
	ptr->~T();
}
template<typename T>
class allocator {
public:
	typedef T			value_type;
	typedef T*			pointer;
	typedef const T*	const_pointer;
	typedef T&			reference;
	typedef const T&    const_reference;
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	template<typename U>
	struct rebind{
		typedef allocator<U> other;
	};

	pointer allocate(size_type n, const void* hint = 0) {
		return _allocate((difference_type)n, (pointer)0);
	}
	void construct(pointer p, const T& value) {
		_construct(p, value);
	}
	void deallocate(pointer p, size_type n) { _deallocate(p); }
	void destory(pointer p) { _destroy(p); }
	pointer adderss(reference x) { return (pointer)&x; }
	const_pointer const_address(const_reference x) {
		return (const_pointer)&x;
	}
};
}
#endif // !_YSALLOCATOR_
