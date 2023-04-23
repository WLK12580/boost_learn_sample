#include <iostream>
#include <memory>
#include <boost/filesystem.hpp>
#include <thread>
#include <mutex>
#include <future>
#include <map>
#include <chrono>
#include <fstream>
#include <functional>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
namespace Manager{
    namespace FileManager
    {
        class filemanager
        {
        private:
            std::mutex mu_mt1,mu_mt2,mu_mt3;
        public:
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
        };
    }
}
