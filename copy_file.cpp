#include "manager.h"
#include <future>
#include<map>
#include<chrono>
using namespace Manager::ThreadManager;
int main() {
	std::shared_ptr<threadmanager> shared_ptr=std::make_shared<threadmanager>();
	threadmanager thm;
  	// std::packaged_task<int(int)> pt(shared_ptr->fun(10));  // 将函数打包起来
	// std::future<int> fu = pt.get_future();        // 并将结果返回给future
	// std::thread t(std::ref(pt), 1);
	// std::cout << fu.get() << std::endl;
	// std::cout << std::this_thread::get_id() << std::endl;
	// t.join();
	auto start=std::chrono::system_clock::now();
	// auto RecvData_Bind_Fun=std::bind(&threadmanager::RecvData,"data");
	// std::future<std::string> func=std::async(std::launch::async,RecvData_Bind_Fun);
    std::future<std::string> func1=std::async(std::launch::deferred,&threadmanager::RecvDataFrom,shared_ptr,"data");
	std::future<std::string> func2=std::async(std::launch::async,&threadmanager::RecvDataSent,thm,"RecvSent");
	// std::string data=func.get();//如果RecvData没有结束，则会一直阻塞
	std::string my_data=func1.get();//调用get时RecvDataFrom才开始执行
	std::cout<<"my_data:"<<my_data<<std::endl;
	std::future_status status;
	do {
		status = func2.wait_for(std::chrono::seconds(1));
		std::this_thread::sleep_for(std::chrono::seconds(1));
		switch (status) {
			case std::future_status::timeout:
				/* code */
				std::cout << "async timeout" << std::endl;
				break;
			case std::future_status::deferred:
				std::cout << "async not start" << std::endl;
				break;
			case std::future_status::ready:
				std::cout << "output=" << func2.get() << std::endl;
				break;
			default:
				break;
		}
	} while (status != std::future_status::ready);

	auto end =std::chrono::system_clock::now();
	// auto diff_time=std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
	auto diff_time=std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
	std::cout<<"duration_time="<<diff_time<<"(s)"<<std::endl;
	return 0;
}