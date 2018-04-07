
#pragma once

#include <newt/app/plugin.hpp>
#include <newt/chain/database.hpp>

#include <fc/thread/future.hpp>

namespace newt { namespace account_history {
using namespace chain;
using app::application;

//
// Plugins should #define their SPACE_ID's so plugins with
// conflicting SPACE_ID assignments can be compiled into the
// same binary (by simply re-assigning some of the conflicting #defined
// SPACE_ID's in a build script).
//
// Assignment of SPACE_ID's cannot be done at run-time because
// various template automagic depends on them being known at compile
// time.
//
#ifndef ACCOUNT_HISTORY_SPACE_ID
#define ACCOUNT_HISTORY_SPACE_ID 5
#endif

enum account_history_object_type
{
   key_account_object_type = 0,
   bucket_object_type = 1 ///< used in market_history_plugin
};


namespace detail
{
    class account_history_plugin_impl;
}

/**
 *  This plugin is designed to track a range of operations by account so that one node
 *  doesn't need to hold the full operation history in memory.
 */
class account_history_plugin : public newt::app::plugin
{
   public:
      account_history_plugin( application* app );
      virtual ~account_history_plugin();

      std::string plugin_name()const override;
      virtual void plugin_set_program_options(
         boost::program_options::options_description& cli,
         boost::program_options::options_description& cfg) override;
      virtual void plugin_initialize(const boost::program_options::variables_map& options) override;
      virtual void plugin_startup() override;


      flat_map< account_name_type, account_name_type > tracked_accounts()const; /// map start_range to end_range

      friend class detail::account_history_plugin_impl;
      std::unique_ptr<detail::account_history_plugin_impl> my;
};

} } //newt::account_history

