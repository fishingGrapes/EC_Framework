#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <thread>

#include "../src/GameObject.h"
#include "../src/ComponentRegistry.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "Tag.h"

int main( )
{
	//Resgister Components so that only their selected virtual functions are called
	ComponentRegistry::Register<Transform>( true, false );
	ComponentRegistry::Register<MeshRenderer>( false, true );
	ComponentRegistry::Register<Tag>( false, false );

	GameObject* simpleObject = GameObject::Instantiate( "Simple Object" );
	dptr<Transform> t1 = simpleObject->AddComponent<Transform>( );
	dptr<Tag> tag1 = simpleObject->AddComponent<Tag>( );

	//can't add multiple components of the same type to a gameobject
	dptr<Tag> tag2 = simpleObject->AddComponent<Tag>( );


	GameObject* meshObject = GameObject::Instantiate( "Player Object" );
	dptr<Transform> t2 = meshObject->AddComponent<Transform>( );
	dptr<MeshRenderer> m1 = meshObject->AddComponent<MeshRenderer>( );

	//Remove the component from the game object.
	simpleObject->RemoveComponent<Tag>( );
	//Trying to get a component that doesn't exist results in nullptr
	dptr<Tag> tag3 = simpleObject->GetComponent<Tag>( );
	if (tag3 == nullptr)
	{
		std::cout << simpleObject->GetName( ) << " doesn't have a Tag." << std::endl;
	}
	//query if a component exists
	bool hasTransform = simpleObject->HasComponent<Transform>( );
	if (hasTransform)
	{
		std::cout << simpleObject->GetName( ) << " has a Transform." << std::endl;
	}


	bool running = true;
	while (running)
	{
		ComponentRegistry::Update( );
		ComponentRegistry::Render( );


		if (GetKeyState( VK_SPACE ) & 0x8000)
		{
			meshObject->AddComponent<Tag>( );
		}
		if (GetKeyState( VK_SHIFT ) & 0x8000)
		{
			meshObject->RemoveComponent<Tag>( );
		}


		//Escape from the game loop
		if (GetKeyState( VK_ESCAPE ) & 0x8000)
		{
			running = false;
		}

		std::this_thread::sleep_for( std::chrono::milliseconds( 32 ) );
	}

	//Destroys all the components composing the gameobject
	GameObject::Destroy( meshObject );
	GameObject::Destroy( simpleObject );
}

