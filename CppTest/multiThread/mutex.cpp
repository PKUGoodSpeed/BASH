#include<iostream>
#include<thread>
#include<vector>
#include<mutex>
#include<stack>

using namespace std;

class SynChrLock{
    static mutex mu;
	static stack<int> stk;
public:
	void addItem(int x){
		stk.push(x);
	}
	void procStk(int i){
		while(true){
			mu.lock();
			if(stk.empty()){
				mu.unlock();
				return;
			}
			cout<<"From Thread #"<<i<<":"<<endl;
			cout<<"Processing Number: "<<stk.top()<<endl;
			stk.pop();
			mu.unlock();
		}
	}
};

mutex SynChrLock::mu;
stack<int> SynChrLock::stk;

int main(){
	int N;
	cout<<"Input the number of threads (1~10)"<<endl;
	cin>>N;
	vector<thread> thread_vec;
	SynChrLock src;
	for(int i=0;i<30;++i) src.addItem(i);
	clock_t start_time = clock(), end_time;
	for(int i=1;i<N;++i){
		thread_vec.push_back(thread(&SynChrLock::procStk, src, i));
	}
	src.procStk(0);
	for(auto& t:thread_vec) t.join();
	cout<<"DONE!"<<endl;
	end_time = clock();
	double delta_t = double(end_time - start_time)/double(CLOCKS_PER_SEC);
	cout<<"Time costed: "<<delta_t<<"s!"<<endl;
	return 0;
}

/*
*This code actually shows that using multithreading may not result in betterperformance.
*/
