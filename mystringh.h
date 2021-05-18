#pragma once
#pragma warning( disable : 4996)
#pragma warning( disable : 4267)
#pragma warning( disable : 6385)
#pragma warning( disable : 26451)
#include"mystring.h"
#include<cassert>
#include"ysallocator.h"
#include<stack>
#include<vector>
#include<cstring>
using namespace ys;
//全代码没有用memcpy而用strcpy的原因：strcpy更适合字符串，而且效率快一些
//参考：https://blog.csdn.net/vgxpm/article/details/47614901
class out_of_r{};
mystring::mystring() :s_ptr(nullptr), slength(0) {}
mystring::mystring(const char* s) {
	if (s == nullptr) {
		s_ptr = nullptr;
		slength = 0;
		return;
	}
	slength = strlen(s);
	s_ptr = new char[slength + 1];
	strcpy(s_ptr, s);
}
mystring::mystring(const mystring& str) {
	if (str.s_ptr == nullptr) {
		s_ptr = nullptr;
		slength = 0;
		return;
	}
	slength = str.slength;
	s_ptr = new char[slength + 1];
	strcpy(s_ptr, str.s_ptr);
}
mystring::mystring(const size_t count, const char c) {
	slength = count;
	s_ptr = new char[count + 1];
	for (int i = 0;i < count;i++)
		s_ptr[i] = c;
	s_ptr[slength] = '\0';
}
mystring::mystring(const mystring&s, size_t n):slength(n) {
	if (s_ptr != nullptr) {
		delete[]s_ptr;
	}
	shared_ptr<char> tem(new char[n + 1]());
	for (int i = 0;i < n;i++)
		tem.get()[i] = s.s_ptr[i];
	tem.get()[n ] = '\0';
	s_ptr = new char[n + 1];
	strcpy(s_ptr, tem.get());
	s_ptr[n ] = '\0';
}
mystring::mystring(const mystring&s, size_t start, size_t count):slength(count) {
	if (start<0 || start>s.slength)
		throw std::out_of_range("out of range!");
	if (s_ptr != nullptr){
		delete[]s_ptr;
	}
	s_ptr = new char[count + 1]();
	for (int i = 0;i < count;i++) {
		s_ptr[i] = s.s_ptr[i + start];
	}
	s_ptr[count ] = '\0';

}
mystring::~mystring() {
	try {
		if (s_ptr != nullptr)
			delete[] s_ptr;
		s_ptr = nullptr;
		slength = 0;
	}
	catch(...){}
}
bool mystring::empty() {
	return slength == 0;
}
size_t mystring::length() const {
	return slength;
}
size_t mystring::size()const {
	return slength;
}
char& mystring::front() {
	return *s_ptr;
}
char& mystring::back() {
	return *(s_ptr + slength - 1);
}
const char* mystring::c_str() {
	return s_ptr;
}
ostream& operator<<(ostream& out, const mystring& s) {
	if (s.s_ptr != nullptr) {
		out << s.s_ptr;
	}
	return out;
}
istream& operator>>(istream& in, mystring& s) {
	char tem[1000];//每次输入不能超过1000个字符
	if (in >> tem) {
		delete[] s.s_ptr;
		s.slength = strlen(tem);
		s.s_ptr = new char[s.slength + 1];
		strcpy(s.s_ptr, tem);
		s.s_ptr[s.slength] = '\0';
	}
	return in;
}
mystring& mystring::operator+(const mystring& s) {
	return *this;
}
//不够好，参见effective c++条款10，11
//接上条，不知道为什么加入了异常安全性会多提示几个warning...不过修复了先前对象析构后出现的bug
mystring& mystring::operator=(const mystring&s) {
	if (s_ptr == s.s_ptr) return *this;
	if (s_ptr != nullptr) {
		delete[]s_ptr;
		s_ptr = new char[s.slength + 1]();
	}
	if (s_ptr == nullptr) throw std::out_of_range("null ptr!");
	strcpy_s(s_ptr,slength+1, s.s_ptr);
	s_ptr[s.slength] = '\0';
	slength = s.slength;
	return *this;
}
//s不是一个对象，不会自动析构
mystring& mystring::operator=(const char*s) {
	this->s_ptr = const_cast<char*>(s);
	s = nullptr;
	this->slength = strlen(s);
	return *this;
}
bool operator==(const mystring& s1, const mystring& s2) {
	if (s1.s_ptr == nullptr && s2.s_ptr == nullptr) return true;
	if (s1.s_ptr == nullptr || s2.s_ptr == nullptr) return false;
	return (strcmp(s1.s_ptr, s2.s_ptr) == 0 ? true : false) && (s1.slength == s2.slength);
}
bool operator==(const mystring&s1, const char*s2) {
	return s1 == mystring(s2);
}
bool operator>(const mystring& s1, const mystring& s2) {
	if (s1.s_ptr == nullptr && s2.s_ptr == nullptr) return false;
	if (s1.s_ptr == nullptr && s2.s_ptr != nullptr) return false;
	if (s1.s_ptr != nullptr && s2.s_ptr == nullptr) return true;
	return (strcmp(s1.s_ptr, s2.s_ptr) > 0 ? true : false) && (s1.slength == s2.slength);
}
bool operator<(const mystring& s1, const mystring& s2) {
	if (s1.s_ptr == nullptr && s2.s_ptr == nullptr) return false;
	if (s1.s_ptr == nullptr && s2.s_ptr != nullptr) return true;
	if (s1.s_ptr != nullptr && s2.s_ptr == nullptr) return false;
	return (strcmp(s1.s_ptr, s2.s_ptr) < 0 ? true : false) && (s1.slength == s2.slength);
}
bool operator>=(const mystring& s1, const mystring& s2) {
	return  s1 > s2||s1 == s2 ;
} 
bool operator<=(const mystring& s1, const mystring& s2) {
	return   s1 < s2||s1 == s2;
}
bool operator!=(const mystring& s1, const mystring& s2) {
	return s1 < s2 || s1>s2;
}
mystring& operator+=(mystring&s1, const mystring&s2) {
	s1.append(s2);
	return s1;
}
mystring& operator+=(mystring&s1, const char c) {
	s1.push_back(c);
	return s1;
}
char& mystring::operator[](const size_t ind) {
	if (ind >= slength || ind < 0) {
		throw "out of range";
	}
	return *(s_ptr + ind);
}
const char& mystring::operator[](const size_t ind)const {
	if (ind >= this->slength || ind < 0) {
		throw "out of range";
	}
	return *(s_ptr + ind);
}
mystring& mystring::append(const size_t count, const char c) {
	if (s_ptr == nullptr) {
		s_ptr = new char('\0');
	}
	if (count < 0) {
		cerr << "out of range";
		//throw out_of_range();
	}
	char* tem1 = new char[count + 1];
	for (int i = 0;i < count;i++)
		tem1[i] = c;
	char* tem2 = new char[slength + 1];
	strcpy(tem2, s_ptr);
	delete[] s_ptr;
	s_ptr = new char[slength + count + 1];
	slength = slength + count;
	strcpy(s_ptr, tem2);
	strcat(s_ptr, tem1);
	s_ptr[slength] = '\0';
	delete[]tem1, tem2;
	return *this;
}
mystring& mystring::append(const mystring& s) {
	if (s_ptr == nullptr) {
		s_ptr = new char('\0');
	}
	if (s.size() == 0) return *this;
	auto tem = new char[slength + s.slength + 1];
	strcpy(tem, s_ptr);
	strcat(tem, s.s_ptr);
	delete[]s_ptr;
	slength += s.slength;
	s_ptr = new char[slength + 1];
	strcpy(s_ptr, tem);
	delete[]tem;
	s_ptr[slength] = '\0';
	return *this;
}
mystring& mystring::append(const char* s, size_t count) {
	if (count < 0)
		throw "bad count";
	if (s_ptr == nullptr) {
		s_ptr = new char('\0');
	}
	auto tem = new char[count];
	for (int i = 0;i < count;i++)
		tem[i] = *(s + i);
	auto tem1 = new char[strlen(tem) + slength+1];
	strcpy(tem1, s_ptr);
	strcat(tem1, tem);
	tem1[slength + count] = '\0';
	slength += count ;
	delete[]s_ptr;
	s_ptr = new char[slength + 1];
	strcpy(s_ptr, tem1);
	delete[]tem;
	delete[]tem1;
	return *this;
}
mystring& mystring::append(const mystring&s, size_t start, size_t end) {
	if (end == npos) end = s.slength;
	if (end > s.slength || start < 0)
		throw "out of range";
	if (s_ptr == nullptr) {
		s_ptr = new char('\0');
	}
	auto tem = new char[end - start + 1]();
	for (int i = 0;i < end - start;i++)
		tem[i] = s.s_ptr[i];
	auto tem1 = new char[s.slength + end - start + 1];
	strcpy(tem1, s_ptr);
	strcat(tem1, tem);
	tem1[strlen(tem1)] = '\0';
	slength += end - start;
	delete[]s_ptr;
	s_ptr = new char[slength + 1];
	strcpy(s_ptr, tem1);
	delete[]tem;
	delete[]tem1;
	return *this;
}
mystring& mystring::append(const char*s,size_t start=0,size_t end=npos){
	if (end == npos) end = strlen(s);
	if (end > strlen(s) || start < 0)
		throw "out of range";
	auto tem1 = new char[this->slength + end - start + 1];
	if (s_ptr == nullptr) {
		s_ptr = new char('\0');
	}
	strcpy(tem1, s_ptr);
	strcat(tem1, s);
	tem1[strlen(tem1)] = '\0';
	slength += end - start;
	delete[]s_ptr;
	s_ptr = new char[slength + 1];
	strcpy(s_ptr, tem1);
	delete[]tem1;
	return *this;
}
void mystring::clear() {
	s_ptr = nullptr;
	slength = 0;
}
mystring& mystring::insert(size_t pos, const char c, size_t n=1) {
	if (s_ptr == nullptr) {
		s_ptr = new char('\0');
	}
	if (pos >= slength||pos<0||n<0) {
		throw "out of range!";
	}
	shared_ptr<char[]> tem(new char[slength + n + 1]());
	shared_ptr<char[]> tem1(new char[n+1]());
	shared_ptr<char[]> tem2 (new char[slength - pos + 1]);
	for (int i = 0;i < n;i++)
		tem1[i] = *const_cast<char*>(&c);
	tem1[strlen(tem1.get())] = '\0';
	for (size_t i = 0;i < pos;i++)
		tem[i] = s_ptr[i];
	for (size_t i = pos;i < slength;i++)
		tem2[i - pos] = s_ptr[i];
	tem2[slength - pos] = '\0';
	strcat(tem.get(), tem1.get());
	tem[strlen(tem.get())] = '\0';
	delete[]s_ptr;
	slength = slength+n;
	s_ptr = new char[slength + 1];
	strcpy(s_ptr, tem.get());
	strcat(s_ptr, tem2.get());
	//delete[]tem;
	return *this;
}
mystring& mystring::insert(size_t pos, const char* s, size_t start=0, size_t end=npos) {
	if (end == npos) end = strlen(s);
	if (s_ptr == nullptr) {
		s_ptr = new char('\0');
	}
	if (pos >= slength||pos<0) {
		throw "out of range!";
	}
	if (start < 0 || end > strlen(s)) {
		throw "out of range!";
	}
	shared_ptr<char[]> tem(new char[pos+1]());
	shared_ptr<char[]> tem1(new char[end-start+1]());
	shared_ptr<char[]> tem2(new char[slength - pos + 1]());
	shared_ptr<char[]> sum(new char[slength + end - start + 1]());
	for (int i = 0;i <= pos-1;i++)
		tem[i] = s_ptr[i];
	tem[pos] = '\0';
	for (size_t i = start;i < end;i++) 
		(tem1.get())[i - start] = *(s + i);
	tem1[strlen(tem1.get())] = '\0';
	for (size_t i = pos;i < slength;i++)
		tem2.get()[i - pos] = s_ptr[i];
	tem2[strlen(tem2.get())] = '\0';
	strcpy(sum.get(), tem.get());
	strcat(sum.get(), tem1.get());
	strcat(sum.get(), tem2.get());
	delete[]s_ptr;
	s_ptr = new char[slength + end - start + 1];
	strcpy(s_ptr, sum.get());
	slength = slength + end - start;
	return *this;
}
mystring& mystring::insert(size_t pos, const mystring&s, size_t begin=0, size_t end=npos) {//偷懒并且代码复用
	const char* tem = s.s_ptr;
	return insert(pos, tem, begin, end);
}
mystring& mystring::erase(size_t begin, size_t count) {
	return *this;

}
void mystring::push_back(const char c) {
	shared_ptr<char[]> tem(new char[slength + 2]());
	strcpy(tem.get(), s_ptr);
	tem[slength] = *const_cast<char*>(&c);
	tem[slength + 1] = '\0';
	slength++;
	delete[]s_ptr;
	s_ptr = new char[slength + 1]();
	strcpy(s_ptr, tem.get());
	s_ptr[slength] = '\0';
}
void mystring::pop_back(){
	this->resize(slength - 1);
}
void mystring::resize(size_t n) {
	if (n == slength) return;
	if (n > slength) {
		resize(n, '\0');
		return;
	}
	if (s_ptr[slength] != '\0')
		s_ptr[slength] = '\0';
	shared_ptr<char[]> tem(new char[n+1]());
	strncpy(tem.get(), s_ptr, n);
	tem[n] = '\0';
	slength=n;
	delete[]s_ptr;
	s_ptr = new char[n+1]();
	strcpy(s_ptr, tem.get());
	s_ptr[n] = '\0';
}
void mystring::resize(size_t n, const char c) {
	if (n == slength) return;
	if (n < slength) {
		resize(n);
		return;
	}
	shared_ptr<char[]> tem(new char[n+slength+1]());
	strcpy(tem.get(), s_ptr);
	for (int i = 0;i < n;i++) {
		tem[i + slength] = c;
	}
	tem[n + slength] = '\0';
	delete[] s_ptr;
	s_ptr = new char[n + slength+1];
	strcpy(s_ptr, tem.get());
	slength += n;
}
bool mystring::compare(const mystring&s2) const{//懒得写这两个，直接调用重载==了
	return *this== s2;
}
bool mystring::compare(const char*_s) const{
	return *this == mystring(_s);
}
bool mystring::start_with(const char c)const noexcept {
	return s_ptr[0] == c;
}
bool mystring::start_with(const char*s)const noexcept {
	if (s == nullptr) return false;
	if (s == "")
		return s_ptr == "" ? true : false;
	mystring tem = *this;
	tem.resize(strlen(s));
	return tem == mystring(s);
}
bool mystring::start_with(const mystring&s)const noexcept {
	if (s.s_ptr == "")
		return s_ptr == "" ? true : false;
	return start_with(s.s_ptr);
}
bool mystring::end_with(const char c)const noexcept {
	return *(s_ptr + slength - 1) == c;
}

