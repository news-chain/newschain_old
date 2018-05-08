//
// Created by boy on 18-4-22.
//

#ifndef STEEM_REWARD_DETAIL_HPP
#define STEEM_REWARD_DETAIL_HPP


#include <steemit/protocol/authority.hpp>
#include <steemit/protocol/steem_operations.hpp>

#include <steemit/chain/steem_object_types.hpp>
#include <steemit/chain/witness_objects.hpp>

#include <boost/multi_index/composite_key.hpp>





namespace steemit{
    namespace chain{

        class reward_detail_object : public object<reward_detail_object_type, reward_detail_object>{
            reward_detail_object() = delete;
        public:
            template<typename Constructor, typename Allocator>
            reward_detail_object(Constructor &&c, allocator <Allocator> a):op(a),creator(a), to_user(a){
                c(*this);
            }
            id_type id;
            shared_string op;           //operation: vote_up, vote_down , comment, share_comment
            shared_string creator;         //
            uint32_t amount = 0;
            time_point_sec created_time;
            uint32_t weight;
            shared_string to_user;
        };


        struct temp_toUser_operation{
//            temp_toUser_operation(string to, string p):to_user(to), op(p){}
            string to_user;
            string op;

        };

        struct comment_op_for_reward_detail{
            string author;
            string permlink;
            string title;
            uint16_t  depth = 0;
            string extends;         //order
            string parent_permlink;
        };


#define  DETAIL_VOTE_UP_STRING ("vote_up")
#define  DETAIL_VOTE_DOWN_STRING ("vote_down")

        struct detail_vote_op{
            string voter;
            string author;
            string permlink;
            string type; // "down" "vote_up"
            time_point_sec vote_time;
        };


        //师徒收益
        class reward_for_teacher_object : public object<reward_for_teacher_object_type, reward_for_teacher_object> {
            reward_for_teacher_object() = delete;
        public:
            template<typename Constructor, typename Allocator>
            reward_for_teacher_object(Constructor &&c, allocator <Allocator> a)
                    :user(a),parent(a),teacher(a), op(a){
                    c(*this);
            }
            id_type id;
            shared_string user;         //产生
            shared_string parent;       //师傅
            shared_string teacher;      //师公

            uint32_t user_amount = 0;
            uint32_t parent_amount = 0;
            uint32_t teacher_amount = 0;
            time_point_sec created_time;

            shared_string op;
        };


//        class reward_for_comment_object : public object<reward_for_comment_object_type, reward_for_comment_object>{
//            reward_for_comment_object() = delete;
//        public:
//            template<typename Constructor, typename Allocator>
//            reward_for_comment_object(Constructor &&c, allocator <Allocator> a) {
//                c(*this);
//            }
//
//            id_type id;
//            account_name_type name;
//            shared_string permlink;
//
//
//
//        };
//




        /*************************************index by******************************************/

        struct by_created_time;
        struct by_user;
        struct by_id;
        typedef struct multi_index_container<
                reward_detail_object,
                    indexed_by<
                                ordered_unique<
                                            tag<by_id>,
                                                    member<reward_detail_object, reward_detail_id_type, &reward_detail_object::id>
                                        >,
                                ordered_non_unique<
                                            tag<by_created_time>,
                                            composite_key<reward_detail_object,
                                                member<reward_detail_object, time_point_sec, &reward_detail_object::created_time>
                                            >
                                        >,
                                ordered_non_unique<
                                            tag<by_user>,
                                            composite_key<reward_detail_object,
                                                member<reward_detail_object, shared_string, &reward_detail_object::creator>
                                            >
                                        >
                            >
            ,allocator<reward_detail_object>
        > reward_detail_index;

        typedef struct multi_index_container<
                reward_for_teacher_object,
                indexed_by<
                        ordered_unique<
                                tag<by_id>,
                                member<reward_for_teacher_object, reward_for_teacher_id_type, &reward_for_teacher_object::id>
                        >,
                        ordered_non_unique<
                                tag<by_created_time>,
                                composite_key<reward_for_teacher_object,
                                        member<reward_for_teacher_object, time_point_sec, &reward_for_teacher_object::created_time>
                                >
                        >
                        ,ordered_non_unique<
                                tag<by_user>,
                                composite_key<reward_for_teacher_object,
                                        member<reward_for_teacher_object, shared_string, &reward_for_teacher_object::user>
                                >
                                >
                >
                ,allocator<reward_for_teacher_object>
        > reward_for_teacher_index;
    }
}



FC_REFLECT(steemit::chain::reward_detail_object, (id)(op)(creator)(amount)(created_time)(weight)(to_user))
FC_REFLECT(steemit::chain::comment_op_for_reward_detail, (author)(permlink)(title)(depth)(extends)(parent_permlink))
FC_REFLECT(steemit::chain::detail_vote_op, (voter)(author)(permlink)(type)(vote_time))
FC_REFLECT(steemit::chain::reward_for_teacher_object, (id)(user)(parent)(teacher)(user_amount)(parent_amount)(teacher_amount)(created_time))

CHAINBASE_SET_INDEX_TYPE(steemit::chain::reward_detail_object, steemit::chain::reward_detail_index)
CHAINBASE_SET_INDEX_TYPE(steemit::chain::reward_for_teacher_object, steemit::chain::reward_for_teacher_index)






#endif //STEEM_REWARD_DETAIL_HPP
