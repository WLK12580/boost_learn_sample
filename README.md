# boost_learn_sample
bool IsFIle(const std::string &filename);  //判断是否为文件
bool GetRelativePath(const std::string &path,std::string &ret_relative); //获取相对路径
void SetFileAllPerms(const std::string &filename); //设置文件的权限
bool IsFileOrDirectory(const std::string &file); //判断是文件或者目录

#include<iostream>
#include<thread>
#include<boost/filesystem.hpp>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
void CheckAndCreateBagUploadPath(std::string path){
   if(!boost::filesystem::exists(path) || !boost::filesystem::is_directory(path)){
      boost::filesystem::create_directories(path);
      std::cout<<"create new_path:sucessed"<<std::endl;
      return;
    }
    std::cout<<"new_path: is exists"<<std::endl;
  }
  bool IsExistsFile(const std::string &filepath){
    boost::system::error_code ec;
    auto filestatus=boost::filesystem::status(filepath,ec);
    if(ec){
      std::cout<<("error or not exists")<<std::endl;
      return false;
    }
    if(boost::filesystem::is_directory(filestatus)){
      std::cout<<("is directory")<<std::endl;
      return false;
    }
    if(filestatus.type()==boost::filesystem::status_unknown){
      std::cout<<("unknown file")<<std::endl;
      return false;
    }
    return true;
  }
    bool RemoveFileWhenUploaded(std::string filepath){
    if(IsExistsFile(filepath)){
      int fd=std::remove(filepath.c_str());
      if(0==fd){
        return true;
      }
      else{
        return false;
      }
    }
    return false;
  }
  bool GetAllFileAccoredPath(const std::string &path,std::vector<std::string>&vec_path){
    boost::filesystem::path ph(path);
    if(!boost::filesystem::exists(path) || !boost::filesystem::is_directory(path)){
      std::cout<<"falseed"<<std::endl;
      return false;
    }
    boost::filesystem::recursive_directory_iterator rd_iter_end;
    for(boost::filesystem::recursive_directory_iterator iter(ph);iter!=rd_iter_end;iter++){
      if(boost::filesystem::is_regular_file(iter->status())){
        std::cout<<"file_path=%s"<<iter->path().string().c_str()<<std::endl;;
        vec_path.push_back(iter->path().string());
      }
    }
    return true;
  }
  bool IsForbitDeleteSet(const std::string &path){
    std::string bash_command="sudo chattr +i "+path;
    int fd=system(bash_command.data());
    if(0==fd){
      std::cout<<"IsForbitDeleteSet_True file: "<<path<<std::endl;
      return true;
    }else{
      std::cout<<"IsForbitDeleteSet_False file : "<<path<<std::endl;
      return false;
    }
  }
  bool IsForbitDeleteUnSet(const std::string &path){
    std::string bash_command="sudo chattr -i "+path;
    int fd=system(bash_command.data());
    if(0==fd){
      std::cout<<"IsForbitDeleteUnSet_True: the file is: "<<path<<std::endl;
      return true;
    }
    else{
      std::cout<<"IsForbitDeleteUnSet_False: the file is:"<<path<<std::endl;
      return false;
    }
  }

  std::mutex mu_mt1,mu_mt2,mu_mt3;
  void MutilThreadCopyFile(const std::vector<std::string>&vec_path,const std::string &new_p,int i){
    std::string file_name="";
    std::string file_path="";
    if(i<vec_path.size()){
        file_path=vec_path[i];
    }else{
      return ;
    }
    if(!IsExistsFile(file_path)){
      return ;
    }
    int pos=vec_path[i].find_last_of("/");
      if(pos!=vec_path[i].npos){
        file_name=vec_path[i].substr(pos+1,vec_path.size()-1-pos);
    }
    std::uint64_t time_start=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout<<"thread_1_time_start:"<<time_start<<std::endl;
    std::string to_p=new_p+"/"+file_name;
    std::cout<<"mute_thread_1 "<<"to_p="<<to_p<<std::endl;
    auto cyop_ov=boost::filesystem::copy_option::overwrite_if_exists;
    boost::system::error_code ec;
    std::lock_guard<std::mutex>lk(mu_mt1);
    boost::filesystem::copy_file(vec_path[i],to_p,cyop_ov,ec);
    if(ec){
      return ;
    }
    
    if(IsForbitDeleteUnSet(vec_path[i])){
      std::cout<<"which is sucessed unlock file can delete"<<std::endl;
    }
    RemoveFileWhenUploaded(vec_path[i]);
    return ;
  }
   void MutilThreadCopyFile1(const std::vector<std::string>&vec_path,const std::string &new_p,int i){
    
    std::string file_name="";
    std::string file_path="";
    if(i<vec_path.size()){
        file_path=vec_path[i];
    }else{
      return ;
    }
    if(!IsExistsFile(file_path)){
      return ;
    }
    int pos=vec_path[i].find_last_of("/");
      if(pos!=vec_path[i].npos){
        file_name=vec_path[i].substr(pos+1,vec_path.size()-1-pos);
    }
    std::uint64_t time_start=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout<<"thread_2_time_start:"<<time_start<<std::endl;
    std::string to_p=new_p+"/"+file_name;
    std::cout<<"mute_thread_2 "<<"to_p="<<to_p<<std::endl;
    auto cyop_ov=boost::filesystem::copy_option::overwrite_if_exists;
    boost::system::error_code ec;
    std::lock_guard<std::mutex>lk(mu_mt2);
    boost::filesystem::copy_file(vec_path[i],to_p,cyop_ov,ec);
    if(ec){
      return ;
    }
    
    if(IsForbitDeleteUnSet(vec_path[i])){
      std::cout<<"which is sucessed unlock file can delete"<<std::endl;
    }
    RemoveFileWhenUploaded(vec_path[i]);
    return ;
  }
   void MutilThreadCopyFile2(const std::vector<std::string>&vec_path,const std::string &new_p,int i){
    
    std::string file_name="";
    std::string file_path="";
    if(i<vec_path.size()){
        file_path=vec_path[i];
    }else{
      return ;
    }
    if(!IsExistsFile(file_path)){
      return ;
    }
    int pos=vec_path[i].find_last_of("/");
      if(pos!=vec_path[i].npos){
        file_name=vec_path[i].substr(pos+1,vec_path.size()-1-pos);
    }
    std::uint64_t time_start=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout<<"thread_3_time_start:"<<time_start<<std::endl;
    std::string to_p=new_p+"/"+file_name;
    std::cout<<"mute_thread_3 "<<"to_p="<<to_p<<std::endl;
    auto cyop_ov=boost::filesystem::copy_option::overwrite_if_exists;
    boost::system::error_code ec;
    std::lock_guard<std::mutex>lk(mu_mt3);
    boost::filesystem::copy_file(vec_path[i],to_p,cyop_ov,ec);
    if(ec){
      return ;
    }
    
    if(IsForbitDeleteUnSet(vec_path[i])){
      std::cout<<"which is sucessed unlock file can delete"<<std::endl;
    }
    RemoveFileWhenUploaded(vec_path[i]);
    return ;
  }
  bool MoveFilePath(const std::string &old_p,const std::string &new_p){
    int fd = std::rename(old_p.data(), new_p.data());
    if (0 == fd) {
      std::cout<<"Move file to path:%s ,result:successed"<<new_p.c_str()<<std::endl;
      return true;
    } else {
      std::cout<<"Move file to path:%s ,result:failed"<< new_p.c_str()<<std::endl;;
      return false;
    }
  }
  bool GetRelativePath(const std::string &path,std::string &ret_relative){
      boost::filesystem::path base=boost::filesystem::current_path();
      boost::system::error_code ec;
      boost::filesystem::path ret_path=boost::filesystem::relative(path,base,ec);
      if(ec){
          std::cout<<"Error: %s"<<ec.message().c_str()<<std::endl;
          return false;
      }else{
          ret_relative=ret_path.string();
          std::cout<<"Successed: releaive_path:%s"<<ret_relative.c_str()<<std::endl;;
          return true;
      }
  }
  

  int main(){
    CheckAndCreateBagUploadPath("/home/wlk/test_workspace/c++/new_p");
    std::vector<std::string> vec_path;
    std::string path1="/home/wlk/test_workspace/c++/old_p";
    if(!GetAllFileAccoredPath(path1,vec_path)){
      std::cout<<"Get File Failed"<<std::endl;
      return 0;
    }
    std::string new_p="/home/wlk/test_workspace/c++/new_p";
    std::uint64_t time_start=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout<<"time_start:"<<time_start<<std::endl;
    for(int i=0;i<vec_path.size();i++){
      if(IsForbitDeleteSet(vec_path[i])){
        std::cout<<"which is sucessed lock file cann't delete:"<<std::endl;
      }
    }
    for(int i=0;i<vec_path.size();i++){
      std::thread mu_th1(MutilThreadCopyFile,vec_path,new_p,i);
      std::thread mu_th2(MutilThreadCopyFile1,vec_path,new_p,i+1);
      std::thread mu_th3(MutilThreadCopyFile2,vec_path,new_p,i+2);
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
