//
// Created by boy on 18-3-21.
//

#ifndef STEEM_ACCOUNT_ASSET_HPP
#define STEEM_ACCOUNT_ASSET_HPP

#include "account_object.hpp"
#include <steemit/protocol/asset.hpp>

#include <boost/multi_index/composite_key.hpp>
#include <boost/container/vector.hpp>
#include <chainbase/chainbase.hpp>
namespace steemit {
    namespace chain {

        using namespace steemit::protocol;


        struct c_other_asset{
            c_other_asset(){}
            c_other_asset(uint64_t a, uint64_t s):amount(a), symbol(s){}
//            c_other_asset(uint64_t a, uint64_t s, string name):amount(a), symbol(s){}
            uint64_t  amount;
            uint64_t  symbol;
            bool operator < (const c_other_asset& c1) const {return symbol < c1.symbol;}
            bool operator == (const c_other_asset &c1) const {return symbol == c1.symbol;}
            bool operator == (uint64_t _symbol) const{return symbol == _symbol;}
        };


        class account_asset : public object<account_asset_type, account_asset>{
        public:
            account_asset() = delete;
            template <typename  Constructor, typename  Allocator>
            account_asset(Constructor &&c, allocator<Allocator> a):array_asset(a){
                c(*this);
            }
            id_type id;
            account_name_type name;
//            c_other_asset m_asset;
            bip::vector<c_other_asset, allocator<c_other_asset>> array_asset;
        };


        class asset_symbol_object : public object<asset_symbol_object_type, asset_symbol_object>{
            asset_symbol_object() = delete;
        public:
            template <typename  Constructor, typename  Allocator>
            asset_symbol_object(Constructor &&c, allocator<Allocator> a):tag_name(a), meta(a){
                c(*this);
            }
            id_type id;


            shared_string tag_name;  //create name
            asset_symbol_type create_symbol_type;  //create symbol

            account_name_type create_account_name;

            time_point_sec create_time;
            uint64_t  amount;
            shared_string meta;    //bei zhu
        };


        struct by_asset_account_id;
        struct by_asset_account_name;
        typedef multi_index_container<
                account_asset,
                        indexed_by<
                                ordered_unique<tag<by_id>,
                                        member<account_asset, account_asset_id_type, &account_asset::id>
                                >
                                ,ordered_unique<tag<by_asset_account_name>,
                                    composite_key<account_asset,
                                            member<account_asset, account_name_type, &account_asset::name>
                                    >,
                                    composite_key_compare<std::less<account_name_type>>
                                >
                        >
                ,allocator<account_asset>
        > account_asset_index;


        struct by_symbol_name;
        typedef multi_index_container<
                asset_symbol_object,
                        indexed_by<
                                ordered_unique<tag<by_id>,
                                        member<asset_symbol_object, asset_symbol_object_id_type, &asset_symbol_object::id>
                                >
                                ,ordered_unique<tag<by_symbol_name>,
                                    composite_key<asset_symbol_object,
                                        member<asset_symbol_object, shared_string, &asset_symbol_object::tag_name>
                                    >,
                                    composite_key_compare<strcmp_less>
                                >
                        >
                ,allocator <asset_symbol_object>
        > asset_symbol_object_index;
    }

}

FC_REFLECT(steemit::chain::c_other_asset, (amount)(symbol))
FC_REFLECT(steemit::chain::account_asset, (id)(name)(array_asset))
CHAINBASE_SET_INDEX_TYPE(steemit::chain::account_asset, steemit::chain::account_asset_index)

FC_REFLECT(steemit::chain::asset_symbol_object, (id)(tag_name)(create_symbol_type)(create_account_name)(create_time)(amount)(meta))
CHAINBASE_SET_INDEX_TYPE(steemit::chain::asset_symbol_object, steemit::chain::asset_symbol_object_index)
#endif //STEEM_ACCOUNT_ASSET_HPP
