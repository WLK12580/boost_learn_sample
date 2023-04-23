#include"manager.h"
using namespace Manager::FileManager;
int main(){
    std::shared_ptr<filemanager> shar_ptr=std::make_shared<filemanager>();
    shar_ptr->CheckAndCreateBagUploadPath("/home/wlk/workspace/boost_learn_sample/new_p");
    std::vector<std::string> vec_path;
    std::string path1="/home/wlk/workspace/boost_learn_sample/old_p";
    if(!shar_ptr->GetAllFileAccoredPath(path1,vec_path)){
        std::cout<<"Get File Failed"<<std::endl;
        return 0;
    }
    std::string new_p="/home/wlk/workspace/boost_learn_sample/new_p";
    std::uint64_t time_start=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout<<"time_start:"<<time_start<<std::endl;
    for(int i=0;i<vec_path.size();i++){
        if(shar_ptr->IsForbitDeleteSet(vec_path[i])){
        std::cout<<"which is sucessed lock file cann't delete:"<<std::endl;
      }
    }
    for(int i=0;i<vec_path.size();i++){
        std::thread mu_th1(&filemanager::MutilThreadCopyFile,shar_ptr,vec_path,new_p,i);
        std::thread mu_th2(&filemanager::MutilThreadCopyFile1,shar_ptr,vec_path,new_p,i+1);
        std::thread mu_th3(&filemanager::MutilThreadCopyFile2,shar_ptr,vec_path,new_p,i+2);
        mu_th1.join();
        mu_th2.join();
        mu_th3.join();
        i+=2;
    }
    std::uint64_t time_end=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout<<"time_end:"<<time_end<<std::endl;
    std::cout<<"copy_costed_time:"<<time_end-time_start<<std::endl;
    return 0;
  }
