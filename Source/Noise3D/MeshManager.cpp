
/***********************************************************************

							class��MeshManager

				description: manager class to manage Mesh

***********************************************************************/
#include "Noise3D.h"

using namespace Noise3D;

Mesh * MeshManager::CreateMesh(SceneNode* pAttachedNode, N_UID meshName)
{
	if (pAttachedNode == nullptr)
	{
		ERROR_MSG("MeshMgr: Failed to create mesh. Father scene node is invalid.");
		return nullptr;
	}
	Mesh* pMesh = IFactory<Mesh>::CreateObject(meshName);

	//init scene object info(necessary for class derived from ISceneObject)
	pMesh->ISceneObject::mFunc_InitSceneObject(meshName, pAttachedNode);

	return pMesh;
}

/***********************************************************************
								P R I V A T E					                    
***********************************************************************/

MeshManager::MeshManager():IFactory<Mesh>(50000)
{

}

MeshManager::~MeshManager()
{
	IFactory<Mesh>::DestroyAllObject();
}
