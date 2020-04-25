#pragma once

#include <iostream>
#include "../src/Component.h"

class Transform : public Component<Transform, 256>
{
public:
	std::vector<float_t> Position;
	std::vector<float_t> Orientation;
	std::vector<float_t> Scale;

	Transform( )
	{
		Position.resize( 3, 0.0f );
		Orientation.resize( 3, 0.0f );
		Scale.resize( 3, 0.0f );
	}

	~Transform( )
	{
	}

	virtual void OnStart( ) override
	{
		std::cout << "Instantiated Transform of " << gameObject->GetName( ) << std::endl;
	}
	virtual void OnUpdate( ) override
	{
		std::cout << "Transform of " << gameObject->GetName( ) << " Updated." << std::endl;
	}
	virtual void OnRender( ) override
	{

	}
	virtual void OnDestroy( ) override
	{
		std::cout << "Destroyed Transform of " << gameObject->GetName( ) << std::endl;
	}

};

