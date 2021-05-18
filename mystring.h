#pragma once
#pragma warning( disable : 4996)
#ifndef MYSTRING_H
#define MYSTRING_H
#define npos 4294967295
#include<iostream>
#include<vector>
using namespace std;
class mystring {
private:
	//data
	char* s_ptr;
	size_t slength;
public:
	//constructor and destructor
	mystring();
	mystring(const char*);
	mystring(const mystring&);
	mystring(const mystring&, size_t);
	mystring(const mystring&, size_t, size_t);
	mystring(const size_t, const char);
	~mystring();
	//basic fun
	size_t length() const;
	bool empty();
	size_t size() const;
	const char* c_str();//返回c风格指针
	char& front();
	char& back();
	//overloading operator
	friend ostream& operator<<(ostream&, const mystring&);
	friend istream& operator>>(istream&, mystring&);

	friend bool operator==(const mystring&, const mystring&);
	friend bool operator==(const mystring&, const char*);
	friend bool operator>(const mystring&, const mystring&);
	friend bool operator<(const mystring&, const mystring&);
	friend bool operator<=(const mystring&, const mystring&);
	friend bool operator>=(const mystring&, const mystring&);
	friend bool operator!=(const mystring&, const mystring&);
	friend mystring& operator+=(mystring&, const mystring&);
	friend mystring& operator+=(mystring&, const char);
	mystring& operator=(const mystring&);
	mystring& operator=(const char*);
	mystring& operator+(const mystring&);

	char& operator[](const size_t);
	const char& operator[](const size_t)const;
	//fun define
	//append overloading
	mystring& append(const size_t, const char);//追加count字符的副本ch
	mystring& append(const mystring&);// 附加字符串 str
	mystring& append(const mystring&, size_t, size_t);//追加子[pos, pos+count)的str。
	//如果请求的子字符串超过字符串的末尾，或者计数== npos，附加的子字符串为[pos, size())。如果pos > str。大小（），则抛出std :: out_of_range。
	mystring& append(const char*, size_t);//追加范围内的字符[s, s + count)。此范围可以包含空字符。
	mystring& append(const char*,size_t,size_t);//附加由指向的以零结尾的字符串s。字符串的长度由第一个空字符使用确定
	//clear
	void clear();
	//insert
	mystring& insert(size_t, const char,size_t);//在哪插入单个字符n次
	mystring& insert(size_t, const char*, size_t, size_t);//在哪插入从a-b对于char指针
	mystring& insert(size_t, const mystring&, size_t, size_t);//在哪插入mystring的a-b
	//erase
	mystring& erase(size_t, size_t);//从a删b个字符,现在不太想写了
	//push_back
	void push_back(const char);
	//pop_back
	void pop_back();
	//compare
	bool compare(const mystring&)const;
	bool compare(const char*)const;
	//start_with
	bool start_with(const char)const noexcept;
	bool start_with(const char*)const noexcept;
	bool start_with(const mystring&)const noexcept;
	//end_with
	bool end_with(const char)const noexcept;
	bool end_with(const char*)const noexcept;
	bool end_with(const mystring&)const noexcept;
	//contains
	bool contains(const char*)const;
	bool contains(const mystring&)const;
	//replace
	void replace(size_t, size_t, const mystring&);
	void replace(size_t, size_t, const char*);
	void replace(const mystring&, const mystring&);
	void replace(size_t, size_t, const char);//由start到end替换为char
	//resize
	void resize(size_t);//缩小版本
	void resize(size_t, const char);//增加版本
	//swap
	void swap(mystring&);
	//find
	size_t find(const mystring&)const;
	size_t find(const char*)const;
	//substr
	mystring& substr(size_t, size_t)const;
	//reverse
	void reverse();
	//python部分:
	//eval
	double eval() ;
	//index
	size_t index(const mystring&);
	//count
	int count(const mystring&)const;
	//split
	vector<mystring> split(const char,int);//暂不支持python中"(const char *).split"
	vector<mystring> rsplit(const char,int);
	//partition
	vector<mystring> partition(const char);
	vector<mystring> rpartition(const char);
	//strip,rstrip,lesrip
	mystring& strip(const char);
	mystring& rstrip(const char);
	mystring& lstrip(const char);
	mystring& rstrip(const mystring&);
	mystring& lstrip(const mystring&);
	mystring& strip(const mystring&);
	//ljust
	mystring& ljust(size_t,const char);
	//rjust
	mystring& rjust(size_t, const char);
};
#endif // !mystring