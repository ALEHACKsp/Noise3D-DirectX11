
/***********************************************************************

							desc��Advanced Material for Path Tracer 

************************************************************************/

#include "Noise3D.h"

using namespace Noise3D;
using namespace Noise3D::Ut;

void Noise3D::GI::PbrtMaterial::SetAlbedo(Color4f albedo)
{
	mMatDesc.albedo = albedo;
}

void Noise3D::GI::PbrtMaterial::SetAlbedoMap(Texture2D * pMap)
{
	mMatDesc.pAlbedoMap = pMap;
}

void Noise3D::GI::PbrtMaterial::SetRoughness(float r)
{
	r = Ut::Clamp(r, 0.0f, 1.0f);
	mMatDesc.roughness = r;
}

void Noise3D::GI::PbrtMaterial::SetRoughnessMap(Texture2D * pMap)
{
	mMatDesc.pRoughnessMap = pMap;
}

void Noise3D::GI::PbrtMaterial::SetTransparency(float t)
{
	t= Ut::Clamp(t, 0.0f, 1.0f);
	mMatDesc.transparency = t;
}

void Noise3D::GI::PbrtMaterial::SetMetallicity(float m)
{
	m = Ut::Clamp(m, 0.0f, 1.0f);
	mMatDesc.metallicity = m;
}

void Noise3D::GI::PbrtMaterial::SetMetallicityMap(Texture2D * pMap)
{
	mMatDesc.pMetallicityMap = pMap;
}

void Noise3D::GI::PbrtMaterial::SetEmission(Vec3 hdrEmission)
{
	mMatDesc.emission = hdrEmission;
}

void Noise3D::GI::PbrtMaterial::SetEmissionMap(Texture2D * pMap)
{
	mMatDesc.pEmissiveMap = pMap;
}

void Noise3D::GI::PbrtMaterial::SetMetalF0(Vec3 F0)
{
	mMatDesc.metal_F0 = Ut::Clamp(F0,Vec3(0,0,0),Vec3(1.0f,1.0f,1.0f));
}

void Noise3D::GI::PbrtMaterial::SetRefractiveIndex(float ior)
{
	if (ior <= 1.0f)ior = 1.001f;
	mMatDesc.ior = ior;
}

bool Noise3D::GI::PbrtMaterial::IsTransmissionEnabled()
{
	return mMatDesc.transparency != 1.0f;
}

bool Noise3D::GI::PbrtMaterial::IsEmissionEnabled()
{
	return mMatDesc.emission!= Vec3(0,0,0);
}

void Noise3D::GI::PbrtMaterial::SetDesc(const N_PbrtMatDesc & desc)
{
	mMatDesc = desc;
}

const GI::N_PbrtMatDesc & Noise3D::GI::PbrtMaterial::GetDesc()
{
	return mMatDesc;
}

void Noise3D::GI::PbrtMaterial::Preset_PerfectGlass(float ior)
{
	mMatDesc.albedo = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
	mMatDesc.emission = Vec3(0, 0, 0);
	mMatDesc.ior = Ut::Clamp(ior,1.0f,std::numeric_limits<float>::infinity());
	mMatDesc.metallicity = 0.0f;
	float F0 = mFunc_IorToF0(mMatDesc.ior);
	mMatDesc.metal_F0 = Vec3(F0, F0, F0);
	mMatDesc.transparency = 0.0f;
	mMatDesc.roughness = 0.0f;
}

float Noise3D::GI::PbrtMaterial::mFunc_IorToF0(float ior)
{
	float x = (ior - 1.0f) / (ior + 1.0f);
	return x*x;
}

//---------------------------------------------

Noise3D::GI::IPbrtMaterialOwner::IPbrtMaterialOwner():
	m_pGiMat(nullptr)
{
	m_pGiMat = Noise3D::GetScene()->GetMaterialMgr()->GetDefaultAdvancedMaterial();
}

Noise3D::GI::IPbrtMaterialOwner::~IPbrtMaterialOwner()
{
}

void Noise3D::GI::IPbrtMaterialOwner::SetPbrtMaterial(GI::PbrtMaterial * pMat)
{
	m_pGiMat = pMat;
}

GI::PbrtMaterial * Noise3D::GI::IPbrtMaterialOwner::GetPbrtMaterial()
{
	return m_pGiMat;
}
