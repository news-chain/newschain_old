#pragma once

#include <steemit/protocol/authority.hpp>
#include <steemit/protocol/steem_operations.hpp>

#include <steemit/chain/steem_object_types.hpp>
#include <steemit/chain/witness_objects.hpp>

#include <boost/multi_index/composite_key.hpp>


namespace steemit {
    namespace chain {

        using protocol::beneficiary_route_type;

        struct strcmp_less {
            bool operator()(const shared_string &a, const shared_string &b) const {
                return less(a.c_str(), b.c_str());
            }

            bool operator()(const shared_string &a, const string &b) const {
                return less(a.c_str(), b.c_str());
            }

            bool operator()(const string &a, const shared_string &b) const {
                return less(a.c_str(), b.c_str());
            }

        private:
            inline bool less(const char *a, const char *b) const {
                return std::strcmp(a, b) < 0;
            }
        };

        class comment_object : public object<comment_object_type, comment_object> {
            comment_object() = delete;

        public:
            template<typename Constructor, typename Allocator>
            comment_object(Constructor &&c, allocator <Allocator> a)
                    :category(a), parent_permlink(a), permlink(a), title(a), body(a), json_metadata(a),
                     beneficiaries(a),extends(a) {
                c(*this);
            }

            id_type id;

            shared_string category;
            account_name_type parent_author;
            shared_string parent_permlink;
            account_name_type author;
            shared_string permlink;

            shared_string title;
            shared_string body;
            shared_string json_metadata;
            time_point_sec last_update;
            time_point_sec created;
            time_point_sec active; ///< the last time this post was "touched" by voting or reply
            time_point_sec last_payout;

            uint16_t depth = 0; ///< used to track max nested depth
            uint32_t children = 0; ///< used to track the total number of children, grandchildren, etc...

            /// index on pending_payout for "things happning now... needs moderation"
            /// TRENDING = UNCLAIMED + PENDING
            share_type net_rshares; // reward is proportional to rshares^2, this is the sum of all votes (positive and negative)
            share_type abs_rshares; /// this is used to track the total abs(weight) of votes for the purpose of calculating cashout_time
            share_type vote_rshares; /// Total positive rshares from all votes. Used to calculate delta weights. Needed to handle vote changing and removal.

            share_type children_abs_rshares; /// this is used to calculate cashout time of a discussion.
            time_point_sec cashout_time; /// 24 hours from the weighted average of vote time
            time_point_sec max_cashout_time;
            uint64_t total_vote_weight = 0; /// the total weight of voting rewards, used to calculate pro-rata share of curation payouts

            uint16_t reward_weight = 0;

            /** tracks the total payout this comment has received over time, measured in SBD */
            asset total_payout_value = asset(0, SBD_SYMBOL);
            asset curator_payout_value = asset(0, SBD_SYMBOL);
            asset beneficiary_payout_value = asset(0, SBD_SYMBOL);

            share_type author_rewards = 0;

            int32_t net_votes = 0;

            id_type root_comment;

            asset max_accepted_payout = asset(1000000000,
                                              SBD_SYMBOL);       /// SBD value of the maximum payout this post will receive
            uint16_t percent_steem_dollars = STEEMIT_100_PERCENT; /// the percent of Steem Dollars to key, unkept amounts will be received as Steem Power
            bool allow_replies = true;      /// allows a post to disable replies.
            bool allow_votes = true;      /// allows a post to receive votes;
            bool allow_curation_rewards = true;



            bip::vector <beneficiary_route_type, allocator<beneficiary_route_type>> beneficiaries;
            shared_string extends;
        };


        /**
         * This index maintains the set of voter/comment pairs that have been used, voters cannot
         * vote on the same comment more than once per payout period.
         */
        class comment_vote_object : public object<comment_vote_object_type, comment_vote_object> {
        public:
            template<typename Constructor, typename Allocator>
            comment_vote_object(Constructor &&c, allocator <Allocator> a) {
                c(*this);
            }

            id_type id;

            account_id_type voter;
            comment_id_type comment;
            uint64_t weight = 0; ///< defines the score this vote receives, used by vote payout calc. 0 if a negative vote or changed votes.
            int64_t rshares = 0; ///< The number of rshares this vote is responsible for
            int16_t vote_percent = 0; ///< The percent weight of the vote
            time_point_sec last_update; ///< The time of the last update of the vote
            int8_t num_changes = 0;
        };

        //add read comment history
        class comment_read_object : public object<comment_read_object_type, comment_read_object> {
        public:
            template<typename Constructor, typename Allocator>
            comment_read_object(Constructor &&c, allocator <Allocator> a) {
                c(*this);
            }

