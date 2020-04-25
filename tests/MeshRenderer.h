#pragma once

#include <iostream>
#include "../src/Component.h"

class MeshRenderer : public Component<MeshRenderer, 128>
{
public:
	MeshRenderer( )
	{
	}

	~MeshRenderer( )
	{
	}

	virtual void OnStart( ) override
	{
		std::cout << "Instantiated MeshRenderer of " << gameObject->GetName( ) << std::endl;
	}
	virtual void OnUpdate( ) override
	{
	}
	virtual void OnRender( ) override
	{
		std::cout << "Mesh of " << gameObject->GetName( ) << " Rendered." << std::endl;
	}
	virtual void OnDestroy( ) override
	{
		std::cout << "Destroyed MeshRenderer of " << gameObject->GetName( ) << std::endl;
	}

};

#pragma once
