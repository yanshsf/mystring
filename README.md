# mystring
关于mystring:
===
学习了一段时间的c++了，自认为已经入门了c++，但看书和看视频学习终究还是纸上谈兵。于是用着自己浅显的c++知识，重写了c++的string类，并且命名为mystring。在此之前无任何c++项目编写经验，这1000多行代码也是通过了一个星期的冥思苦想独立完成的。第一次写对我来说如此“浩大”的工程，难免bug百出。截至到现在只是完成了基本的实现功能，但是代码没有任何的鲁棒性，接下来的几个星期我将继续不断完善这个代码，提升代码的鲁棒性，加入更多的功能进去。

简介：
--
mystring实现了最基本的c++ string，包含大部分string中的功能，目前不支持iterator，在后续版本会写入。同时我认为这个项目最大的亮点是用c++实现了python中的部分字符串处理函数，包括count，eval，strip，split等。

手册：
--
1.c++中string自带的函数
与c++中的函数大体运用方式相同，支持以下函数：<br>
  mystring();<br>
	mystring(const char*);<br>
	mystring(const mystring&);<br>
	mystring(const mystring&, size_t);<br>
	mystring(const mystring&, size_t, size_t);<br>
	mystring(const size_t, const char);<br>
	~mystring();<br>
	//basic fun<br>
	size_t length() const;<br>
	bool empty();<br>
	size_t size() const;<br>
	const char* c_str();//返回c风格指针<br>
	char& front();<br>
	char& back();<br>
	//overloading operator<br>
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
	mystring substr(size_t, size_t)const;
	//reverse
	void reverse();
2.python字符串处理函数：<br>
	double eval() ;<br>
	//index<br>
	size_t index(const mystring&);<br>
	//count<br>
	int count(const mystring&)const;<br>
	//split<br>
	vector<mystring> split(const char,int);//暂不支持python中"(const char *).split"<br>
	vector<mystring> rsplit(const char,int);<br>
	//partition<br>
	vector<mystring> partition(const char);<br>
	vector<mystring> rpartition(const char);<br>
	//strip,rstrip,lesrip<br>
	mystring& strip(const char);<br>
	mystring& rstrip(const char);<br>
	mystring& lstrip(const char);<br>
	mystring& rstrip(const mystring&);<br>
	mystring& lstrip(const mystring&);<br>
	mystring& strip(const mystring&);<br>
	//ljust<br>
	mystring& ljust(size_t,const char);<br>
	//rjust<br>
	mystring& rjust(size_t, const char);<br>
