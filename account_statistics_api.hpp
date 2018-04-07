#pragma once

#include <newt/account_statistics/account_statistics_plugin.hpp>

#include <fc/api.hpp>

namespace newt{ namespace app {
   struct api_context;
} }

namespace newt { namespace account_statistics {

namespace detail
{
   class account_statistics_api_impl;
}

class account_statistics_api
{
   public:
      account_statistics_api( const newt::app::api_context& ctx );

      void on_api_startup();

   private:
      std::shared_ptr< detail::account_statistics_api_impl > _my;
};

} } // newt::account_statistics

FC_API( newt::account_statistics::account_statistics_api, )