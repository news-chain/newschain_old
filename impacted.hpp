
#pragma once

#include <fc/container/flat.hpp>
#include <newt/protocol/operations.hpp>
#include <newt/protocol/transaction.hpp>
#include <newt/chain/steem_object_types.hpp>

#include <fc/string.hpp>

namespace newt { namespace app {

using namespace fc;

void operation_get_impacted_accounts(
   const newt::protocol::operation& op,
   fc::flat_set<protocol::account_name_type>& result );

void transaction_get_impacted_accounts(
   const newt::protocol::transaction& tx,
   fc::flat_set<protocol::account_name_type>& result
   );

} } // newt::app