            id_type id;
            account_id_type reader;
            comment_id_type comment;
            time_point_sec first_read ;
            time_point_sec last_read ;
        };


        class comment_share_object : public object<comment_share_object_type, comment_share_object>{
        public:
            template<typename Constructor, typename Allocator>
            comment_share_object(Constructor &&c, allocator <Allocator> a) {
                c(*this);
            }

            id_type id;
            account_id_type sharer;
            comment_id_type comment;

            time_point_sec first_share;
            time_point_sec last_share;
            uint32_t count;

        };


        class comment_vote_up_object : public object<comment_vote_up_object_type, comment_vote_up_object>{
        public:
            template<typename Constructor, typename Allocator>
            comment_vote_up_object(Constructor &&c, allocator <Allocator> a):extends(a) {
                c(*this);
            }

            id_type id;

            account_id_type voter;
            account_id_type author;
            comment_id_type comment;
            time_point_sec vote_time;
            shared_string extends;
        };

        class comment_vote_down_object : public object<comment_vote_down_object_type, comment_vote_down_object>{
        public:
            template<typename Constructor, typename Allocator>
            comment_vote_down_object(Constructor &&c, allocator <Allocator> a):extends(a) {
                c(*this);
            }

            id_type id;

            account_id_type voter;
            account_id_type author;
            comment_id_type comment;
            time_point_sec vote_time;

            shared_string extends;
        };




        /******************************************index for object******************************************************/


        struct by_comment_voter;
        struct by_voter_comment;
        struct by_comment_weight_voter;
        struct by_voter_last_update;
        typedef multi_index_container <
        comment_vote_object,
        indexed_by<
                ordered_unique < tag <
                     by_id>, member<comment_vote_object, comment_vote_id_type, &comment_vote_object::id>>,
                ordered_unique <tag<by_comment_voter>,
                    composite_key<comment_vote_object,
                        member < comment_vote_object, comment_id_type, &comment_vote_object::comment>,
                        member<comment_vote_object, account_id_type, &comment_vote_object::voter>
                    >
                >,
                ordered_unique <tag<by_voter_comment>,
                    composite_key<comment_vote_object,
                        member < comment_vote_object, account_id_type, &comment_vote_object::voter>,
                        member<comment_vote_object, comment_id_type, &comment_vote_object::comment>
                    >
                 >,
                ordered_unique <tag<by_voter_last_update>,
                    composite_key<comment_vote_object,
                        member < comment_vote_object, account_id_type, &comment_vote_object::voter>,
                        member<comment_vote_object, time_point_sec, &comment_vote_object::last_update>,
                        member<comment_vote_object, comment_id_type, &comment_vote_object::comment>
                    >,
                    composite_key_compare <std::less<account_id_type>, std::greater<time_point_sec>, std::less<comment_id_type>>
                >,
                ordered_unique <tag<by_comment_weight_voter>,
                    composite_key<comment_vote_object,
                        member < comment_vote_object, comment_id_type, &comment_vote_object::comment>,
                        member<comment_vote_object, uint64_t, &comment_vote_object::weight>,
                        member<comment_vote_object, account_id_type, &comment_vote_object::voter>
                    >,
                    composite_key_compare <std::less<comment_id_type>, std::greater<uint64_t>, std::less<account_id_type>>
                >
            >,
        allocator <comment_vote_object>
        >
        comment_vote_index;


        struct by_cashout_time; /// cashout_time
        struct by_permlink; /// author, perm
        struct by_root;
        struct by_parent;
        struct by_active; /// parent_auth, active
        struct by_pending_payout;
        struct by_total_pending_payout;
        struct by_last_update; /// parent_auth, last_update
        struct by_created; /// parent_auth, last_update
        struct by_payout; /// parent_auth, last_update
        struct by_blog;
        struct by_votes;
        struct by_responses;
        struct by_author_last_update;

