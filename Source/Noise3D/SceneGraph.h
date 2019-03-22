
/***********************************************************************

								 h��Scene Node
				desc: a single node in a scene graph, storing 
				transformation and some geometry, object binding infos
				(similar to OGRE's idea)

************************************************************************/

#pragma once

namespace Noise3D
{

	class SceneGraph;
	class ISceneObject;

	//Scene Node is a base class that contains Tree operation and transformation info
	class SceneNode :
		public TreeNodeTemplate<SceneNode, SceneGraph>
	{
	public:

		SceneNode();

		~SceneNode();

		AffineTransform& GetLocalTransform();//relative to its father node (if current node is attached to root node, then local=world)

		//traverse through scene graph(from given node to root) and concatenate local transforms.
		//evaluated world matrix(relative to root) won't cache in ScenNode by default
		//set 'cacheResult' to true in order to cache the evaluated world matrix 
		//(which can be directly retrived until the cache is cleared)
		NMATRIX EvalWorldAffineTransformMatrix(bool cacheResult = false);

		//eval world matrix, and its inverse-transpose
		void EvalWorldAffineTransformMatrix(NMATRIX& outWorldMat, NMATRIX& outWorldInvTranspose, bool cacheResult = false);

		//eval world matrix, and its inverse, and its inverse-transpose
		void EvalWorldAffineTransformMatrix(NMATRIX& outWorldMat, NMATRIX& outWorldInv, NMATRIX& outWorldInvTranspose, bool cacheResult = false);

		//only consider Rotation and Translation
		NMATRIX EvalWorldRigidTransformMatrix(bool cacheResult = false);

		//only consider Rotation
		NMATRIX EvalWorldRotationMatrix(bool cacheResult = false);

		//clear world matrix cache, disable retrival
		void ClearWorldMatrixCache();

		//determine if world matrix has been stored.
		bool IsWorldMatrixCached();

		//attach scene object to this node
		void AttachSceneObject(ISceneObject* pObj);

		//detach scene object from this node, clear reference to pObj
		void DetachSceneObject(ISceneObject* pObj);

		//,
		bool IsAttachedSceneObject();

	protected:

		AffineTransform mLocalTransform;

		std::vector<ISceneObject*> mAttachedSceneObjectList;

		//(2019.3.23)to avoid tremendous re-calculation by setting 'cacheResult'
		//when eval world transform matrix
		bool mIsWorldMatrixCached;
		NMATRIX mWorldMatrixCache;

	};

	class SceneGraph :
		public TreeTemplate<SceneNode,SceneGraph>
	{
	public:


	private:

		friend class SceneManager;

		SceneGraph();

		~SceneGraph();

	};

};