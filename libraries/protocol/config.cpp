//
// Created by boy on 18-1-3.
//


#include "steemit/protocol/config.hpp"
namespace stpt = steemit::protocol;

namespace steemit {

    configManager::configManager(std::string path)
            : dataPath(path) {
        std::cout << "config manager = " << dataPath << std::endl;
        boost::filesystem::path filepath(dataPath);

        if (!boost::filesystem::exists(filepath)) {
            initConfigureFile();
        } else { // read file
            readConfigFile();
        }
    }


    configManager *configManager::getInstance(std::string path) {
        static configManager *shareInstance = NULL;
        if (!shareInstance) {
            if (path[path.length() - 1] == '/') {
                shareInstance = new configManager(path + "configManager.json");
            } else {
                shareInstance = new configManager(path + "/configManager.json");
            }

        }
//			if(path != "" && shareInstance != NULL){
//				shareInstance->dataPath = path;
//			}

        return shareInstance;
    }

    stpt::version configManager::getVersion() {
        return stpt::version(0, 19, 3);
    }

//    const std::string& configManager::getSteemit_init_private_key(){
//        return "";
//    }
//
//   std::string configManager::getSteemit_chain_id(){
//			return "";
//	}
//


    void configManager::initConfigureFile() {
        boost::property_tree::ptree root;

        //todo, time unit, all use by seconds
        root.put("steemit_init_private_key", "newbitprivatekey");
        root.put("steemit_chain_id", "chainnewbcoin");
        root.put("vests_symbol", "VESTS");
        root.put("steem_symbol", "TESTS");
        root.put("steemit_symbol", "test");
        root.put("sdb_symbol", "TBD");
        root.put("stmd_symbol", "TSTD");
        root.put("steemit_address_prefix", "TST");
        root.put("steemit_cashout_window_seconds", std::to_string(60 * 60));
        //generae time
        root.put("steemit_genesis_time", "1451606400");
        root.put("steemit_mining_time", "1451606400");
        //m
        root.put("steemit_cashout_window_seconds_pre_HS12", "3600");
        root.put("steemit_cashout_window_seconds_pre_HS17", "3600");

        root.put("steemit_second_cashout_window", std::to_string(60 * 60 * 24 * 3));
        root.put("steemit_max_cashout_window_seconds", std::to_string(60 * 60 * 24));
        root.put("steemit_vote_change_lockout_period", std::to_string(60 * 10));

        //vote
        root.put("steemit_upvote_lockout_HF7", "600");
        root.put("steemit_original_min_account_creation_fee", "0");
        root.put("steemit_min_account_creation_fee", "0");

        root.put("steemit_owner_auth_recovery_period", "60");
        root.put("steemit_account_recovery_request_expiration_period", "12");
        root.put("steemit_min_account_creation_fee", "0");
        root.put("steemit_owner_auth_history_tracking_start_block_num", "1");

        root.put("steemit_block_interval", "3");

        root.put("steemit_init_miner_name", "newcoin");
        root.put("steemit_num_init_miners", "2");

        root.put("steemit_max_witnesses", "2");
        root.put("steemit_max_voted_witnesses_HF0", "19");
        root.put("steemit_max_miner_witnesses_HF0", "1");
        root.put("steemit_max_runner_witnesses_HF0", "1");

        root.put("steemit_max_voted_witnesses_HF17", "20");
        root.put("steemit_max_miner_witnesses_HF17", "0");
        root.put("steemit_max_runner_witnesses_HF17", "1");

        root.put("steemit_hardfork_required_witnesses", "17");
        root.put("steemit_max_time_until_expriation", "3600");
        root.put("steemit_max_memo_size", "2048");
        root.put("steemit_max_proxy_recursion_depath", "4");
        root.put("steemit_vesting_withdraw_intervals_pre_hf_16", "104");
        root.put("steemit_vesting_withdraw_intervals", "13");
        root.put("steemit_vesting_withdraw_intervals_seconds", "600"); //a  week = 60 * 60 *24 * 7 = 7 day
        root.put("steemit_max_withdraw_routes", "10");
        root.put("steemit_savings_withdraw_time_day", "259200");   // default 3 days, 3 * 24 * 60 * 60 = 259200 seconds
        root.put("steemit_savings_withdraw_request_limint", "100");
        root.put("steemit_vote_regeneration_seconds", "432000");  //

        root.put("steemit_max_vote_changes", "5");  //
        root.put("steemit_reverse_auction_window_seconds", "1800");  //
        root.put("steemit_min_vote_interval_sec", "3");  //
        root.put("steemit_vote_dust_threshold", "50000000");  //

        root.put("steemit_min_root_comment_interval", "300");
        root.put("steemit_min_reply_interval", "20");
        root.put("steemit_post_average_window", "86400");

        root.put("steemit_100_percent", "10000");

        root.put("steemit_max_account_witness_votes", "30");
        root.put("steemit_post_max_bandwidth", "10000"); //10000 * 4 // 2 posts per 1 days, average 1 every 12 hours

        root.put("steemit_inflation_rate_start_percent",
                 "978");         //        root.put("steemit_post_weight_constant", "100000000");
        root.put("steemit_inflation_reate_stop_percent", "95");
        root.put("steemit_inflation_narrowing_period", "250000");
        root.put("steemit_content_reward_percent", "75");
        root.put("steemit_vesting_fund_percent", "15");

        root.put("steemit_miner_pay_percent", "100");
        root.put("steemit_min_ration", "100000");
        root.put("steemit_max_ration_decay_rate", "1000000");
        root.put("steemit_free_transactions_with_new_account", "100");

        root.put("steemit_bandwidth_average_window_seconds", "604800");

        root.put("steemit_bandwidth_percision", "1000000");
        root.put("steemit_max_comment_depath_pre_hf17", "6");
        root.put("steemit_max_comment_depath", "65535");
        root.put("steemit_soft_max_comment_depath", "255");
        root.put("seeemit_max_reserve_ratio", "20000");

        root.put("steemit_create_account_with_steem_modifier", "30");
        root.put("steemit_create_account_delegation_ratio", "5");
        root.put("steemit_create_account_delegation_time_day", "2592000"); // 30 day : 30 *24 * 60 * 60 = 2592000

        root.put("steemit_mining_reward", "1000"); //
        root.put("steemit_equihash_n", "140"); //
        root.put("steemit_equihas_k", "6"); //

        root.put("steemit_liquidity_timeout_sec", "604800"); // 60 * 60 * 24 * 7
        root.put("steemit_min_liquidity_reward_period_sec", "60"); //
        root.put("steemit_liquidity_reward_period_sec", "3600"); //
        root.put("steemit_liquidity_reward_blocks", "1000"); //
        root.put("steemit_min_liquidity_reward", "1000"); //
        root.put("steemit_min_content_reward", "1000"); //
        root.put("steemit_min_curate_reward", "1000"); //
        root.put("steemit_min_producer_reward", "1000"); //
        root.put("steemit_min_pow_reward", "1000"); //

        root.put("steemit_active_challenge_fee", "2000"); //
        root.put("steemit_owner_challenge_fee", "3000"); //
        root.put("steemit_active_challenge_cooldown_day", "86400"); // 1 day = 24 * 60 * 60
        root.put("steemit_owner_challenge_cooldown_day", "86400"); //

        root.put("steemit_post_reward_fund_name", "post"); //
        root.put("steemit_commeent_reward_fund_name", "comment"); //

        root.put("steemit_recent_rshares_decay_rate_hf17", "2592000"); // 30 days
        root.put("steemit_recent_rshares_decay_rate_hf19", "1986000"); // 15 days

        root.put("steemit_content_constant_hf0", "2000000000000"); //
        root.put("steemit_apr_percent_multiply_per_block", "87"); //
        root.put("steemit_apr_percent_shift_per_block", "83"); //

        root.put("steemit_curate_apr_percent", "3875"); //
        root.put("steemit_content_apr_percent", "3875"); //
        root.put("steemit_liquidity_apr_percent", "750"); //
        root.put("steemit_producer_apr_percent", "750"); //
        root.put("steemit_pow_apr_percent", "750"); //


        root.put("steemit_curation_percent", "0"); //
        root.put("steemit_initminer_percent", "0"); //
        root.put("steemit_author_percent", "2000"); //
        root.put("steemit_pow_percent", "1000"); //
        root.put("steemit_other_percent", "6000"); //          //share
        root.put("steemit_reader_percent", "1000"); //


        root.put("steemit_min_payout_sbd", "20"); //
        root.put("steemit_sbd_stop_percent", "5"); //
        root.put("steemit_sbd_start_percent", "2"); //

        root.put("steemit_min_account_name_length", "3"); //
        root.put("steemit_max_account_name_length", "16"); //

        root.put("steemit_min_permlink_length", "0"); //
        root.put("steemit_max_permlink_length", "256"); //
        root.put("steemit_max_witness_url_length", "2048"); //

        root.put("steemit_init_supply", "0"); //
        root.put("steemit_max_share_supply", "1000000000000000"); //
        root.put("steemit_max_sig_check_depth", "2"); //

        root.put("steemit_min_transaction_size_limit", "1024"); //
        root.put("steemit_seconds_per_year", "1892160000"); //
        root.put("steemit_sbd_interest_compound_interval_sec", "2592000"); //(60*60*24*30)

        root.put("steemit_max_transaction_size", "65536"); //
        root.put("steemit_min_block_size_limit", "65536"); //
        root.put("steemit_max_block_size", "65536"); //

        root.put("steemit_soft_max_block_size", "2097152"); //
        root.put("steemit_min_block_size", "115"); //
        root.put("steemit_blocks_per_hour", "3600"); //
//            root.put("steemit_feed_interval_blocks", "65536"); //

        root.put("steemit_feed_history_window_pre_hf_16", "144"); //
        root.put("steemit_feed_history_window", "98"); //
        root.put("steemit_max_feed_age_seconds", "604800"); //
        root.put("steemit_min_feeds", "3"); //

        root.put("steemit_conversion_delay_pre_hf_16_day", "7"); //
//            root.put("steemit_conversion_delay", "3"); //

        root.put("steemit_min_undo_history", "10"); //
        root.put("steemit_max_undo_history", "10000"); //

        root.put("steemit_blockchain_precision", "1000"); //

        root.put("steemit_blockchain_precision_digits", "3"); //

        root.put("steemit_max_authority_membership", "10"); //
        root.put("steemit_max_asset_whitelist_authorities", "10"); //
        root.put("steemit_max_url_length", "127"); //

        root.put("steemit_irreversible_threshold", "75"); //

        root.put("steemit_miner_account", "miners"); //
        root.put("steemit_null_account", "null"); //
        root.put("steemit_temp_account", "temp"); //
        root.put("steemit_proxy_to_self_account", ""); //

        root.put("post_file", "192.168.2.184:2084/store");
        root.put("post_java", "192.168.2.66:8080/app/v1.1/login/addWaterBill/");

        root.put("cashout_time", "1520826247");
        root.put("cashout_time_step", "120");


        root.put("readComment_max", "20000");
        root.put("shareComment_max", "10000");


        root.put("registPostCoin", "20000");  // min. 5
        root.put("everyReadPostCoin", "100");  // min. 5
        root.put("everySharePostCoin", "1000");  // min 5

        root.put("everySharePostCoin", "1000");  // min 5
        root.put("everySharePostCoin", "1000");  // min 5

        root.put("NewsPrivateEquity", "PrivateEquity");
        root.put("news_private_equity_private_key", "news_private_equity_private_key");

        root.put("NewsEarlyInvestment", "EarlyInvestment");
        root.put("news_early_private_key", "news_early_private_key");

        root.put("NewsTrafficeMarket", "TrafficeMarket");
        root.put("new_traffic_private_key", "new_traffic_private_key");

        root.put("NewsCoreTeam", "CoreTeam");
        root.put("new_core_private_key", "new_core_private_key");

        root.put("NewsFoundation", "Foundation");
        root.put("new_foundation_private_key", "new_foundation_private_key");


        initUserLevel(root);
        boost::property_tree::write_json(dataPath, root);

        std::cerr << "create configManager.json  and init, please modfiy it\n";

        //must modify config
        assert(0);
    }

