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