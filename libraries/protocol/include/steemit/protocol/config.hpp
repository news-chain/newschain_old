/*
 * Copyright (c) 2016 Steemit, Inc., and contributors.
 */
#pragma once

#include <fc/filesystem.hpp>
#include <fc/variant_object.hpp>
#include <fc/time.hpp>
#include <steemit/protocol/version.hpp>
#include <fc/crypto/elliptic.hpp>
#include <boost/filesystem.hpp>
#include <fc/uint128.hpp>
#include <iostream>
#include <fstream>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/thread/mutex.hpp>


namespace stpt = steemit::protocol;
//using fc::uint128_t;
namespace steemit {
    class configManager {
    public:
        static configManager *getInstance(std::string path = "");

        stpt::version getVersion();

//        const std::string &getSteemit_init_private_key();
//
//        std::string getSteemit_chain_id();
//
        uint64_t getVests_symbol();

        uint64_t getSteem_symbol();

        uint64_t getSdb_symbol();

//
        uint64_t getStmd_symbol();

        std::string &getValueForKey_tostring(std::string key);

        uint64_t getValueForKey_touint64_t(std::string key);

        fc::time_point_sec getTime_point_sec_byKey(std::string key);

        fc::microseconds getTime_seconds_byKey(std::string key);


        int getValueForkey_toInt(std::string key);

        std::map<std::string, std::map<uint32_t, uint32_t>>& getLevelInfo();

        uint32_t getReaderLevelStep();
        uint32_t getShareLevelStep();
        uint32_t getAuthorLevelStep();

        std::string getPost_history_url();

        bool get_cashout_exp(fc::time_point_sec time);
        void update_cashout_time(fc::time_point begin);
    private:
        std::string dataPath;
        configManager(std::string path);


        /*
         if not exists config file, create file and init data.
         */
        void initConfigureFile();

        void initUserLevel(boost::property_tree::ptree &root);

        void readConfigFile();

        inline void findKey(std::string key){
            if(m_json[key].length() == 0){
                std::cerr << " error! cannot find key: " << key << std::endl;
                assert(0);
            }
        }

        std::map<std::string, std::string> m_json;
    };
}

#define CONFIGMANAGE        (steemit::configManager::getInstance())

#define STEEMIT_BLOCKCHAIN_VERSION                ( CONFIGMANAGE->getVersion() )
#define STEEMIT_BLOCKCHAIN_HARDFORK_VERSION     ( hardfork_version( STEEMIT_BLOCKCHAIN_VERSION ) )

//
#define STEEMIT_INIT_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("ad0001"))))
#define STEEMIT_INIT_PUBLIC_KEY_STR             (std::string( steemit::protocol::public_key_type(STEEMIT_INIT_PRIVATE_KEY.get_public_key()) ))
#define STEEMIT_CHAIN_ID                        (fc::sha256::hash(std::string("newschainid")))

//#define VESTS_SYMBOL  (CONFIGMANAGE->getVests_symbol())
//#define STEEM_SYMBOL  (CONFIGMANAGE->getSteem_symbol())
//#define SBD_SYMBOL  (CONFIGMANAGE->getSdb_symbol())
//#define STMD_SYMBOL  (CONFIGMANAGE->getStmd_symbol())
#define VESTS_SYMBOL  (uint64_t(6) | (uint64_t('V') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< VESTS with 6 digits of precision
#define STEEM_SYMBOL  (uint64_t(3) | (uint64_t('T') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< STEEM with 3 digits of precision
#define SBD_SYMBOL    (uint64_t(3) | (uint64_t('T') << 8) | (uint64_t('B') << 16) | (uint64_t('D') << 24) ) ///< Test Backed Dollars with 3 digits of precision
#define STMD_SYMBOL   (uint64_t(3) | (uint64_t('T') << 8) | (uint64_t('S') << 16) | (uint64_t('T') << 24) | (uint64_t('D') << 32) ) ///< Test Dollars with 3 digits of precision

#define STEEMIT_SYMBOL                          "TEST"
#define STEEMIT_ADDRESS_PREFIX                  "NT"


#define NEWS_SYMBOL    (uint64_t(3) | (uint64_t('N') << 8) | (uint64_t('E') << 16) | (uint64_t('W') << 24) | (uint64_t('T') << 32)) ///< STEEM with 3 digits of precision
#define NEWS_TOKEN_SYMBOL                        "NEWT"
#define NEWS_ADDRESS_PREFIX                      "NT"

