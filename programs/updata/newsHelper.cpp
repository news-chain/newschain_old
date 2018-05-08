//
// Created by boy on 18-4-15.
//

#include "newsHelper.h"
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

using namespace graphene::utilities;
using namespace steemit::app;
using namespace steemit::chain;
using namespace steemit::wallet;
using namespace std;
namespace bpo = boost::program_options;

newsHelper::newsHelper(std::string server_endpoint, std::string wallet_file) {

    wallet_data wdata;
    if(wallet_file.size() == 0){
        FC_ASSERT("wallet_file size == 0");
    }
    if( fc::exists( wallet_file ) )
    {
        wdata = fc::json::from_file( wallet_file ).as<wallet_data>();
    }

    wdata.ws_server = server_endpoint;
    fc::http::websocket_client client("_default");
    auto con  = client.connect( wdata.ws_server );
    auto apic = std::make_shared<fc::rpc::websocket_api_connection>(*con);

    auto remote_api = apic->get_remote_api< login_api >(1);
    FC_ASSERT( remote_api->login( wdata.ws_user, wdata.ws_password ) );
    m_wallet_api = std::make_shared<wallet_api>( std::move(wdata), std::move(remote_api) );
    m_wallet_api->set_wallet_filename( wallet_file);
    fc::api<wallet_api> m_wapi(m_wallet_api);
    m_wapi->save_wallet_file(wallet_file);
    if(!m_wallet_api->load_wallet_file()){
        std::cout << "cant load wallet file\n";
    }



    m_wapi->set_password("123456");
    m_wapi->import_key("5JG2b4VBLLaMFLzsxz57NjRC3hNSo2GyZ6W7DAQS7xdtn4Z12kg");

    string tag = "news";
    for(int i = 0; i < 50; i++){
        auto start = fc::time_point::now();
        std::string user = getRandString(16);
        m_wapi->create_account("newcoin", user, "111", true);
        auto end = fc::time_point::now();
        auto cost = end.time_since_epoch() - start.time_since_epoch();
        elog("====================create_account = end - start ${n}, user:${u}", ("n", cost)("u", user));
        m_wapi->post_comment(user, getRandString(20), "", tag, getRandString(10), getRandString(30), "", true);
        auto end1 = fc::time_point::now();
        cost = end1.time_since_epoch() - end.time_since_epoch();
        elog("====================create_comment = end - start ${n}, user:${u}", ("n", cost)("u", user));
    }
    wlog("thread end ================");
}






void newsHelper::create_account(std::string name) {
//    m_wapi->create_account("newcoin", name, "111", true);
}






std::string newsHelper::getRandString(uint16_t length) {
    static std::string ccc = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    boost::random::random_device rng;
    boost::random::uniform_int_distribution<> index_dist(0, ccc.size() - 1);
    std::string result;
    for(uint16_t i = 0; i < length; i++){
        result += ccc[index_dist(rng)];
    }
    return result;
}



