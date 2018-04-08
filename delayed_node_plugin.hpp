
#pragma once

#include <newt/app/plugin.hpp>
#include <newt/chain/steem_objects.hpp>

namespace newt { namespace delayed_node {
namespace detail { struct delayed_node_plugin_impl; }

using app::application;

class delayed_node_plugin : public newt::app::plugin
{
   std::unique_ptr<detail::delayed_node_plugin_impl> my;
public:
   delayed_node_plugin( application* app );
   virtual ~delayed_node_plugin();

   std::string plugin_name()const override { return "delayed_node"; }
   virtual void plugin_set_program_options(boost::program_options::options_description&,
                                           boost::program_options::options_description& cfg) override;
   virtual void plugin_initialize(const boost::program_options::variables_map& options) override;
   virtual void plugin_startup() override;
   void mainloop();

protected:
   void connection_failed();
   void connect();
   void sync_with_trusted_node();
};

} } //newt::account_history

