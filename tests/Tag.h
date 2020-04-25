#pragma once

#include <iostream>
#include "../src/Component.h"

class Tag : public Component<Tag, 16>
{
public:
	Tag( )
	{
	}

	~Tag( )
	{
	}

	virtual void OnStart( ) override
	{
		std::cout << "Added Tag to " << gameObject->GetName( ) << std::endl;
	}
	virtual void OnUpdate( ) override
	{
	}
	virtual void OnRender( ) override
	{
	}
	virtual void OnDestroy( ) override
	{
		std::cout << "Removed Tag from " << gameObject->GetName( ) << std::endl;
	}

};

#pragma once
