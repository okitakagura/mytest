#include<iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;
class MyString
{
private:
	char * _str;
	int len;
	int flag;
public:
	MyString(const char *s1);
	MyString(const MyString &st);
	MyString();
	~MyString();
	int size() const { return len; };
	MyString & append(const char *s2);
	MyString & append(const MyString &st);
	MyString & operator=(const MyString &st);
	MyString & operator=(const char *s);
	char & operator[](int i);
	const char &operator[](int i) const;
	friend int cmp(const MyString &st1, const MyString &st2);
	friend ostream & operator<<(ostream & os, const MyString &st);
	friend bool operator<(const MyString &st1, const MyString &st2);
	friend bool operator>(const MyString &st1, const MyString &st2);
	friend bool operator==(const MyString &st1, const MyString &st2);
	friend bool operator<=(const MyString &st1, const MyString &st2);
	friend bool operator>=(const MyString &st1, const MyString &st2);
	friend bool operator!=(const MyString &st1, const MyString &st2);
};
MyString::MyString()
{
	len = 0;
	_str = (char *)malloc(1 * sizeof(char));
	_str[0] = '\0';
	flag = 0;
}
MyString::MyString(const char *s1)
	:flag(0),len(strlen(s1)), _str((char *)malloc((len + 1) * sizeof(char)))
{
	memcpy(_str, s1, strlen(s1));
}
MyString::MyString(const MyString &st)
	: len(st.len), _str((char *)malloc((len + 1) * sizeof(char)))
{
	if (*this != st) {
		this->_str = st._str;
		this->flag++;
	}
	memcpy(_str, st._str, st.len);
}
MyString::~MyString()
{
	flag--;
	if (flag = 0) {
		free(_str);
	}
}
MyString & MyString::append(const char *s2)
{
	if (len == 0)
	{
		len = strlen(s2);
		_str = (char *)realloc(_str, (len + 1) * sizeof(char));
		memcpy(_str, s2, len);
		return *this;
	}
	else {
		len += strlen(s2);
		_str = (char *)realloc(_str, (len + 1) * sizeof(char));
		memcpy(_str + len - strlen(s2), s2, strlen(s2));
		return *this;
	}

}
MyString & MyString::append(const MyString & st)
{
	if (len == 0) {
		len = st.len;
		_str = (char *)realloc(_str, (len + 1) * sizeof(char));
		memcpy(_str, st._str, len);
		return *this;
	}
	else {
		len += st.len;
		_str = (char *)realloc(_str, (len + 1) * sizeof(char));
		memcpy(_str + len - st.len, st._str, st.len);
		return *this;
	}
}
MyString & MyString::operator=(const MyString &st)
{
	if (this == &st)
		return *this;
	free(_str);
	len = st.len;
	_str = (char *)malloc((len + 1) * sizeof(char));
	memcpy(_str, st._str, len);
	return *this;
}
MyString & MyString::operator=(const char *s)
{
	free(_str);
	len = strlen(s);
	_str = (char *)malloc((len + 1) * sizeof(char));
	memcpy(_str, s, len);
	return *this;
}
char & MyString::operator[](int i)
{
	flag--;
	char *tmp = (char *)malloc((len + 1) * sizeof(char));
	memcpy(tmp, _str, len);
	_str = tmp;
	flag = 0;
	return _str[i];
}
const char & MyString::operator[](int i)const
{
	return _str[i];
}
ostream & operator<<(ostream & os, const MyString &st)
{
	for (int i = 0; i<st.len; ++i)
	{
		os << st._str[i];
	}
	return os;
}
int cmp(const MyString &st1, const MyString &st2)
{
	int i = 0;
	while (st1._str[i] == st2._str[i])
	{
		if (i == st1.len)
			return 0;
		i++;
	}
	return(st1._str[i] - st2._str[i]);
}
bool operator<(const MyString &st1, const MyString &st2)
{
	return(cmp(st1, st2) < 0);
}
bool operator>(const MyString &st1, const MyString &st2)
{
	return(cmp(st1, st2) > 0);
}
bool operator==(const MyString &st1, const MyString &st2)
{
	return(cmp(st1, st2) == 0);
}
bool operator<=(const MyString &st1, const MyString &st2)
{
	return(cmp(st1, st2) <= 0);
}
bool operator>=(const MyString &st1, const MyString &st2)
{
	return(cmp(st1, st2) >= 0);
}
bool operator!=(const MyString &st1, const MyString &st2)
{
	return(cmp(st1, st2) != 0);
}
