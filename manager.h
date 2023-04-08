#include<iostream>
#include<filesystem>
#include<memory>
#include<boost/filesystem.hpp>
#include<thread>
namespace Manager{
    namespace FileManager{
        class filemanager
        {
            private:
                
            public:
                bool IsFIle(const std::string &filename);
                bool GetRelativePath(const std::string &path,std::string &ret_relative);
                void SetFileAllPerms(const std::string &filename);
                bool IsFileOrDirectory(const std::string &file);
        };
  
    }

}