//#define STEEMIT_GENESIS_TIME                    (CONFIGMANAGE->getTime_point_sec_byKey("steemit_genesis_time"))
#define STEEMIT_GENESIS_TIME                    (fc::time_point_sec(1451606400))
#define STEEMIT_MINING_TIME                    (fc::time_point_sec(1451606400))
//#define STEEMIT_MINING_TIME                     (CONFIGMANAGE->getTime_point_sec_byKey("steemit_mining_time"))
#define STEEMIT_CASHOUT_WINDOW_SECONDS          (CONFIGMANAGE->getValueForKey_touint64_t("steemit_cashout_window_seconds")) /// 1 hr
#define STEEMIT_CASHOUT_WINDOW_SECONDS_PRE_HF12 (STEEMIT_CASHOUT_WINDOW_SECONDS)
#define STEEMIT_CASHOUT_WINDOW_SECONDS_PRE_HF17 (STEEMIT_CASHOUT_WINDOW_SECONDS)
#define STEEMIT_SECOND_CASHOUT_WINDOW           (CONFIGMANAGE->getValueForKey_touint64_t("steemit_second_cashout_window")) /// 3 days
#define STEEMIT_MAX_CASHOUT_WINDOW_SECONDS      (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_cashout_window_seconds")) /// 1 day
#define STEEMIT_VOTE_CHANGE_LOCKOUT_PERIOD      (CONFIGMANAGE->getValueForKey_touint64_t("steemit_vote_change_lockout_period")) /// 10 minutes
#define STEEMIT_UPVOTE_LOCKOUT_HF7              (fc::minutes(1))
#define STEEMIT_UPVOTE_LOCKOUT_HF17             (fc::minutes(5))


#define STEEMIT_ORIGINAL_MIN_ACCOUNT_CREATION_FEE (CONFIGMANAGE->getValueForKey_touint64_t("steemit_original_min_account_creation_fee"))
#define STEEMIT_MIN_ACCOUNT_CREATION_FEE          (CONFIGMANAGE->getValueForKey_touint64_t("steemit_min_account_creation_fee"))

#define STEEMIT_OWNER_AUTH_RECOVERY_PERIOD                  (CONFIGMANAGE->getTime_seconds_byKey("steemit_owner_auth_recovery_period"))
#define STEEMIT_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  (CONFIGMANAGE->getTime_seconds_byKey("steemit_account_recovery_request_expiration_period"))
#define STEEMIT_OWNER_UPDATE_LIMIT                          (CONFIGMANAGE->getTime_seconds_byKey("steemit_owner_update_limit"))
#define STEEMIT_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM (CONFIGMANAGE->getValueForKey_touint64_t("steemit_owner_auth_history_tracking_start_block_num"))
//#else // IS LIVE STEEM NETWORK
//
//#define STEEMIT_INIT_PUBLIC_KEY_STR             "STM8GC13uCZbP44HzMLV6zPZGwVQ8Nt4Kji8PapsPiNq1BK153XTX"
//#define STEEMIT_CHAIN_ID                        (steemit::protocol::chain_id_type())
//#define VESTS_SYMBOL  (uint64_t(6) | (uint64_t('V') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< VESTS with 6 digits of precision
//#define STEEM_SYMBOL  (uint64_t(3) | (uint64_t('S') << 8) | (uint64_t('T') << 16) | (uint64_t('E') << 24) | (uint64_t('E') << 32) | (uint64_t('M') << 40)) ///< STEEM with 3 digits of precision
//#define SBD_SYMBOL    (uint64_t(3) | (uint64_t('S') << 8) | (uint64_t('B') << 16) | (uint64_t('D') << 24) ) ///< STEEM Backed Dollars with 3 digits of precision
//#define STMD_SYMBOL   (uint64_t(3) | (uint64_t('S') << 8) | (uint64_t('T') << 16) | (uint64_t('M') << 24) | (uint64_t('D') << 32) ) ///< STEEM Dollars with 3 digits of precision
//#define STEEMIT_SYMBOL                          "STEEM"
//#define STEEMIT_ADDRESS_PREFIX                  "STM"
//
//#define STEEMIT_GENESIS_TIME                    (fc::time_point_sec(1458835200))
//#define STEEMIT_MINING_TIME                     (fc::time_point_sec(1458838800))
//#define STEEMIT_CASHOUT_WINDOW_SECONDS_PRE_HF12 (60*60*24)    /// 1 day
//#define STEEMIT_CASHOUT_WINDOW_SECONDS_PRE_HF17 (60*60*12)    /// 12 hours
//#define STEEMIT_CASHOUT_WINDOW_SECONDS          (60*60*24*7)  /// 7 days
//#define STEEMIT_SECOND_CASHOUT_WINDOW           (60*60*24*30) /// 30 days
//#define STEEMIT_MAX_CASHOUT_WINDOW_SECONDS      (60*60*24*14) /// 2 weeks
//#define STEEMIT_VOTE_CHANGE_LOCKOUT_PERIOD      (60*60*2)     /// 2 hours
//#define STEEMIT_UPVOTE_LOCKOUT_HF7              (fc::minutes(1))
//#define STEEMIT_UPVOTE_LOCKOUT_HF17             (fc::hours(12))
//
//#define STEEMIT_ORIGINAL_MIN_ACCOUNT_CREATION_FEE  100000
//#define STEEMIT_MIN_ACCOUNT_CREATION_FEE           1
//
//#define STEEMIT_OWNER_AUTH_RECOVERY_PERIOD                  fc::days(30)
//#define STEEMIT_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::days(1)
//#define STEEMIT_OWNER_UPDATE_LIMIT                          fc::minutes(60)
//#define STEEMIT_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 3186477
//
//#endif