        /**
         * @ingroup object_index
         */
        typedef multi_index_container <
        comment_object,
        indexed_by<
                /// CONSENUSS INDICIES - used by evaluators
                ordered_unique < tag < by_id>, member<comment_object, comment_id_type, &comment_object::id>>,
        ordered_unique <tag<by_cashout_time>,
        composite_key<comment_object,
                member < comment_object, time_point_sec, &comment_object::cashout_time>,
        member<comment_object, comment_id_type, &comment_object::id>
        >
        >,
        ordered_unique <tag<by_permlink>, /// used by consensus to find posts referenced in ops
        composite_key<comment_object,
                member < comment_object, account_name_type, &comment_object::author>,
                member<comment_object, shared_string, &comment_object::permlink>
        >,
        composite_key_compare <std::less<account_name_type>, strcmp_less>
        >,
        ordered_unique <tag<by_root>,
        composite_key<comment_object,
                member < comment_object, comment_id_type, &comment_object::root_comment>,
                member<comment_object, comment_id_type, &comment_object::id>
        >
        >,
        ordered_unique <tag<by_parent>, /// used by consensus to find posts referenced in ops
        composite_key<comment_object,
                member < comment_object, account_name_type, &comment_object::parent_author>,
        member<comment_object, shared_string, &comment_object::parent_permlink>,
        member<comment_object, comment_id_type, &comment_object::id>
        >,
        composite_key_compare <std::less<account_name_type>, strcmp_less, std::less<comment_id_type>>
        >
        /// NON_CONSENSUS INDICIES - used by APIs
#ifndef IS_LOW_MEM
        ,
        ordered_unique <tag<by_last_update>,
        composite_key<comment_object,
                member < comment_object, account_name_type, &comment_object::parent_author>,
        member<comment_object, time_point_sec, &comment_object::last_update>,
        member<comment_object, comment_id_type, &comment_object::id>
        >,
        composite_key_compare <std::less<account_name_type>, std::greater<time_point_sec>, std::less<comment_id_type>>
        >,
        ordered_unique <tag<by_author_last_update>,
        composite_key<comment_object,
                member < comment_object, account_name_type, &comment_object::author>,
        member<comment_object, time_point_sec, &comment_object::last_update>,
        member<comment_object, comment_id_type, &comment_object::id>
        >,
        composite_key_compare <std::less<account_name_type>, std::greater<time_point_sec>, std::less<comment_id_type>>
        >
#endif
        >,
        allocator <comment_object>
        >
        comment_index;



        //add 2018.2.26 by zhang
//        struct by_reader_id;
        struct by_comment_reader;
        struct by_reader_comment;
        struct by_first_time_commentReader;
        typedef multi_index_container<
                comment_read_object,
                        indexed_by<
                                ordered_unique<
                                        tag<by_id>
                                                ,member<comment_read_object, comment_read_id_type, &comment_read_object::id>
                                                >,
                                ordered_unique<
                                        tag<by_comment_reader>,
                                        composite_key<comment_read_object,
                                                member<comment_read_object, comment_id_type, &comment_read_object::comment>,
                                                member<comment_read_object, account_id_type, &comment_read_object::reader>
                                        >
                                >
                                ,ordered_unique<
                                        tag<by_reader_comment>,
                                        composite_key<comment_read_object,
                                                member<comment_read_object, account_id_type, &comment_read_object::reader>,
                                                member<comment_read_object, comment_id_type, &comment_read_object::comment>

                                        >
                                >
                                ,ordered_non_unique<
                                        tag<by_first_time_commentReader>,
                                            composite_key<comment_read_object,
//                                                    member<comment_read_object, account_id_type, &comment_read_object::reader>,
//                                                    member<comment_read_object, comment_id_type, &comment_read_object::comment>,
                                                    member<comment_read_object, time_point_sec, &comment_read_object::first_read>
                                            >
                                        ,composite_key_compare<std::less<time_point_sec>>
                                        >
                        >,
                        allocator<comment_read_object>
                >comment_read_index;




        //add 2018.3.2 for comment_share_object by zhang
        struct by_comment_sharer;
//        struct by_comment_share_id;
        struct by_comment_share_lastTime;
        typedef multi_index_container<
                    comment_share_object,
                            indexed_by<
                                    ordered_unique<
                                            tag<by_id>, member<comment_share_object, comment_share_id_type, &comment_share_object::id>
                                            >,
                                    ordered_unique<
                                            tag<by_comment_sharer>,
                                                composite_key<comment_share_object,
                                                    member<comment_share_object, account_id_type, &comment_share_object::sharer>
//                                                    ,member<comment_share_object, account_id_type, &comment_share_object::author>
                                                    ,member<comment_share_object, comment_id_type, &comment_share_object::comment>
                                                    >
                                            >,
                                    ordered_non_unique<
                                            tag<by_comment_share_lastTime>,
                                                composite_key<comment_share_object,
                                                    member<comment_share_object, account_id_type, &comment_share_object::sharer>,
                                                    member<comment_share_object, time_point_sec, &comment_share_object::last_share>
                                                >
                                            >
                    >,
                    allocator<comment_share_object>
                 > comment_share_index;