    void configManager::readConfigFile() {


        try {
            boost::property_tree::ptree root;
            boost::property_tree::read_json<boost::property_tree::ptree>(dataPath, root);
////			steemit_init_private_key = root.get_value("steemit_init_private_key");
            for (boost::property_tree::ptree::iterator it = root.begin(); it != root.end(); it++) {
                std::string key = it->first;
                auto value = root.get<std::string>(key);
                m_json[key] = value;
            }
        }catch (std::exception e){
            wlog("canot update configManager file ${e}", ("e", e.what()));
        }


    }


    std::string &configManager::getValueForKey_tostring(std::string key) {
        findKey(key);
        std::string value = m_json[key];
        return m_json[key];
    }

    uint64_t configManager::getValueForKey_touint64_t(std::string key) {
        findKey(key);
        std::string value = m_json[key];
        uint64_t ret = std::stoi(value);
        return ret;
    }

    uint64_t configManager::getVests_symbol() {
        uint64_t ret = 6;
        std::string value = m_json["vests_symbol"];
        for (int i = 0; i < value.length(); i++) {
            uint64_t c = (uint64_t) (char) (value[i]);
            ret |= (c << (8 * (i + 1)));
        }
        return ret;
    }

    uint64_t configManager::getSteem_symbol() {
        uint64_t ret = 3;
        std::string value = m_json["steem_symbol"];
        for (int i = 0; i < value.length(); i++) {
            uint64_t c = (uint64_t) (char) (value[i]);
            ret |= (c << (8 * (i + 1)));
        }
        return ret;
    }

