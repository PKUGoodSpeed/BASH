#include<iostream>
#include<thread>
#include<vector>

using namespace std;

void func(int i){
	cout<<"Welcome from Thread #"<<i<<endl;
	return;
}

int main(){
	const int N = thread::hardware_concurrency();
	vector<thread> thread_vec;
	for(int i=1;i<N;++i){
		thread_vec.push_back(thread(func, i));
	}
	func(0);
	for(auto& t:thread_vec) t.join();
	return 0;
}

/*
*Non-determinstic Running Results
*/