//#define STEEMIT_BLOCK_INTERVAL                  (CONFIGMANAGE->getValueForKey_touint64_t("steemit_block_interval"))
#define STEEMIT_BLOCK_INTERVAL                  3
#define STEEMIT_BLOCKS_PER_YEAR                 (365*24*60*60/STEEMIT_BLOCK_INTERVAL)
#define STEEMIT_BLOCKS_PER_DAY                  (24*60*60/STEEMIT_BLOCK_INTERVAL)
#define STEEMIT_START_VESTING_BLOCK             (STEEMIT_BLOCKS_PER_DAY * 7)
#define STEEMIT_START_MINER_VOTING_BLOCK        (STEEMIT_BLOCKS_PER_DAY * 30)

#define STEEMIT_INIT_MINER_NAME                 (CONFIGMANAGE->getValueForKey_tostring("steemit_init_miner_name"))
#define STEEMIT_NUM_INIT_MINERS                 (CONFIGMANAGE->getValueForKey_touint64_t("steemit_num_init_miners"))

#define STEEMIT_INIT_TIME                       (fc::time_point_sec());

//#define STEEMIT_MAX_WITNESSES                   (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_witnesses"))
#define STEEMIT_MAX_WITNESSES                   21

#define STEEMIT_MAX_VOTED_WITNESSES_HF0         19
#define STEEMIT_MAX_MINER_WITNESSES_HF0         1
#define STEEMIT_MAX_RUNNER_WITNESSES_HF0        1
//#define STEEMIT_MAX_VOTED_WITNESSES_HF0         (CONFIGMANAGE->getValueForkey_toInt("steemit_max_voted_witnesses_HF0"))
//#define STEEMIT_MAX_MINER_WITNESSES_HF0         (CONFIGMANAGE->getValueForkey_toInt("steemit_max_miner_witnesses_HF0"))
//#define STEEMIT_MAX_RUNNER_WITNESSES_HF0        (CONFIGMANAGE->getValueForkey_toInt("steemit_max_runner_witnesses_HF0"))

#define STEEMIT_MAX_VOTED_WITNESSES_HF17        20
#define STEEMIT_MAX_MINER_WITNESSES_HF17        0
#define STEEMIT_MAX_RUNNER_WITNESSES_HF17       1
//#define STEEMIT_MAX_VOTED_WITNESSES_HF17        (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_voted_witnesses_HF17"))
//#define STEEMIT_MAX_MINER_WITNESSES_HF17        (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_m
//
//
//
//
// iner_witnesses_HF17"))
//#define STEEMIT_MAX_RUNNER_WITNESSES_HF17       (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_runner_witnesses_HF17"))

// 17 of the 21 dpos witnesses (20 elected and 1 virtual time) required for hardfork. This guarantees 75% participation on all subsequent rounds.
#define STEEMIT_HARDFORK_REQUIRED_WITNESSES     (CONFIGMANAGE->getValueForKey_touint64_t("steemit_hardfork_required_witnesses"))
#define STEEMIT_MAX_TIME_UNTIL_EXPIRATION       (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_time_until_expriation")) // seconds,  aka: 1 hour
#define STEEMIT_MAX_MEMO_SIZE                   (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_memo_size"))
//#define STEEMIT_MAX_PROXY_RECURSION_DEPTH       (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_proxy_recursion_depath"))
#define STEEMIT_MAX_PROXY_RECURSION_DEPTH       4

