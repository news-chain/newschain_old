//
// Created by boy on 18-3-9.
//

#ifndef STEEM_CASHOUT_HISTORY_HPP
#define STEEM_CASHOUT_HISTORY_HPP

#include <fc/time.hpp>
#include <string>

#include <array>
#include <fc/log/logger.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/algorithm.hpp>
#include <steemit/protocol/config.hpp>
#include <thread>

namespace steemit{
    namespace chain{



        enum historyType{
            regist = 1,
            reader,
            postComment,
            shareComment,
            write_to_comment,
            teacher
        };


        class cashout_history
        {
        public:
            cashout_history(std::string orderId, uint64_t payout):m_orderId(orderId), m_payout(payout){m_type = postComment;}
            cashout_history(std::string userId, std::string parentId, uint64_t payout, std::string orderid):m_userId(userId),m_parentId(parentId), m_payout(payout), m_orderId(orderid){m_type = teacher;}
            void cacheJsonByName_toPath(boost::filesystem::fstream &stream);

            std::string m_orderId;  //if type = postComment, order_id from java server, else type = teacher  orderId = permlink
            uint64_t m_payout;
            historyType m_type;

            std::string m_userId;
            std::string m_parentId;



        private:
            void cacheRegist(std::string path);

            void cacheOther(std::string path);
        };

        namespace http{
            bool asyc_postData(std::string url, std::string data, std::string contentType,std::string &reponse_data);
        }



    }
}











#endif //STEEM_CASHOUT_HISTORY_HPP