    uint64_t configManager::getStmd_symbol() {
        uint64_t ret = 3;
        std::string value = m_json["stmd_sybol"];
        for (int i = 0; i < value.length(); i++) {
            uint64_t c = (uint64_t) (char) (value[i]);
            ret |= (c << (8 * (i + 1)));
        }
        return ret;
    }

    uint64_t configManager::getSdb_symbol() {
        uint64_t ret = 3;
        std::string value = m_json["sdb_symbol"];
        for (int i = 0; i < value.length(); i++) {
            uint64_t c = (uint64_t) (char) (value[i]);
            ret |= (c << (8 * (i + 1)));
        }
        return ret;
    }

    fc::time_point_sec configManager::getTime_point_sec_byKey(std::string key) {
        findKey(key);
        std::string value = m_json[key];
        unsigned long ret = std::stol(value);
        return fc::time_point_sec(ret);
    }

    fc::microseconds configManager::getTime_seconds_byKey(std::string key) {
        findKey(key);
        std::string value = m_json[key];
        uint64_t ret = std::stol(value);
        return fc::seconds(ret);
    }



    int configManager::getValueForkey_toInt(std::string key) {
        findKey(key);
        std::string value = m_json[key];

        int ret = std::stol(value);
        return ret;
    }


    std::map<std::string, std::map<uint32_t, uint32_t>> &configManager::getLevelInfo() {
        static std::map<std::string, std::map<uint32_t, uint32_t>> mm;
        if (mm.size() == 0) {
            boost::property_tree::ptree root;
            boost::property_tree::read_json<boost::property_tree::ptree>(dataPath, root);
            boost::property_tree::ptree level = root.get_child("level");
            if (level.size() == 0) {
                assert(0);
            }
            //reader
            boost::property_tree::ptree readerLevel = level.get_child("reader");
            boost::property_tree::ptree shareLevel = level.get_child("share");
            boost::property_tree::ptree writeLevel = level.get_child("write");

            std::map<uint32_t, uint32_t> reader;
            for (auto itr = readerLevel.begin(); itr != readerLevel.end(); itr++) {
                std::string key = itr->first;
                auto value = readerLevel.get<std::string>(key);
                reader[std::stol(key)] = std::stol(value);
            }

            //share
            std::map<uint32_t, uint32_t> share;
            for (auto itr = shareLevel.begin(); itr != shareLevel.end(); itr++) {
                std::string key = itr->first;
                auto value = shareLevel.get<std::string>(key);
                share[std::stol(key)] = std::stol(value);
            }
            //write
            std::map<uint32_t, uint32_t> write;
            for (auto itr = writeLevel.begin(); itr != writeLevel.end(); itr++) {
                std::string key = itr->first;
                auto value = writeLevel.get<std::string>(key);
                write[std::stol(key)] = std::stol(value);
            }

            mm["reader"] = reader;
            mm["share"] = share;
            mm["write"] = write;
        }

        int size = mm.size();
        return mm;
    }

