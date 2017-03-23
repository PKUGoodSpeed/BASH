#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<chrono>

using namespace std;

class Base{
};

int main(){
	//Input information here
	clock_t start_time = clock(), end_time;
	//Enter you code here
	promise<int> p;
	future<int> f = p.get_future();





	//Calculating computational time
	end_time = clock();
	cout<<"DONE!"<<endl;
	double delta_t = double(end_time - start_time)/double(CLOCKS_PER_SEC);
	cout << "Time costed: " << delta_t <<endl;
}