        //vote up
//        struct by_comment_vote_up_id;
        struct by_comment_vote_up_voter;
        struct by_comment_vote_up_comment;
        struct by_comment_vote_up_time;
        typedef multi_index_container<
                    comment_vote_up_object,
                            indexed_by<
                                    ordered_unique<
                                            tag<by_id>,
                                            member<comment_vote_up_object, comment_vote_up_id_type, &comment_vote_up_object::id>
                                    >
                                    ,ordered_unique<
                                            tag<by_comment_vote_up_voter>,
                                                composite_key<comment_vote_up_object,
                                                    member<comment_vote_up_object, account_id_type, &comment_vote_up_object::voter>
//                                                    ,member<comment_vote_up_object, account_id_type, &comment_vote_up_object::author>
                                                    ,member<comment_vote_up_object, comment_id_type, &comment_vote_up_object::comment>
                                                >
                                    >
                                    ,ordered_non_unique<
                                            tag<by_comment_vote_up_time>,
                                                composite_key<comment_vote_up_object,
                                                member<comment_vote_up_object, time_point_sec, &comment_vote_up_object::vote_time>
//                                                ,member<comment_vote_up_object, comment_vote_up_id_type, &comment_vote_up_object::id>
                                                >
                                            ,composite_key_compare<std::less<time_point_sec>>
                                    >
                            >
                            ,allocator<comment_vote_up_object>
                        > comment_vote_up_index;

        //vote down
//        struct by_comment_vote_down_id;
        struct by_comment_vote_down_voter;
        struct by_comment_vote_down_comment;
        struct by_comment_vote_down_time;
        typedef multi_index_container<
        comment_vote_down_object,
        indexed_by<
                ordered_unique<
                tag<by_id>,
                    member<comment_vote_down_object, comment_vote_down_id_type, &comment_vote_down_object::id>
                >
                ,ordered_unique<
                tag<by_comment_vote_down_voter>,
                    composite_key<comment_vote_down_object,
                        member<comment_vote_down_object, account_id_type, &comment_vote_down_object::voter>
//                        ,member<comment_vote_down_object, account_id_type, &comment_vote_down_object::author>
                        ,member<comment_vote_down_object, comment_id_type, &comment_vote_down_object::comment>
                        >
                >
                ,ordered_non_unique<
                    tag<by_comment_vote_down_time>,
                    composite_key<comment_vote_down_object,
                            member<comment_vote_down_object, time_point_sec, &comment_vote_down_object::vote_time>
//                            ,member<comment_vote_down_object, comment_vote_down_id_type, &comment_vote_down_object::id>
                    >
                >
            >
        ,allocator<comment_vote_down_object>
        > comment_vote_down_index;
    }
} // steemit::chain

FC_REFLECT(steemit::chain::comment_object,
           (id)(author)(permlink)
                   (category)(parent_author)(parent_permlink)
                   (title)(body)(json_metadata)(last_update)(created)(active)(last_payout)
                   (depth)(children)
                   (net_rshares)(abs_rshares)(vote_rshares)
                   (children_abs_rshares)(cashout_time)(max_cashout_time)
                   (total_vote_weight)(reward_weight)(total_payout_value)(curator_payout_value)(
                   beneficiary_payout_value)(author_rewards)(net_votes)(root_comment)
                   (max_accepted_payout)(percent_steem_dollars)(allow_replies)(allow_votes)(allow_curation_rewards)
                   (beneficiaries)(extends)
)
CHAINBASE_SET_INDEX_TYPE(steemit::chain::comment_object, steemit::chain::comment_index)

FC_REFLECT(steemit::chain::comment_vote_object,
           (id)(voter)(comment)(weight)(rshares)(vote_percent)(last_update)(num_changes)
)
CHAINBASE_SET_INDEX_TYPE(steemit::chain::comment_vote_object, steemit::chain::comment_vote_index)

FC_REFLECT(steemit::chain::comment_read_object, (id)(reader)(comment)(first_read)(last_read))

CHAINBASE_SET_INDEX_TYPE(steemit::chain::comment_read_object, steemit::chain::comment_read_index)

FC_REFLECT(steemit::chain::comment_share_object, (id)(sharer)(comment)(first_share)(last_share)(count))

CHAINBASE_SET_INDEX_TYPE(steemit::chain::comment_share_object, steemit::chain::comment_share_index)

FC_REFLECT(steemit::chain::comment_vote_up_object, (id)(voter)(author)(comment)(vote_time)(extends))
CHAINBASE_SET_INDEX_TYPE(steemit::chain::comment_vote_up_object, steemit::chain::comment_vote_up_index)

FC_REFLECT(steemit::chain::comment_vote_down_object, (id)(voter)(author)(comment)(vote_time)(extends))
CHAINBASE_SET_INDEX_TYPE(steemit::chain::comment_vote_down_object, steemit::chain::comment_vote_down_index)
