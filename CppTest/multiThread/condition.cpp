#include<iostream>
#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<chrono>

using namespace std;

queue<int> que;
condition_variable cond;
mutex mu;

void func1(int n){
	unique_lock<mutex> locker(mu,defer_lock);
	while(n){
		locker.lock();
		que.push(n);
		locker.unlock();
		cond.notify_one();
		//cond.notify_all();
		this_thread::sleep_for(chrono::milliseconds(20));
		--n;
	}
	return;
}

void func2(){
	unique_lock<mutex> locker(mu,defer_lock);
	int data = 0;
	while(true){
		locker.lock();
		cond.wait(locker, [](){ return !que.empty();});
		data = que.front();
		cout<< "Getting data from another thread: "<<data<<","<<this_thread::get_id()<<endl;
		que.pop();
		locker.unlock();
		if(data == 1) break;
	}
	return;
}

int main(){
	int n;
	cout<<"Input data number : ";
	cin>>n;
	clock_t start_time = clock(), end_time;
	//Add your code here

	thread t1(func1,n);
	thread t2(func2);
	t1.join();
	t2.join();

	cout<<"DONE!"<<endl;
	end_time = clock();
	double delta_t = double(end_time - start_time)/double(CLOCKS_PER_SEC);
	cout<<"Time costed: "<<delta_t<<endl;
	return 0;
}
