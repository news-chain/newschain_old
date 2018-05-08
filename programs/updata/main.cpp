//
// Created by boy on 18-4-15.
//




#include <newsHelper.h>
#include <iostream>
#include <steemit/protocol/config.hpp>

#include <boost/filesystem.hpp>

int main(){
    try {
        steemit::configManager::getInstance(fc::current_path().string());

        if(!boost::filesystem::exists("temp")){
            boost::filesystem::create_directories("temp");
        }

        for(int i = 0; i < 50; i++){
            std::thread([&](){
                std::string path = "temp/wallet"+ std::to_string(i) +".json";
                newsHelper n("ws://47.100.216.113:7000", path);
//                std::string name = newsHelper::getRandString(10);
            }).detach();

        }



        while(true);

    }catch (const fc::exception &e){
        std::cout << "exception :" << e.what() << std::endl;
    }



    return 0;
}