#define STEEMIT_VESTING_WITHDRAW_INTERVALS_PRE_HF_16 (CONFIGMANAGE->getValueForKey_touint64_t("steemit_vesting_withdraw_intervals_pre_hf_16"))
#define STEEMIT_VESTING_WITHDRAW_INTERVALS      (CONFIGMANAGE->getValueForKey_touint64_t("steemit_vesting_withdraw_intervals"))
#define STEEMIT_VESTING_WITHDRAW_INTERVAL_SECONDS (CONFIGMANAGE->getValueForKey_touint64_t("steemit_vesting_withdraw_intervals_seconds")) /// 1 week per interval
#define STEEMIT_MAX_WITHDRAW_ROUTES             (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_withdraw_routes"))
#define STEEMIT_SAVINGS_WITHDRAW_TIME            (CONFIGMANAGE->getTime_seconds_byKey("steemit_savings_withdraw_time_day"))
#define STEEMIT_SAVINGS_WITHDRAW_REQUEST_LIMIT  (CONFIGMANAGE->getValueForKey_touint64_t("steemit_savings_withdraw_request_limint"))
#define STEEMIT_VOTE_REGENERATION_SECONDS       (CONFIGMANAGE->getValueForKey_touint64_t("steemit_vote_regeneration_seconds")) // 5 day 5*24*60*60=432000

#define STEEMIT_MAX_VOTE_CHANGES                (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_vote_changes"))
#define STEEMIT_REVERSE_AUCTION_WINDOW_SECONDS   (CONFIGMANAGE->getValueForKey_touint64_t("steemit_reverse_auction_window_seconds")) /// 30 minutes
#define STEEMIT_MIN_VOTE_INTERVAL_SEC            (CONFIGMANAGE->getValueForKey_touint64_t("steemit_min_vote_interval_sec"))
#define STEEMIT_VOTE_DUST_THRESHOLD              (CONFIGMANAGE->getValueForKey_touint64_t("steemit_vote_dust_threshold"))

#define STEEMIT_MIN_ROOT_COMMENT_INTERVAL       (CONFIGMANAGE->getTime_seconds_byKey("steemit_min_root_comment_interval")) // 5 minutes
#define STEEMIT_MIN_REPLY_INTERVAL              (CONFIGMANAGE->getTime_seconds_byKey("steemit_min_reply_interval")) // 20 seconds
//#define STEEMIT_POST_AVERAGE_WINDOW             (CONFIGMANAGE->getValueForkey_toInt("steemit_post_average_window")) // 1 day
#define STEEMIT_POST_AVERAGE_WINDOW             (60*60*24u)
#define STEEMIT_POST_MAX_BANDWIDTH              (4*STEEMIT_100_PERCENT) // 2 posts per 1 days, average 1 every 12 hours
#define STEEMIT_POST_WEIGHT_CONSTANT            (uint64_t(STEEMIT_POST_MAX_BANDWIDTH) * STEEMIT_POST_MAX_BANDWIDTH)

#define STEEMIT_MAX_ACCOUNT_WITNESS_VOTES        (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_account_witness_votes"))

#define STEEMIT_100_PERCENT                     10000
//#define STEEMIT_100_PERCENT                     (CONFIGMANAGE->getValueForKey_touint64_t("steemit_100_percent"))
#define STEEMIT_1_PERCENT                       (STEEMIT_100_PERCENT/100)
#define STEEMIT_1_TENTH_PERCENT                 (STEEMIT_100_PERCENT/1000)
#define STEEMIT_DEFAULT_SBD_INTEREST_RATE       (10*STEEMIT_1_PERCENT) ///< 10% APR

#define STEEMIT_INFLATION_RATE_START_PERCENT     (CONFIGMANAGE->getValueForKey_touint64_t("steemit_inflation_rate_start_percent")) // Fixes block 7,000,000 to 9.5%
#define STEEMIT_INFLATION_RATE_STOP_PERCENT      (CONFIGMANAGE->getValueForKey_touint64_t("steemit_inflation_reate_stop_percent")) // 0.95%
#define STEEMIT_INFLATION_NARROWING_PERIOD       (CONFIGMANAGE->getValueForKey_touint64_t("steemit_inflation_narrowing_period")) // Narrow 0.01% every 250k blocks
#define STEEMIT_CONTENT_REWARD_PERCENT          (((CONFIGMANAGE->getValueForKey_touint64_t("steemit_content_reward_percent")))*STEEMIT_1_PERCENT) //75% of inflation, 7.125% inflation
#define STEEMIT_VESTING_FUND_PERCENT            (((CONFIGMANAGE->getValueForKey_touint64_t("steemit_vesting_fund_percent")))*STEEMIT_1_PERCENT) //15% of inflation, 1.425% inflation

