#include <iostream>
#include <memory>
#include <boost/filesystem.hpp>
#include <thread>
#include<mutex>
#include <future>
#include<map>
#include<chrono>
#include<fstream>
#include<functional>
namespace Manager
{
    namespace ThreadManager
    {
        class threadmanager
        {
            private:
                // int val_=0;
                // std::mutex mu_l;
                // std::condition_variable producer,consume;
            public:
                void AddSum(const int &val1, const int &val2);
                void UseMutex(const std::string &message,int &input_val) ;//message:消息类型，input_val:输入的参数
                void Producer(int i);
                void Consumer();
                std::string RecvDataSent(const std::string &senddata);
                std::string RecvDataFrom(const std::string &recvdata);
                std::string RecvData(const std::string &data);
                int fun(int x);
                
        };

    }

}
