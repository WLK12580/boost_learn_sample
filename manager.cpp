#include "manager.h"
using namespace Manager::ThreadManager;
// void threadmanager::AddSum(const int &val1,const int &val2){
//     val_+=val1+val2;
//     std::cout<<"val_="<<val_<<std::endl;
// }
// void threadmanager::UseMutex(const std::string &message,int &input_val){
//     if(mu_l.try_lock())
//     {
//         std::cout<<"message:"<<message<<" val_num:"<<input_val<<std::endl;
//         mu_l.unlock();
//     }
// }
// void threadmanager::Producer(int i){
//     std::unique_lock<std::mutex> lk(mu_l); //unique_lock在其生命周期内会保持锁住的状态
//     while (val_)
//     {
//         producer.wait(lk);
//     }
//     val_=i;
//     std::cout<<"ba---"<<std::endl;
//     consume.notify_one();
// }
// void threadmanager::Consumer(){
//     std::unique_lock<std::mutex> lk(mu_l);
//     while(!val_){
//         consume.wait(lk);
//     }
//     std::cout<<"val_="<<val_<<std::endl;
//     val_=0;
//     producer.notify_one();
// }

int threadmanager::fun(int x) {
  x++;
  x *= 10;
  std::cout << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return x;
}
std::string threadmanager::RecvData(const std::string &data) {
        std::cout << "start_:" << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return data + "RecvData";
}
std::string threadmanager::RecvDataFrom(const std::string &recvdata) {
        std::cout << "recv_start_id:" << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return recvdata + "RecvData";
}
std::string threadmanager::RecvDataSent(const std::string &senddata) {
        std::cout << "send_start_id:" << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(20));
        return senddata + "SendData";
}