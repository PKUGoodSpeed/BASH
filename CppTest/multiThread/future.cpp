#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<chrono>

using namespace std;

class Job{
protected:
	static mutex mu;
	static condition_variable cond;
	static bool _fini1,_fini2;
public:
	Job() = default;
	virtual int MyJob(int x) = 0;
};

class ZeboJob: public Job{
public:
	ZeboJob() = default;
	virtual int MyJob(int x){
		unique_lock<mutex> locker(mu,defer_lock);
		int y = 0;
		locker.lock();
		cond.wait(locker, [](){return _fini2;});
		cout<<endl;
		cout<<"At time == " << clock() << "," <<endl;
		cout<<"Zebo is doing his job at Thread#" << this_thread::get_id() <<endl;
		y = x*x;
		locker.unlock();
		return y;
	}
};

class ShaocongJob: public Job{
	public:
	ShaocongJob() = default;
	virtual int MyJob(int x){
		unique_lock<mutex> locker(mu,defer_lock);
		int y = 0;
		locker.lock();
		Job::cond.wait(locker, [](){return _fini1;});
		cout<<endl;
		cout<< "At time == " << clock() << "," <<endl;
		cout<<"Shaocong is doing his job at Thread#" << this_thread::get_id() <<endl;
		while(x) y += (x--);
		locker.unlock();
		cond.notify_one();
		_fini2 = true;
		return y;
	}
};

class HyojungJob: public Job{
	public:
	HyojungJob() = default;
	virtual int MyJob(int x){
		unique_lock<mutex> locker(mu,defer_lock);
		int y = 1;
		locker.lock();
		cout<<endl;
		cout<< "At time == " << clock() << "," <<endl;
		cout<<"Hyojung is doing his job at Thread#" << this_thread::get_id() <<endl;
		while(x) y *= (x--);
		locker.unlock();
		_fini1 = true;
	    Job::cond.notify_one();
		return y;
	}
};


mutex Job::mu;
condition_variable Job::cond;
bool Job::_fini1 = false, Job::_fini2 = false;

int main(){
	//Input information here
	clock_t start_time = clock(), end_time;
	//Enter you code here
	auto p = async(launch::async, &Job::MyJob, move(HyojungJob()), 4);
	p = move(async(launch::async, &Job::MyJob, move(ShaocongJob()), p.get()));
	p = move(async(launch::async, &Job::MyJob, move(ZeboJob()), p.get()));
	cout<< "The answer is " << p.get() <<endl;
	//Calculating computational time
	end_time = clock();
	cout<<"DONE!"<<endl;
	double delta_t = double(end_time - start_time)/double(CLOCKS_PER_SEC);
	cout << "Time costed: " << delta_t <<endl;
}

/*
*In this case, three future are actually aranged into the same thread.
*When calling condition_variable::notify_one(), we need to consider this situation.
*Actually we use another synchronization mechanism to avoid forever waiting.
*/
