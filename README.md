<!-- # boost_learn_sample
bool IsFIle(const std::string &filename);  //判断是否为文件
bool GetRelativePath(const std::string &path,std::string &ret_relative); //获取相对路径
void SetFileAllPerms(const std::string &filename); //设置文件的权限
bool IsFileOrDirectory(const std::string &file); //判断是文件或者目录 -->

void CheckAndCreateBagUploadPath(std::string path);
bool IsExistsFile(const std::string &filepath);
bool RemoveFileWhenUploaded(std::string filepath);
bool GetAllFileAccoredPath(const std::string &path,std::vector<std::string>&vec_path);
bool IsForbitDeleteSet(const std::string &path);
bool IsForbitDeleteUnSet(const std::string &path);
void MutilThreadCopyFile(const std::vector<std::string>&vec_path,const std::string &new_p,int i);
bool GetRelativePath(const std::string &path,std::string &ret_relative);
bool MoveFilePath(const std::string &old_p,const std::string &new_p);
void MutilThreadCopyFile2(const std::vector<std::string>&vec_path,const std::string &new_p,int i);
void MutilThreadCopyFile1(const std::vector<std::string>&vec_path,const std::string &new_p,int i);

文件的操作包含

  std::mutex mu_mt;
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

    std::string to_p=new_p+"/"+file_name;
    std::cout<<"mute_thread_"<<i<<" to_p="<<to_p<<std::endl;
    auto cyop_ov=boost::filesystem::copy_option::overwrite_if_exists;
    boost::system::error_code ec;
    std::uint64_t time_start=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout<<"thread_"<<i<<"_time_start: "<<time_start<<std::endl;
    std::lock_guard<std::mutex>lk(mu_mt);
    boost::filesystem::copy_file(vec_path[i],to_p,cyop_ov,ec);
    if(ec){
      return ;
    }
    
    if(IsForbitDeleteUnSet(vec_path[i])){
      std::cout<<"which is sucessed unlock file can delete"<<std::endl;
    }
    // RemoveFileWhenUploaded(vec_path[i]);
    return ;
  }
  
      for(int i=0;i<vec_path.size();i++){
      std::thread mu_th1(MutilThreadCopyFile,vec_path,new_p,i);
      std::thread mu_th2(MutilThreadCopyFile,vec_path,new_p,i+1);
      std::thread mu_th3(MutilThreadCopyFile,vec_path,new_p,i+2);
      mu_th1.join();
      mu_th2.join();
      mu_th3.join();
      // mu_th1.detach();
      // mu_th2.detach();
      // mu_th3.detach();
      i+=2;
    }
