
#include "NetworkRequest.h"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/program_options.hpp>



namespace bpo = boost::program_options;



void printHelp()
{
    std::cout << "--server ; server address " << std::endl;
    std::cout << "--port ; server port;" << std::endl;
    std::cout << "--numbers, create accounts numbers" << std::endl;
    std::cout << "--path, save file path, default current path" << std::endl;
    std::cout << "--prefix, account prefix" << std::endl;
}



int main(int argc, const char *argv[]){



    bpo::options_description app_desc;
    app_desc.add_options()
    ("help", "help and exit")
    ("server",bpo::value<std::string>(), "server address")
    ("port",bpo::value<std::string>(), "server port")
    ("numbers",bpo::value<std::string>(), "create accounts numbers")
    ("paths",bpo::value<std::string>(), "save file path")
    ("prefix",bpo::value<std::string>(), "account prefix");
    
    bpo::variables_map op;
    try {
        bpo::store(bpo::parse_command_line(argc, argv, app_desc), op);
    } catch (const boost::program_options::error &e) {
        std::cerr << "error command line " << e.what() << std::endl;
        printHelp();
        return 1;
    }
    
    if(op.count("help")){
        printHelp();
        return 0;
    }
    std::string path;
    std::string server;
    std::string port;
    std::string prefix;
    std::string num;
    if(op.count("server")){
        server = op.at("server").as<std::string>();
    }
    else{
        printHelp();
        return 1;

    }
    
    if(op.count("port")){
        port = op["port"].as<std::string>();
    }else{
        printHelp();
        return 1;
    }
    
    if(op.count("numbers")){
        num = op["numbers"].as<std::string>();
    }else{
        num = 10;
    }
    
    if(op.count("prefix")){
        prefix = op["prefix"].as<std::string>();
    }
    else{
        prefix = "zsmwtest";
    }
    
    if(op.count("path")){
        path = op["path"].as<std::string>();
    }
    else{
        path = boost::filesystem::current_path().string() + "/account.json";
    }

    boost::property_tree::ptree root;
    
    for(int i = 0; i < std::atoi(num.c_str()); i++){
        std::string account = prefix + std::to_string(i);
        std::string json = "{\"jsonrpc\": \"2.0\", \"method\": \"create_account\", \"params\": [\"initminer\", \""+ account +"\", \"\",  \"true\"], \"id\": 10}";
        std::string data = PostRequest(server.c_str(), port.c_str(), json);
        root.put(std::to_string(i), data);
    }
    
    
    boost::property_tree::write_json(path, root);

    return 0;
}
