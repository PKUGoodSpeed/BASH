// I/O libs
#include<iostream>
#include<fstream>
#include<cstdio>

// STL templates
#include<string>
#include<vector>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<stack>
#include<queue>
#include<deque>
#include<algorithm>
#include<cmath>
#include<numeric>
#include<functional>

// Others
#include<memory.h>
#include<cassert>

// Multithreading
#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<chrono>

using namespace std;

// Typedefs
typedef long long LL;
typedef vector<int> vi;
typedef pair<int,int>ii;
typedef vector<LL> vL;
typedef vector<bool> vb;

int Factorial(future<int> f){
	int ans = 1, x = f.get();
	while(x) ans *= (x--);
	return ans;
}

int main(){
	// For accelerating I/O from std::cin and std::cout
	std::ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cout<< "Input a number " <<endl;
	int n;
	cin>>n;

	clock_t start_time = clock(), end_time;
	promise<int> p;
	auto f=p.get_future();
	f = async(launch::async, Factorial, move(f));
	p.set_value(n + n/3);
	cout<< "The result is: " << f.get() <<endl;

	// Output computational time
	end_time = clock();
	double d_t = double(end_time - start_time)/CLOCKS_PER_SEC;
	cout<< "Time spent: " << d_t << " s" <<endl;

	// Show ending
	cout<< "DONE!" <<endl;
	return 0;
}
