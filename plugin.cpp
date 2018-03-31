
#include <newt/app/plugin.hpp>

#include <fc/vector.hpp>

namespace newt { namespace app {

plugin::plugin( application* app ) : _app( app )
{
   return;
}

plugin::~plugin()
{
   return;
}

std::string plugin::plugin_name()const
{
   return "<unknown plugin>";
}

void plugin::plugin_initialize( const boost::program_options::variables_map& options )
{
   return;
}

void plugin::plugin_startup()
{
   return;
}

void plugin::plugin_shutdown()
{
   return;
}

void plugin::plugin_set_program_options(
   boost::program_options::options_description& command_line_options,
   boost::program_options::options_description& config_file_options
)
{
   return;
}

} } // newt::app