#define STEEMIT_MINER_PAY_PERCENT               ((CONFIGMANAGE->getValueForKey_touint64_t("steemit_miner_pay_percent"))) // 1%
#define STEEMIT_MIN_RATION                      (CONFIGMANAGE->getValueForKey_touint64_t("steemit_min_ration"))
#define STEEMIT_MAX_RATION_DECAY_RATE           ((CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_ration_decay_rate")))
#define STEEMIT_FREE_TRANSACTIONS_WITH_NEW_ACCOUNT  (CONFIGMANAGE->getValueForKey_touint64_t("steemit_free_transactions_with_new_account"))

#define STEEMIT_BANDWIDTH_AVERAGE_WINDOW_SECONDS ((CONFIGMANAGE->getValueForKey_touint64_t("steemit_bandwidth_average_window_seconds"))) ///< 1 week
#define STEEMIT_BANDWIDTH_PRECISION             ((CONFIGMANAGE->getValueForKey_touint64_t("steemit_bandwidth_percision"))) ///< 1 million
#define STEEMIT_MAX_COMMENT_DEPTH_PRE_HF17       (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_comment_depath_pre_hf17"))
#define STEEMIT_MAX_COMMENT_DEPTH                (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_comment_depath")) // 64k
#define STEEMIT_SOFT_MAX_COMMENT_DEPTH           (CONFIGMANAGE->getValueForKey_touint64_t("steemit_soft_max_comment_depath")) // 255

#define STEEMIT_MAX_RESERVE_RATIO               ( (CONFIGMANAGE->getValueForKey_touint64_t("seeemit_max_reserve_ratio")))

#define STEEMIT_CREATE_ACCOUNT_WITH_STEEM_MODIFIER  (CONFIGMANAGE->getValueForKey_touint64_t("steemit_create_account_with_steem_modifier"))
#define STEEMIT_CREATE_ACCOUNT_DELEGATION_RATIO     (CONFIGMANAGE->getValueForKey_touint64_t("steemit_create_account_delegation_ratio"))
#define STEEMIT_CREATE_ACCOUNT_DELEGATION_TIME      (CONFIGMANAGE->getTime_seconds_byKey("steemit_create_account_delegation_time_day"))

//#define STEEMIT_MINING_REWARD                   asset((CONFIGMANAGE->getValueForKey_touint64_t("stemit_mining_reward")), STEEM_SYMBOL )
#define STEEMIT_MINING_REWARD                   asset(1000, STEEM_SYMBOL )
#define STEEMIT_EQUIHASH_N                       (CONFIGMANAGE->getValueForKey_touint64_t("steemit_equihash_n"))
#define STEEMIT_EQUIHASH_K                       (CONFIGMANAGE->getValueForKey_touint64_t("steemit_equihas_k"))

