#include"manager.h"
using namespace Manager::FileManager;
void filemanager::CheckAndCreateBagUploadPath(std::string path){
   if(!boost::filesystem::exists(path) || !boost::filesystem::is_directory(path)){
      boost::filesystem::create_directories(path);
      std::cout<<"create new_path:sucessed"<<std::endl;
      return;
    }
    std::cout<<"new_path: is exists"<<std::endl;
}
bool filemanager::IsExistsFile(const std::string &filepath){
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

bool filemanager::RemoveFileWhenUploaded(std::string filepath){
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
bool filemanager::GetAllFileAccoredPath(const std::string &path,std::vector<std::string>&vec_path){
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
bool filemanager::IsForbitDeleteSet(const std::string &path){
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
bool filemanager::IsForbitDeleteUnSet(const std::string &path){
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
void filemanager::MutilThreadCopyFile(const std::vector<std::string>&vec_path,const std::string &new_p,int i){
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
    if(ec){   //拷贝失败解锁，防止不让监控脚本删除
      if(IsForbitDeleteUnSet(vec_path[i])){
        std::cout<<"which is sucessed unlock file can delete"<<std::endl;
      }
      return ;
    }
    if(IsForbitDeleteUnSet(vec_path[i])){  //拷贝成功，解除锁定
      std::cout<<"which is sucessed unlock file can delete"<<std::endl;
    }
    RemoveFileWhenUploaded(vec_path[i]);
    return ;
}
void filemanager::MutilThreadCopyFile1(const std::vector<std::string>&vec_path,const std::string &new_p,int i){
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
void filemanager::MutilThreadCopyFile2(const std::vector<std::string>&vec_path,const std::string &new_p,int i){
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
bool filemanager::MoveFilePath(const std::string &old_p,const std::string &new_p){
    int fd = std::rename(old_p.data(), new_p.data());
    if (0 == fd) {
        std::cout<<"Move file to path:%s ,result:successed"<<new_p.c_str()<<std::endl;
        return true;
    } else {
        std::cout<<"Move file to path:%s ,result:failed"<< new_p.c_str()<<std::endl;;
        return false;
    }
}
bool filemanager::GetRelativePath(const std::string &path,std::string &ret_relative){
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
