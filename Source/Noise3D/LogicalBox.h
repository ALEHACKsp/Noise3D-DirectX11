
/*********************************************************

								Logical Box
		geometry representation that is not based on polygon.
		instead, it's based on analytic description

************************************************************/

#pragma once

namespace Noise3D
{
	//side's of AABB (or box in local space)
	enum NOISE_BOX_FACET
	{
		POS_X=0, NEG_X, POS_Y, NEG_Y, POS_Z, NEG_Z
	};

	class /*_declspec(dllexport)*/ LogicalBox :
		public ILogicalShape
	{
	public:

		//compute normal on given surface position
		//('facet' is used to explicit decide  face, avoid the rounding error on box's corner, might round to adjacent facet)
		bool ComputeNormal(NOISE_BOX_FACET facet);

	private:

	};

}