#define STEEMIT_LIQUIDITY_TIMEOUT_SEC           ((CONFIGMANAGE->getTime_seconds_byKey("steemit_liquidity_timeout_sec"))) // After one week volume is set to 0
//#define STEEMIT_MIN_LIQUIDITY_REWARD_PERIOD_SEC ((CONFIGMANAGE->getTime_seconds_byKey("steemit_min_liquidity_reward_period_sec"))) // 1 minute required on books to receive volume
#define STEEMIT_MIN_LIQUIDITY_REWARD_PERIOD_SEC (fc::seconds(60)) // 1 minute required on books to receive volume
//#define STEEMIT_LIQUIDITY_REWARD_PERIOD_SEC     ( (CONFIGMANAGE->getValueForKey_touint64_t("steemit_liquidity_reward_blocks")))
#define STEEMIT_LIQUIDITY_REWARD_PERIOD_SEC     (60 * 60)
#define STEEMIT_LIQUIDITY_REWARD_BLOCKS         (STEEMIT_LIQUIDITY_REWARD_PERIOD_SEC/STEEMIT_BLOCK_INTERVAL)
#define STEEMIT_MIN_LIQUIDITY_REWARD            (asset(  (CONFIGMANAGE->getValueForKey_touint64_t("steemit_liquidity_reward_blocks"))*STEEMIT_LIQUIDITY_REWARD_BLOCKS, STEEM_SYMBOL )) // Minumum reward to be paid out to liquidity providers
//#define STEEMIT_MIN_CONTENT_REWARD               (CONFIGMANAGE->getValueForKey_touint64_t("steemit_min_content_reward"))
#define STEEMIT_MIN_CONTENT_REWARD              STEEMIT_MINING_REWARD                                //#define STEEMIT_MIN_CONTENT_REWARD               (CONFIGMANAGE->getValueForKey_touint64_t("steemit_min_content_reward"))
#define STEEMIT_MIN_CURATE_REWARD               STEEMIT_MINING_REWARD                              //#define STEEMIT_MIN_CURATE_REWARD                (CONFIGMANAGE->getValueForKey_touint64_t("steemit_min_curate_reward"))
#define STEEMIT_MIN_PRODUCER_REWARD             STEEMIT_MINING_REWARD                                    //#define STEEMIT_MIN_PRODUCER_REWARD              (CONFIGMANAGE->getValueForKey_touint64_t("steemit_min_producer_reward"))
#define STEEMIT_MIN_POW_REWARD                  STEEMIT_MINING_REWARD                          //#define STEEMIT_MIN_POW_REWARD                   (CONFIGMANAGE->getValueForKey_touint64_t("steemit_min_pow_reward"))

#define STEEMIT_ACTIVE_CHALLENGE_FEE            asset(  (CONFIGMANAGE->getValueForKey_touint64_t("steemit_active_challenge_fee")), STEEM_SYMBOL )
#define STEEMIT_OWNER_CHALLENGE_FEE             asset(  (CONFIGMANAGE->getValueForKey_touint64_t("steemit_owner_challenge_fee")), STEEM_SYMBOL )
#define STEEMIT_ACTIVE_CHALLENGE_COOLDOWN       (CONFIGMANAGE->getTime_seconds_byKey("steemit_active_challenge_cooldown_day"))
#define STEEMIT_OWNER_CHALLENGE_COOLDOWN        (CONFIGMANAGE->getTime_seconds_byKey("steemit_active_challenge_cooldown_day"))

#define STEEMIT_POST_REWARD_FUND_NAME            (CONFIGMANAGE->getValueForKey_tostring("steemit_post_reward_fund_name"))
#define STEEMIT_COMMENT_REWARD_FUND_NAME         (CONFIGMANAGE->getValueForKey_tostring("steemit_recent_rshares_decay_rate_hf17"))
#define STEEMIT_RECENT_RSHARES_DECAY_RATE_HF17  (CONFIGMANAGE->getTime_seconds_byKey("steemit_active_challenge_cooldown_day"))
#define STEEMIT_RECENT_RSHARES_DECAY_RATE_HF19  (CONFIGMANAGE->getTime_seconds_byKey("steemit_recent_rshares_decay_rate_hf19"))
#define STEEMIT_CONTENT_CONSTANT_HF0            (uint128_t(uint64_t(2000000000000ll)))
// note, if redefining these constants make sure calculate_claims doesn't overflow

// 5ccc e802 de5f
// int(expm1( log1p( 1 ) / BLOCKS_PER_YEAR ) * 2**STEEMIT_APR_PERCENT_SHIFT_PER_BLOCK / 100000 + 0.5)
// we use 100000 here instead of 10000 because we end up creating an additional 9x for vesting
#define STEEMIT_APR_PERCENT_MULTIPLY_PER_BLOCK          ( (uint64_t( 0x5ccc ) << 0x20) \
                                                        | (uint64_t( 0xe802 ) << 0x10) \
                                                        | (uint64_t( 0xde5f )        ) \
                                                        )
// chosen to be the maximal value such that STEEMIT_APR_PERCENT_MULTIPLY_PER_BLOCK * 2**64 * 100000 < 2**128
#define STEEMIT_APR_PERCENT_SHIFT_PER_BLOCK             87

#define STEEMIT_APR_PERCENT_MULTIPLY_PER_ROUND          ( (uint64_t( 0x79cc ) << 0x20 ) \
                                                        | (uint64_t( 0xf5c7 ) << 0x10 ) \
                                                        | (uint64_t( 0x3480 )         ) \
                                                        )

#define STEEMIT_APR_PERCENT_SHIFT_PER_ROUND             83

