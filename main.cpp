// #include"manager.h"
// using namespace Manager::ThreadManager;
// void callback_1(threadmanager &th_mag){ //常量类指针只能访问类的常量成员函数
//     for(int i=0;i<100;i++){
//         th_mag.UseMutex("callback_1",i);
//     }
// }
// int main(){
//     std::shared_ptr<threadmanager> shar_ptr(new threadmanager);
//     std::thread th1(&threadmanager::AddSum,shar_ptr,1,2); //函数指针，不支持重载
//     threadmanager th_mg;
//     std::thread th2(callback_1,std::ref(th_mg)); //必须要std::ref，用
//     std::thread com[10],pro[10];
//     for(int i=0;i<10;i++){
//         com[i]=std::thread(&threadmanager::Consumer,shar_ptr);
//         pro[i]=std::thread(&threadmanager::Producer,shar_ptr,i);
//     }
//     for(int i=0;i<10;i++){
//         com[i].join();
//         pro[i].join();
//     }
//     std::ifstream ifin;
//     ifin.open("/home/wlk/workspace/boost_learn_sample/test/test/log/txt/my.log",std::ios::in | std::ios::out);
//     th1.join();
//     th2.join();

//     return 0;
// }