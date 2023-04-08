#include"manager.h"
using namespace Manager::FileManager;
int main(){

    std::shared_ptr<filemanager> ptr(new filemanager());
    std::string path="/home/wlk/workspace/boost_learn_sample/test.log";
    std::string ret_path;
    if(ptr->GetRelativePath(path,ret_path)){
        std::cout<<"relative_path="<<ret_path<<std::endl;
    }else{
        std::cout<<"error"<<std::endl;
    }
    std::thread th0(&filemanager::IsFIle,ptr,path);
    std::thread th1(&filemanager::SetFileAllPerms,ptr,path);
    std::thread th2(&filemanager::IsFileOrDirectory,ptr,path);
    
    th0.join();
    th1.join();
    th2.join();
    return 0;
}