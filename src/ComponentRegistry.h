#pragma once
#include <memory>
#include <functional>

#include "Component.h"


class ComponentRegistry
{
	using  ComponentFunction = std::function<void( )>;

public:
	template <typename T>
	static void Register( bool update, bool render )
	{
		auto allocator = T::get_allocator( );

		if (update)
		{
			updates_.push_back( [ allocator ] ( )
			{
				auto& alloc_ref = *( allocator.get( ) );
				for (size_t i = 0; i < alloc_ref.size( ); i++)
				{
					auto component = alloc_ref[ i ];
					component->OnUpdate( );
				}
			} );
		}

		if (render)
		{
			renders_.push_back( [ allocator ] ( )
			{
				auto& alloc_ref = *( allocator.get( ) );
				for (size_t i = 0; i < alloc_ref.size( ); i++)
				{
					auto component = alloc_ref[ i ];
					component->OnRender( );
				}
			} );
		}
	}

	static void Update( );
	static void Render( );


	static void Destroy( );

private:
	static std::vector<ComponentFunction> updates_;
	static std::vector<ComponentFunction> renders_;
};


