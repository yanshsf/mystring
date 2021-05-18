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
	const char* c_str();//����c���ָ��
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
	mystring& append(const size_t, const char);//׷��count�ַ��ĸ���ch
	mystring& append(const mystring&);// �����ַ��� str
	mystring& append(const mystring&, size_t, size_t);//׷����[pos, pos+count)��str��
	//�����������ַ��������ַ�����ĩβ�����߼���== npos�����ӵ����ַ���Ϊ[pos, size())�����pos > str����С���������׳�std :: out_of_range��
	mystring& append(const char*, size_t);//׷�ӷ�Χ�ڵ��ַ�[s, s + count)���˷�Χ���԰������ַ���
	mystring& append(const char*,size_t,size_t);//������ָ��������β���ַ���s���ַ����ĳ����ɵ�һ�����ַ�ʹ��ȷ��
	//clear
	void clear();
	//insert
	mystring& insert(size_t, const char,size_t);//���Ĳ��뵥���ַ�n��
	mystring& insert(size_t, const char*, size_t, size_t);//���Ĳ����a-b����charָ��
	mystring& insert(size_t, const mystring&, size_t, size_t);//���Ĳ���mystring��a-b
	//erase
	mystring& erase(size_t, size_t);//��aɾb���ַ�,���ڲ�̫��д��
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
	void replace(size_t, size_t, const char);//��start��end�滻Ϊchar
	//resize
	void resize(size_t);//��С�汾
	void resize(size_t, const char);//���Ӱ汾
	//swap
	void swap(mystring&);
	//find
	size_t find(const mystring&)const;
	size_t find(const char*)const;
	//substr
	mystring& substr(size_t, size_t)const;
	//reverse
	void reverse();
	//python����:
	//eval
	double eval() ;
	//index
	size_t index(const mystring&);
	//count
	int count(const mystring&)const;
	//split
	vector<mystring> split(const char,int);//�ݲ�֧��python��"(const char *).split"
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