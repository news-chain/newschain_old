#include <newt/follow/follow_operations.hpp>

#include <newt/protocol/operation_util_impl.hpp>

namespace newt { namespace follow {

void follow_operation::validate()const
{
   FC_ASSERT( follower != following, "You cannot follow yourself" );
}

void reblog_operation::validate()const
{
   FC_ASSERT( account != author, "You cannot reblog your own content" );
}

} } //newt::follow

DEFINE_OPERATION_TYPE( newt::follow::follow_plugin_operation )
