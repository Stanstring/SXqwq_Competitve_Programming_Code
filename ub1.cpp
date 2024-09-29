#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int n, k, minn, ans;
char op;
char buf[1 << 20], *p1, *p2;
vector <int> a;
#define get() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
long long read()
{
	long long s = 0, w = 1;
	char c = get();
	while (c < '0' || c > '9')
	{
		if (c == '-') w = -1;
		c = get();
	}
	while (c >= '0' && c <= '9')
	{
		s = s * 10 + c - '0';
		c = get();
	}
	return s * w;
}
void write(long long n)
{
	if (n < 0) 
	{
		putchar_unlocked('-');
		n = -n;
	}
	if (n >= 10) write(n / 10);
	putchar_unlocked(n % 10 + '0');
	return;
}
int main()
{
	n = read(), minn = read();
    a.reserve(1000001);
	while (n--)
	{
        op = get(), k = read();
		if (op == 'I')
		{
			if (k >= minn)
			    a.insert(lower_bound(a.begin(), a.end(), k) ,k); 
		}
		else if (op == 'A')
		{
			int l = a.size();
			for (int i = 0; i < l; i++)
				a[i] += k;
		}
		else if (op == 'S')
		{
		    int l = a.size();
			for (int i = 0; i < l; i++)
			{
				a[i] -= k;
				if (a[i] < minn)
				{
					a.erase(lower_bound(a.begin(), a.end(), a[i]));
					i--;
					l--;
					ans++;
				}
			}
		}
		else if (op == 'F')
		{
			int l = a.size();
			if (k > l) write(-1);
			else write(a[l - k]);
			putchar_unlocked('\n');
		}
	}
	write(ans);
	return 0;
}