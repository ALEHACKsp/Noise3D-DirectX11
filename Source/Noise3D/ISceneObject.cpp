/***********************************************************

								ISceneObject

			interface that will be inherited by some 'Object' 
			like mesh/actor/particles/light blahblahblah.
			ISceneObject can be bound to SceneNode to enable
			hierarchical transformation (and add to scene graph)

***********************************************************/
#include "Noise3D.h"

using namespace Noise3D;



Noise3D::ISceneObject::ISceneObject():
	m_pAttachedSceneNode(nullptr)
{
}

Noise3D::ISceneObject::~ISceneObject()
{
}

//bounding box of transformed bounding box
N_AABB Noise3D::ISceneObject::ComputeWorldAABB_Fast()
{
	//Scene Object is bound with an

	//local aabb
	N_AABB localAabb =this->GetLocalAABB();
	const Vec3& a = localAabb.min;
	const Vec3& b = localAabb.max;

	//world transform matrix (under scene graph's root's coordinate system)
	Matrix worldMat = m_pAttachedSceneNode->EvalWorldTransform().GetAffineTransformMatrix();

	//get 8 vertices coord of local AABB
	Vec3 vertices[8] = 
	{
		{a.x, a.y, a.z},
		{ b.x, a.y, a.z },
		{ a.x, b.y, a.z },
		{ a.x, a.y, b.z },
		{ b.x, b.y, a.z },
		{ b.x, a.y, b.z },
		{ a.x, b.y, b.z },
		{ b.x, b.y, b.z }
	};

	for (uint32_t i = 0; i < 8; ++i)
	{
		//apply world transform of scene node to 8 vertices of local AABB
		vertices[i] = AffineTransform::TransformVector_MatrixMul(vertices[i], worldMat); //trans.TransformVector_Affine(vertices[i]);
	}

	//find the AABB of these 8 transformed vertices
	N_AABB outAabb;

	for (uint32_t i = 0; i < 8; i++)
	{
		Vec3  & tmpV =vertices[i];
		if (tmpV.x < (outAabb.min.x)) { outAabb.min.x = tmpV.x; }
		if (tmpV.y < (outAabb.min.y)) { outAabb.min.y = tmpV.y; }
		if (tmpV.z < (outAabb.min.z)) { outAabb.min.z = tmpV.z; }

		if (tmpV.x >(outAabb.max.x)) { outAabb.max.x = tmpV.x; }
		if (tmpV.y >(outAabb.max.y)) { outAabb.max.y = tmpV.y; }
		if (tmpV.z >(outAabb.max.z)) { outAabb.max.z = tmpV.z; }
	}

	return outAabb;
}

std::string Noise3D::ISceneObject::GetName()
{
	return mUid;
}

void Noise3D::ISceneObject::AttachToSceneNode(SceneNode * pNode)
{
	if (pNode != nullptr)
	{
		//m_pAttachedSceneNode will be set by friend function of SceneNode
		pNode->AttachSceneObject(this);
	}
}

void Noise3D::ISceneObject::DetachFromSceneNode()
{
	if (m_pAttachedSceneNode != nullptr)
	{
		m_pAttachedSceneNode->DetachSceneObject(this);
	}
}

SceneNode * Noise3D::ISceneObject::GetAttachedSceneNode() const
{
	return m_pAttachedSceneNode;
}

void Noise3D::ISceneObject::mFunc_InitSceneObject(const std::string & name, SceneNode* pNode)
{
	mUid = name;
	//(2019.3.9) in ISceneObject's constructor, SceneNode's 'IsBoundToObject' is initialized to true
	ISceneObject::AttachToSceneNode(pNode);
}
