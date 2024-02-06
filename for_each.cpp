#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<functional>
using namespace std;

struct maxlenftn {
	maxlenftn() { maxlen = 0; }
    void operator()(string s) {
		maxlen = max(maxlen,s.size());
	}
	string::size_type maxlen;
};

vector<string> names = {
	"Spertus", "Lemon", "Golden", "Melhus"
};

void wrong() {
	maxlenftn maxf;
	for_each(names.begin(),names.end(),maxf);
	cout << maxf.maxlen << endl;
}

void better() {
	maxlenftn maxf;
	for_each(names.begin(),names.end(), ref(maxf));
	cout << maxf.maxlen << endl;
}

void best() {
	cout << for_each(names.begin(),names.end(),maxlenftn()).maxlen << endl;
}

struct maxlenftn2 {
	maxlenftn2() { maxlen = 0; }
    void operator()(string s) {
		maxlen = max(maxlen,s.size());
	}
	static string::size_type maxlen;
};

string::size_type maxlenftn2::maxlen;

void bad() {
	maxlenftn2 maxf;
	for_each(names.begin(),names.end(),maxf);
	cout << maxf.maxlen << endl;
}

void with_lambda() {
	size_t maxl{};
	for_each(names.begin(),names.end(),[&](string const &s) { 
		maxl = max(maxl, s.size());
	});
	cout << maxl << endl;
}

struct maxlenftn3 {
	maxlenftn3(string::size_type &maxlen) : maxlen(maxlen) { maxlen = 0; }
    void operator()(string s) {
		maxlen = max(maxlen,s.size());
	}
	string::size_type &maxlen;
};

void with_bound_functor() {
	size_t maxl{};
	for_each(names.begin(),names.end(), maxlenftn3(maxl));
	cout << maxl << endl;
}
int main()
{
  wrong();
  bad();
  better();
  best();
  with_lambda();
  with_bound_functor();
  return 0;
}
