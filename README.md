## EC_Framework
An implementation of Entity-Component architecture inspired by Unity3D and Unreal Engine.

#### Features
* A Entity-Componenet framework with a simple API, where GameObjects are composed of components.
* Fast iterations through components using a custom allocator which ensures that components of a given type are always tightly-packed together.
* Safety Measures to avoid adding duplicate components to GameObjects, removing or accessing non-existent components from GameObjects.
* Automatic deallocation of components and it's resources on GameObject destruction. This means, No need to worry about components once added.
* The framework also provides methods to remove a component on-demand from a GameObject.

#### Usage
Include the header `GameObject.h` wherever ypu need to interact with GameObjects and Components in your project. Include the header `ComponentRegistry.h` where you have the game loop, so as to call component callbacks. Following is an example of how to use the framework:

```
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <thread>

//Include this wherever you need to interact with GameObjects and Components
#include "GameObject.h"
//Include this in the file with the game loop so as to call the component callbacks accordingly
#include "ComponentRegistry.h"

//These are user-created components 
#include "Transform.h"
#include "MeshRenderer.h"
#include "Tag.h"

int main( )
{
	//Register components so that only their selected virtual functions are called
        //ComponenetRegistry::Register<T>(update, render);
	ComponentRegistry::Register<Transform>( true, false );
	ComponentRegistry::Register<MeshRenderer>( false, true );
	ComponentRegistry::Register<Tag>( false, false );

        //Instantiating a GameObject
	GameObject* simpleObject = GameObject::Instantiate( "Simple Object" );
	dptr<Transform> t1 = simpleObject->AddComponent<Transform>( );
	dptr<Tag> tag1 = simpleObject->AddComponent<Tag>( );

	//Tring to add multiple components of the same type to a GameObject
	dptr<Tag> tag2 = simpleObject->AddComponent<Tag>( );


	GameObject* meshObject = GameObject::Instantiate( "Player Object" );
	dptr<Transform> t2 = meshObject->AddComponent<Transform>( );
	dptr<MeshRenderer> m1 = meshObject->AddComponent<MeshRenderer>( );

	//Removing a component from a GameObject
	simpleObject->RemoveComponent<Tag>( );
  
	//Trying to get a component that doesn't exist (results in nullptr)
	dptr<Tag> tag3 = simpleObject->GetComponent<Tag>( );
	if (tag3 == nullptr)
	{
		std::cout << simpleObject->GetName( ) << " doesn't have a Tag." << std::endl;
	}
  
	//Querying if a component exists in the GameObject
	bool hasTransform = simpleObject->HasComponent<Transform>( );
	if (hasTransform)
	{
		std::cout << simpleObject->GetName( ) << " has a Transform." << std::endl;
	}


        //Game Loop
	bool running = true;
	while (running)
	{
                //Calls OnUpdate on all components which has registred it's OnUpdate function
		ComponentRegistry::Update( );
		ComponentRegistry::Render( );

		//Escape from the game loop
		if (GetKeyState( VK_ESCAPE ) & 0x8000)
		{
			running = false;
		}
	}

	//Destroys all the components composing the GameObject and the GameObject itself
	GameObject::Destroy( meshObject );
	GameObject::Destroy( simpleObject );
  
  return 0;
}
```
And, here is how to setup a component:

```
#include <iostream>
#include "Component.h"

//256 is the block size used by the memory allocator
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
```
## Growing List Allocator

![growinglistallocator](https://github.com/fishingGrapes/CustomAllocators/blob/master/images/growinglistallocator.png)

I needed to iterate through a collection of components(similar to Unity3D) every frame. There are game objects which are composed of components and these components contain behaviour like Transform, Camera, Light, Mesh Renderer and so on, which need to be updated every frame. I could not afford to iterate through components at different places in memory. So I wrote this allocactor which is nothing but a list of fixed-size memory blocks and actively keeps the objects tightly packed on allocation and deallocation, so as to ensure the best cache locality and fast iterations. 

#### Usage
```c++
int main( )
{
	GrowingBlockAllocator<Pack, 3> allocator;
	std::vector< ptr_ref<Pack>> packs;

	std::cout << '\n' << "**************************" << '\n' << std::endl;
	for (size_t i = 0; i < 7; i++)
	{
		packs.push_back( allocator.instantiate( static_cast<int32_t>( 1 + i ) ) );
	}

	std::cout << '\n' << "**************************" << '\n' << std::endl;
	allocator.release( packs[ 1 ] );
	allocator.release( packs[ 4 ] );

	std::cout << "Is packs[4] null? " << ( packs[ 4 ] == nullptr ) << std::endl;
	packs[ 4 ] = allocator.instantiate( 8 );
	std::cout << "Is packs[4] null? " << ( packs[ 4 ] == nullptr ) << std::endl;

	std::cout << '\n' << "**************************" << '\n' << std::endl;

	std::cout << "Elements in Memery Pool :" << std::endl;
	for (size_t i = 0; i < allocator.size( ); i++)
	{
		std::cout << "Data_" << allocator[ i ]->value << std::endl;
	}
	std::cout << '\n' << "**************************" << '\n' << std::endl;

	return 0;
}
```