mystring mystring::substr(size_t pos, size_t count)const {
	return mystring (*this, pos, count);
}
size_t mystring::find(const mystring& needle)const {
	shared_ptr<size_t[]> next(new size_t[needle.size()]());
	next[0] = 0;
	size_t j = 0;
	for (size_t i = 1;i < needle.size();i++) {
		while (needle[i] != needle[j] && j > 0)
			j = next[j - 1];
		if (needle[i] == needle[j])
			j++;
		next[i] = j;
	}
	j = 0;
	for (size_t i = 0;i < slength;i++) {
		while (j > 0 && s_ptr[i] != needle[j])
			j = next[j - 1];
		if (needle[j] == s_ptr[i])
			j++;
		if (j == needle.size())
			return (i - needle.size() + 1);
	}
	return -1;
}
size_t mystring::find(const char* needle)const {
	return find(mystring(needle));
}
void mystring::replace(size_t pos, size_t cou, const mystring& s2) {
	if (pos >= slength)
		throw std::out_of_range("error");
	int tem=this->find(s2);
	shared_ptr<char[]>tem1(new char[pos + 1]),tem2(new char[slength-cou-pos+1]),res(new char[slength-cou+s2.slength+1]);
	for (int i = 0;i < pos;i++) 
		res[i] = s_ptr[i];
	res[pos] = '\0';
	for (int i = 0;i < slength - cou - pos;i++)
		tem2[i] = s_ptr[i + pos + cou];
	tem2[slength - cou - pos] = '\0';
	strcat(res.get(), s2.s_ptr);
	strcat(res.get(), tem2.get());
	res[slength - cou + s2.slength] = '\0';
	delete[]s_ptr;
	s_ptr = new char[slength - cou + s2.slength + 1];
	strcpy(s_ptr, res.get());
	s_ptr[slength - cou + s2.slength] = '\0';
	slength = slength - cou + s2.slength;
}
void mystring::replace(size_t pos, size_t cou, const char*s) {
	replace(pos, cou, mystring(s));
}
void mystring::replace(const mystring&s1, const mystring&s2) {
	int pos = this->find(s1);
	if (pos == -1) {
		cerr << "can not find traget string!" << endl;
		throw std::out_of_range("can not find traget string!");
		return;
	}
	replace(pos, s1.size(), s2);
}
void mystring::replace(size_t start, size_t end, const char c) {
	for (int i = start;i < end;i++)
		s_ptr[i] = c;
}
void mystring::reverse() {
	shared_ptr<char[]> tem(new char[slength+1]());
	for (int i = 0,j=slength-1;i <slength;i++,j--) {
		tem[i] = s_ptr[j];
	}
	tem[slength ] = '\0';
	delete[]s_ptr;
	s_ptr = new char[slength+1];
	strcpy(s_ptr, tem.get());
	s_ptr[slength] = '\0';
}
bool mystring::end_with(const mystring&s)const noexcept {
	int len = s.size();
	for (int i = slength - len, j = 0;i < slength;i++, j++)
		if (s[j] != s_ptr[i]) return false;
	return true;
}
bool mystring::end_with(const char*s)const noexcept {
	int len = strlen(s);
	for (int i = slength - len,j=0;i < slength;i++,j++)
		if (s[j] != s_ptr[i]) return false;
	return true;
}
void mystring::swap(mystring&s) {
	mystring tem = *this;
	*this = s;
	s = tem;
}
bool mystring::contains(const mystring&s)const {
	return find(s) != -1;
}
bool mystring::contains(const char* s)const {
	return contains(mystring(s));
}
double fun(mystring, size_t&);
double calculate(mystring s) {
	size_t i = 0;
	return fun(s, i);
	}
