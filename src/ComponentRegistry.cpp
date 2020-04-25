#include "ComponentRegistry.h"


using  ComponentFunction = std::function<void( )>;
std::vector<ComponentFunction> ComponentRegistry::updates_;
std::vector<ComponentFunction> ComponentRegistry::renders_;


void ComponentRegistry::Update( )
{
	for (size_t i = 0; i < updates_.size( ); i++)
	{
		updates_[ i ]( );
	}
}

void ComponentRegistry::Render( )
{
	for (size_t i = 0; i < renders_.size( ); i++)
	{
		renders_[ i ]( );
	}
}

void ComponentRegistry::Destroy( )
{
	updates_.clear( );
	renders_.clear( );
}
