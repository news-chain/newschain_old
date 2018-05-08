//
// Created by boy on 18-4-30.
//

#ifndef STEEM_TRANSFERHISTORY_HPP
#define STEEM_TRANSFERHISTORY_HPP



#include <fc/fixed_string.hpp>

#include <steemit/protocol/authority.hpp>
#include <steemit/protocol/steem_operations.hpp>

#include <steemit/chain/steem_object_types.hpp>
#include <steemit/chain/witness_objects.hpp>
#include <steemit/chain/shared_authority.hpp>

#include <boost/multi_index/composite_key.hpp>


namespace  steemit{
    namespace  chain{

        class transfer_history : public object<transfer_history_type, transfer_history>{
            transfer_history() = delete;

        public:
            template<typename Constructor, typename Allocator>
            transfer_history(Constructor &&c, allocator<Allocator> a)
            :memo(a){
                    c(*this);
            };

            id_type id;
            account_name_type from_name;
            account_name_type to_name;
            asset amount;
            time_point_sec created_time;
            shared_string memo;

        };


        struct by_from;
        struct by_to;
        struct by_created_time;
        struct by_memo;
        struct by_from_to;
        typedef multi_index_container<
                transfer_history,
                        indexed_by<
                            ordered_unique<tag<by_id>,
                                    member<transfer_history, transfer_history_id_type, &transfer_history::id>
                            >,
                            ordered_non_unique<tag<by_from>,
                                    member<transfer_history, account_name_type, &transfer_history::from_name>
                            >,
                            ordered_non_unique<tag<by_to>,
                                    member<transfer_history, account_name_type, &transfer_history::to_name>
                            >,
                            ordered_non_unique<tag<by_created_time>,
                                    composite_key<transfer_history,
                                            member<transfer_history, time_point_sec, &transfer_history::created_time>
                                    >,
                                    composite_key_compare<std::greater<time_point_sec>>
                            >,
                            ordered_non_unique<tag<by_memo>,
                                    composite_key<transfer_history,
                                            member<transfer_history, shared_string, &transfer_history::memo>
                                    >,
                                    composite_key_compare<strcmp_less>
                            >,
                            ordered_non_unique<tag<by_from_to>,
                                    composite_key<transfer_history,
                                            member<transfer_history, account_name_type, &transfer_history::from_name>,
                                            member<transfer_history, account_name_type, &transfer_history::to_name>
                                    >,
                                    composite_key_compare<std::less<account_name_type>, std::less<account_name_type>>
                            >
                        >,
                                allocator <transfer_history>
                > transfer_history_index;
    }
}



FC_REFLECT(steemit::chain::transfer_history, (id)(from_name)(to_name)(amount)(created_time)(memo))
CHAINBASE_SET_INDEX_TYPE(steemit::chain::transfer_history, steemit::chain::transfer_history_index)










#endif //STEEM_TRANSFERHISTORY_HPP