    void configManager::initUserLevel(boost::property_tree::ptree &root) {
        //add user level
        boost::property_tree::ptree level;
        boost::property_tree::ptree readerLevel;
        boost::property_tree::ptree shareLevel;
        boost::property_tree::ptree writeLevel;

        readerLevel.put("1", "10");
        readerLevel.put("2", "50");
        readerLevel.put("3", "100");
        readerLevel.put("4", "300");
        readerLevel.put("5", "500");
        readerLevel.put("6", "1000");
        readerLevel.put("7", "2000");
        readerLevel.put("8", "5000");
        readerLevel.put("9", "8000");
        readerLevel.put("10", "10000");

        shareLevel.put("1", "5");
        shareLevel.put("2", "10");
        shareLevel.put("3", "15");
        shareLevel.put("4", "20");
        shareLevel.put("5", "50");
        shareLevel.put("6", "100");
        shareLevel.put("7", "200");
        shareLevel.put("8", "500");
        shareLevel.put("9", "800");
        shareLevel.put("10", "1000");

        writeLevel.put("1", "5");
        writeLevel.put("2", "10");
        writeLevel.put("3", "15");
        writeLevel.put("4", "20");
        writeLevel.put("5", "50");
        writeLevel.put("6", "100");
        writeLevel.put("7", "200");
        writeLevel.put("8", "500");
        writeLevel.put("9", "800");
        writeLevel.put("10", "1000");


        level.put_child("reader", readerLevel);
        level.put_child("share", shareLevel);
        level.put_child("write", writeLevel);


        root.put_child("level", level);
        root.put("readLevelStep", "1");
        root.put("writeLevelStep", "1");
        root.put("shareLevelStep", "1");
    }