// We have different constants for hourly rewards
// i.e. hex(int(math.expm1( math.log1p( 1 ) / HOURS_PER_YEAR ) * 2**STEEMIT_APR_PERCENT_SHIFT_PER_HOUR / 100000 + 0.5))
#define STEEMIT_APR_PERCENT_MULTIPLY_PER_HOUR           ( (uint64_t( 0x6cc1 ) << 0x20) \
                                                        | (uint64_t( 0x39a1 ) << 0x10) \
                                                        | (uint64_t( 0x5cbd )        ) \
                                                        )

// chosen to be the maximal value such that STEEMIT_APR_PERCENT_MULTIPLY_PER_HOUR * 2**64 * 100000 < 2**128
#define STEEMIT_APR_PERCENT_SHIFT_PER_HOUR              77

// These constants add up to GRAPHENE_100_PERCENT.  Each GRAPHENE_1_PERCENT is equivalent to 1% per year APY
// *including the corresponding 9x vesting rewards*
#define STEEMIT_CURATE_APR_PERCENT              3875
#define STEEMIT_CONTENT_APR_PERCENT             3875
#define STEEMIT_LIQUIDITY_APR_PERCENT            750
#define STEEMIT_PRODUCER_APR_PERCENT             750
#define STEEMIT_POW_APR_PERCENT                  750

#define STEEMIT_CURATION_PERCENT                (CONFIGMANAGE->getValueForKey_touint64_t("steemit_curation_percent"))
#define STEEMIT_INITMINER_PERCENT                (CONFIGMANAGE->getValueForKey_touint64_t("steemit_initminer_percent"))
#define STEEMIT_AUTHOR_PERCENT                (CONFIGMANAGE->getValueForKey_touint64_t("steemit_author_percent"))
#define STEEMIT_POW_PERCENT                (CONFIGMANAGE->getValueForKey_touint64_t("steemit_pow_percent"))
#define STEEMIT_OTHER_PERCENT                (CONFIGMANAGE->getValueForKey_touint64_t("steemit_other_percent"))
#define STEEMIT_READER_PERCENT                (CONFIGMANAGE->getValueForKey_touint64_t("steemit_reader_percent"))



#define STEEMIT_MIN_PAYOUT_SBD                  (asset(20,SBD_SYMBOL))

#define STEEMIT_SBD_STOP_PERCENT                (5*STEEMIT_1_PERCENT ) // Stop printing SBD at 5% Market Cap
#define STEEMIT_SBD_START_PERCENT               (2*STEEMIT_1_PERCENT) // Start reducing printing of SBD at 2% Market Cap

#define STEEMIT_MIN_ACCOUNT_NAME_LENGTH         (CONFIGMANAGE->getValueForKey_touint64_t("steemit_min_account_name_length"))
#define STEEMIT_MAX_ACCOUNT_NAME_LENGTH         (CONFIGMANAGE->getValueForKey_touint64_t("steemit_max_account_name_length"))

#define STEEMIT_MIN_PERMLINK_LENGTH             0
#define STEEMIT_MAX_PERMLINK_LENGTH             256
#define STEEMIT_MAX_WITNESS_URL_LENGTH          2048

#define STEEMIT_INIT_SUPPLY                     int64_t(0)
#define STEEMIT_MAX_SHARE_SUPPLY                int64_t(1000000000000000ll)
#define STEEMIT_MAX_SIG_CHECK_DEPTH             2

#define STEEMIT_MIN_TRANSACTION_SIZE_LIMIT      1024
#define STEEMIT_SECONDS_PER_YEAR                (uint64_t(60*60*24*365ll))

#define STEEMIT_SBD_INTEREST_COMPOUND_INTERVAL_SEC  (60*60*24*30)
#define STEEMIT_MAX_TRANSACTION_SIZE            (1024*64*8)
#define STEEMIT_MIN_BLOCK_SIZE_LIMIT            (STEEMIT_MAX_TRANSACTION_SIZE)
#define STEEMIT_MAX_BLOCK_SIZE                  (STEEMIT_MAX_TRANSACTION_SIZE*STEEMIT_BLOCK_INTERVAL*4000)
#define STEEMIT_SOFT_MAX_BLOCK_SIZE             (4*1024*1024)
#define STEEMIT_MIN_BLOCK_SIZE                  115
#define STEEMIT_BLOCKS_PER_HOUR                 (60*60/STEEMIT_BLOCK_INTERVAL)
#define STEEMIT_FEED_INTERVAL_BLOCKS            (STEEMIT_BLOCKS_PER_HOUR)
#define STEEMIT_FEED_HISTORY_WINDOW_PRE_HF_16   (24*7) /// 7 days * 24 hours per day
#define STEEMIT_FEED_HISTORY_WINDOW             (12*7) // 3.5 days
#define STEEMIT_MAX_FEED_AGE_SECONDS            (60*60*24*7) // 7 days
#define STEEMIT_MIN_FEEDS                       (STEEMIT_MAX_WITNESSES/3) /// protects the network from conversions before price has been established
#define STEEMIT_CONVERSION_DELAY_PRE_HF_16      (fc::days(7))
#define STEEMIT_CONVERSION_DELAY                (fc::hours(STEEMIT_FEED_HISTORY_WINDOW)) //3.5 day conversion

