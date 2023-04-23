#include "manager.h"
using namespace Manager::FileManager;

bool filemanager::GetRelativePath(const std::string &path, std::string &ret_relative)
{
    boost::filesystem::path base = boost::filesystem::current_path();
    boost::system::error_code ec;
    boost::filesystem::path ret_path = boost::filesystem::relative(path, base, ec);
    if (ec)
    {
        std::cout << "ec.meaasge: " << ec.message() << std::endl;
        ec.assign(errno,boost::system::system_category());
        return false;
    }
    else
    {
        ret_relative = ret_path.string();
        return true;
    }
}
void filemanager::SetFileAllPerms(const std::string &filename){
    if(!IsFIle(filename)){
        std::cout<<"not File"<<std::endl;
        return ;
    }
    auto perms=boost::filesystem::perms::owner_all;
    boost::system::error_code ec;
    boost::filesystem::permissions(filename,perms,ec);
    if(ec){
        std::cout<<"error: "<<ec.message()<<std::endl;
        return ;
    }else{
        std::cout<<"set perms ok"<<std::endl;
    }
}
bool filemanager::IsFIle(const std::string &filename){
    boost::system::error_code ec;
    auto file_status=boost::filesystem::status(filename,ec);
    if(ec){
        std::cout<<"error: "<<ec.message()<<std::endl;
        return false;
    }
    if(boost::filesystem::is_directory(file_status)){
        std::cout<<"is derectory"<<std::endl;
        return false;
    }
    if(file_status.type()==boost::filesystem::status_unknown){
        std::cout<<"unknow type"<<std::endl;
        return false;
    }
    std::cout<<"IsFile"<<std::endl;
    return true;
}
bool filemanager::IsFileOrDirectory(const std::string &file){
    boost::system::error_code ec;
    auto file_status=boost::filesystem::status(file,ec);
    if(ec){
        std::cout<<"error: "<<ec.message()<<std::endl;
        return false;
    }
    std::cout<<"is File or Directory"<<std::endl;
    return true;
}