    uint32_t configManager::getReaderLevelStep() {
        std::string key = "readLevelStep";
        findKey(key);
        int ret = std::stoi(m_json[key]);
        return ret;
    }

    uint32_t configManager::getShareLevelStep() {
        std::string key = "shareLevelStep";
        findKey(key);
        int ret = std::stoi(m_json[key]);
        return ret;
    }

    uint32_t configManager::getAuthorLevelStep() {
        std::string key = "writeLevelStep";
        findKey(key);
        int ret = std::stoi(m_json[key]);
        return ret;
    }


    std::string configManager::getPost_history_url() {
        std::string key = "post_history_url";
        findKey(key);
        return m_json[key];
    }

    bool configManager::get_cashout_exp(fc::time_point_sec time) {
        uint32_t value = getTime_point_sec_byKey("cashout_time").sec_since_epoch();
        if(value == 0){
//            update_cashout_time();
            return false;
        }
        if(value > time.sec_since_epoch()){
            return false;
        }
        return true;
    }

    void configManager::update_cashout_time(fc::time_point begin) {

        long step_time = std::stol(m_json["cashout_time_step"]);
        uint32_t time = begin.sec_since_epoch();
        time += step_time;
        m_json["cashout_time"] = std::to_string(time);

        try {
            boost::property_tree::ptree root;
            boost::property_tree::read_json<boost::property_tree::ptree>(dataPath, root);

            root.put("cashout_time", std::to_string(time));

            boost::property_tree::write_json(dataPath, root);

            readConfigFile();
        }catch (...){
            elog("error!!!!!!!!!!  update cashout time error!");
        }



    }
}