#define STEEMIT_MIN_UNDO_HISTORY                10
#define STEEMIT_MAX_UNDO_HISTORY                10000

#define STEEMIT_MIN_TRANSACTION_EXPIRATION_LIMIT (STEEMIT_BLOCK_INTERVAL * 5) // 5 transactions per block
#define STEEMIT_BLOCKCHAIN_PRECISION            uint64_t( 1000 )

#define STEEMIT_BLOCKCHAIN_PRECISION_DIGITS     3
#define STEEMIT_MAX_INSTANCE_ID                 (uint64_t(-1)>>16)
/** NOTE: making this a power of 2 (say 2^15) would greatly accelerate fee calcs */
#define STEEMIT_MAX_AUTHORITY_MEMBERSHIP        10
#define STEEMIT_MAX_ASSET_WHITELIST_AUTHORITIES 10
#define STEEMIT_MAX_URL_LENGTH                  127

#define STEEMIT_IRREVERSIBLE_THRESHOLD          (75 * STEEMIT_1_PERCENT)

#define VIRTUAL_SCHEDULE_LAP_LENGTH  ( fc::uint128(uint64_t(-1)) )
#define VIRTUAL_SCHEDULE_LAP_LENGTH2 ( fc::uint128::max_value() )

/**
 *  Reserved Account IDs with special meaning
 */
///@{
/// Represents the current witnesses
#define STEEMIT_MINER_ACCOUNT                   "miners"
/// Represents the canonical account with NO authority (nobody can access funds in null account)
#define STEEMIT_NULL_ACCOUNT                    "null"
/// Represents the canonical account with WILDCARD authority (anybody can access funds in temp account)
#define STEEMIT_TEMP_ACCOUNT                    "temp"
/// Represents the canonical account for specifying you will vote for directly (as opposed to a proxy)
#define STEEMIT_PROXY_TO_SELF_ACCOUNT           ""
/// Represents the canonical root post parent account
#define STEEMIT_ROOT_POST_PARENT                (account_name_type())
///@}


#define NEWS_PRIVATE_EQUITY                         ("PrivateEquity")
#define NEWS_PRIVATE_EQUITY_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("ad0001"))))
#define NEWS_PRIVATE_EQUITY_PUBLIC_KEY             (steemit::protocol::public_key_type(NEWS_PRIVATE_EQUITY_PRIVATE_KEY.get_public_key()) )

#define NEWS_EARLY_INVESTMENT                   ("EarlyInvestment")
#define NEWS_EARLY_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("ad0001"))))
#define NEWS_EARLY_PUBLIC_KEY             ((steemit::protocol::public_key_type(NEWS_EARLY_PRIVATE_KEY.get_public_key()) ))

#define NEWS_TRAFFIC_MARKET                    ("TrafficeMarket")
#define NEWS_TRAFFIC_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("ad0001"))))
#define NEWS_TRAFFIC_PUBLIC_KEY             (( steemit::protocol::public_key_type(NEWS_TRAFFIC_PRIVATE_KEY.get_public_key()) ))


#define NEWS_CORE_TEAM                      ("CoreTeam")
#define NEWS_CORE_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("ad0001"))))
#define NEWS_CORE_PUBLIC_KEY             (( steemit::protocol::public_key_type(NEWS_CORE_PRIVATE_KEY.get_public_key()) ))

#define NEWS_FOUNDATION                     ("Foundation")
#define NEWS_FOUNDATION_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("ad0001"))))
#define NEWS_FOUNDATION_PUBLIC_KEY             (( steemit::protocol::public_key_type(NEWS_FOUNDATION_PRIVATE_KEY.get_public_key()) ))





