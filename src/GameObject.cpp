#include "GameObject.h"


GameObject::GameObject( const std::string& name )
	: name_( name )
{
	componentFilter_.reset( );
}

GameObject::~GameObject( )
{
	for (DeleterMap::iterator it = deleterMap_.begin( ); it != deleterMap_.end( ); ++it)
	{
		it->second( );
	}

	deleterMap_.clear( );
	componentMap_.clear( );
	componentFilter_.reset( );
}