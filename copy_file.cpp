#define BOOST_FILESYSTEM_NO_DEPRECATED
#include<iostream>
#include<string>
#include<boost/filesystem.hpp>
bool IsExistsFile(const boost::filesystem::path& ph) {
	auto file_status = boost::filesystem::status(ph);
	if (boost::filesystem::is_directory(file_status))
	{
		std::cout << "is_directory" << std::endl;
		return false;
	}
    if(!boost::filesystem::is_regular_file(file_status)){
        std::cout<<"not regular file"<<std::endl;
        return false;
    }
	if (!boost::filesystem::exists(file_status)) {
		std::cout << "file not exists" << std::endl;
		return false;
	}
	std::cout << "exists" << std::endl;
	return true;
}

bool CopyFile(const std::string& from, const std::string& to) {
	if (!IsExistsFile(from)) {
		return false;
	}
	boost::filesystem::path from_p = from;
	boost::filesystem::path to_p = to;
    boost::system::error_code ec;
	auto options=boost::filesystem::copy_option::overwrite_if_exists;//替换既存文件
    //auto options=boost::filesystem::copy_option::none;//默认方式,目标文件不存在则拷贝ec=0，存在则报错，ec=17
    //auto options=boost::filesystem::copy_option::fail_if_exists;//默认方式
    //auto options = boost::filesystem::copy_options::update_existing;//替换既存文件,仅若它旧于被复制的文件(std库)
	boost::filesystem::copy_file(from_p, to_p, options,ec);
    std::cout<<"ec="<<ec<<std::endl;
    if (ec){
        std::cout << "failed" << ec.message()<<std::endl;
        return false;
    }else{
        std::cout << "successed" << std::endl;
        return true;
    }
}
int main() {
	std::string from_path = "../gdb.pdf";
	std::string to_path = "../build/gdb-user.pdf";
	if (CopyFile(from_path, to_path)) {
		std::cout << "copy file successed" << std::endl;
	}
	else {
		std::cout << "copy file failed" << std::endl;
	}
    boost::filesystem::path ph("/home/wlk/workspace/boost_learn_sample/build");
    std::cout<<"IsEmpty="<<ph.filename()<<std::endl;
	return 0;
}