double fun(mystring s, size_t& i) {
	stack<double> re;
	char sign = '+';
	double pre = 0, sum = 0, num = 0;
	for (i;i < s.size();i++) {
		if (isdigit(s[i])) {
			num = num * 10 + (s[i] - '0');
		}
		if (s[i] == '(') {
			num = fun(s, ++i);
			i++;
		}
		if ((!isdigit(s[i]) && s[i] != ' ') || i == s.size() - 1) {
			switch (sign) {
			case '+': re.push(num);  break;
			case '-': re.push(-num); break;
			case '*':
				pre = re.top();
				re.pop();
				re.push(num * pre);
				break;
			case '/':
				pre = re.top();
				re.pop();
				re.push(pre / num);
				break;
			}
			num = 0;
			sign = s[i];
		}
		if (s[i] == ')') break;
	}
	while (!re.empty()) {
		sum += re.top();
		re.pop();
	}
	return sum;
}
double mystring::eval() {
	return calculate(*this);
}
class index_error { void exit(); };
size_t mystring::index(const mystring& needle) {
	if (needle.size() == 0)
		throw std::out_of_range("error") ;
	shared_ptr<size_t[]> next(new size_t[needle.size()]());
	next[0] = 0;
	size_t j = 0;
	for (size_t i = 1;i < needle.size();i++) {
		while (needle[i] != needle[j] && j > 0)
			j = next[j - 1];
		if (needle[i] == needle[j])
			j++;
		next[i] = j;
	}
	j = 0;
	for (size_t i = 0;i < slength;i++) {
		while(j > 0 && s_ptr[i] != needle[j])
			j = next[j-1];
		if (needle[j] == s_ptr[i])
			j++;
		if (j == needle.size())
			return (i - needle.size() + 1);
	}
	throw std::out_of_range("ys nb!");
	return -1;
}
int mystring::count(const mystring& needle)const {
	if (needle.size() == 0)
		throw std::out_of_range("ys nb!");
	shared_ptr<int[]> next(new int[needle.size()]());
	next[0] = 0;
	int j = 0;
	int cou = 0;
	for (int i = 1;i < needle.size();i++) {
		while (needle[i] != needle[j] && j > 0)
			j = next[j - 1];
		if (needle[i] == needle[j])
			j++;
		next[i] = j;
	}
	j = 0;
	for (int i = 0;i < slength;i++) {
		while (j > 0 && s_ptr[i] != needle[j])
			j = next[j - 1];
		if (needle[j] == s_ptr[i])
			j++;
		if (j == needle.size()) {
			cou++;
			j--;
		}
	}
	return cou;
}
//返回值为一个vector
vector<mystring> mystring::split(const char c='\n',int n=INT_MAX) {
	vector<mystring>strs;
	int left = 0,cou=0;
	for (int i = 0;i < slength;i++) {
		if (s_ptr[i] == c && s_ptr[i - 1] != c) {
			mystring buf1(*this, left, i - left);
			strs.push_back(buf1);
			left = i + 1;
			cou++;
		}
		if (cou == n) break;
	}
	mystring buf(*this, left, slength);
	strs.push_back(buf);
	return strs;
}
vector<mystring> mystring::rsplit(const char c = '\n',int n=INT_MAX) {//使用release模式运行！否则可能会报错
	vector<mystring> strs = this->split(c,n);
	for (int i = 0;i < strs.size()/2;i++) {
		mystring tem = strs[i];
		strs[i] = strs[strs.size() - i - 1];
		strs[strs.size() - i - 1] = tem;
	}
	return strs;
}
vector<mystring> mystring::partition(const char c) {
	vector<mystring> strs = this->split(c, 1);
	return strs;
}
//使用release模式运行！否则可能会报错
vector<mystring> mystring::rpartition(const char c) {
	vector<mystring> strs = this->rsplit(c, 1);
	return strs;
}
mystring& mystring::lstrip(const char c=' ') {
	int pos = 0;
	while (s_ptr[pos] == c) 
		pos++;
	if (pos == 0) return *this;
	shared_ptr<char[]>tem(new char[slength-pos+1]());
	for (int i = 0;i < slength - i;i++)
		tem[i] = s_ptr[pos + i];
	tem[slength - pos] = '\0';
	delete[]s_ptr;
	s_ptr =new char[slength - pos+1];
	strcpy( s_ptr,tem.get());
	s_ptr[slength - pos] = '\0';
	slength = slength - pos;
	return *this;
}
mystring& mystring::rstrip(const char c=' ') {
	int pos= slength-1;
	for (; pos > 0; pos--) {
		if (s_ptr[pos] != c) break;
	}
	this->resize(pos+1);
	return *this;
}
mystring& mystring::strip(const char c = ' ') {
	this->rstrip(c);
	this->lstrip(c);
	return *this;
}
mystring& mystring::rstrip(const mystring&s) {
	for (int i = 0;i < s.slength;i++)
		this->rstrip(s[i]);
	return *this;
}
mystring& mystring::lstrip(const mystring&s) {
	for (int i = 0;i < s.slength;i++)
		this->lstrip(s[i]);
	return *this;
}
mystring& mystring::strip(const mystring&s) {
	this->rstrip(s);
	this->lstrip(s);
	return *this;
}
mystring& mystring::rjust(size_t n,const char c) {
	this->resize(n, c);
}

