//
// Created by boy on 18-4-15.
//

#ifndef STEEM_NEWSHELPER_H
#define STEEM_NEWSHELPER_H

#include <string>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>

#include <fc/io/json.hpp>
#include <fc/io/stdio.hpp>
#include <fc/network/http/server.hpp>
#include <fc/network/http/websocket.hpp>
#include <fc/rpc/cli.hpp>
#include <fc/rpc/http_api.hpp>
#include <fc/rpc/websocket_api.hpp>
#include <fc/smart_ref_impl.hpp>

#include <graphene/utilities/key_conversion.hpp>

#include <steemit/app/api.hpp>
#include <steemit/protocol/protocol.hpp>
#include <steemit/wallet/wallet.hpp>

#include <fc/interprocess/signals.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

#include <fc/log/console_appender.hpp>
#include <fc/log/file_appender.hpp>
#include <fc/log/logger.hpp>
#include <fc/log/logger_config.hpp>

using namespace graphene::utilities;
using namespace steemit::app;
using namespace steemit::chain;
using namespace steemit::wallet;
//using namespace std;
namespace bpo = boost::program_options;

class newsHelper {
public:
    newsHelper(std::string server_endpoint, std::string wallet_file);


    static std::string getRandString(uint16_t length);

    void create_account(std::string name);
private:
    fc::api<steemit::wallet::wallet_api> m_wapi;
//    wallet_data m_wdata;
    std::shared_ptr<wallet_api> m_wallet_api;
};


#endif //STEEM_NEWSHELPER_H
