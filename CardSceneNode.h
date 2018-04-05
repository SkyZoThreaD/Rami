#pragma once

#include "CardType.h"

class CSampleSceneNode : public scene::ISceneNode
{
	core::aabbox3d<f32> Box;
	video::S3DVertex Vertices[4];
	video::SMaterial Material;

public:

	CSampleSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id, video::IVideoDriver *drv, CardType type) : scene::ISceneNode(parent, mgr, id)
	{
		Material.Wireframe = false;
		Material.Lighting = false;

		f32 Card_W = 10/2;
		f32 Card_H = 15/2;

		TC_area tc_array = TC_from_CardType(type);

		Vertices[0] = video::S3DVertex(core::vector3df(0+ Card_H, 0, 0+ Card_W), core::vector3df(0, 1, 0), video::SColor(255, 255, 255, 255), core::vector2d< f32 >(tc_array.u_max, tc_array.v_min));
		Vertices[1] = video::S3DVertex(core::vector3df(0- Card_H, 0, 0+ Card_W), core::vector3df(0, 1, 0), video::SColor(255, 255, 255, 255), core::vector2d< f32 >(tc_array.u_max, tc_array.v_max));
		Vertices[2] = video::S3DVertex(core::vector3df(0- Card_H, 0, 0- Card_W), core::vector3df(0, 1, 0), video::SColor(255, 255, 255, 255), core::vector2d< f32 >(tc_array.u_min, tc_array.v_max));
		Vertices[3] = video::S3DVertex(core::vector3df(0+ Card_H, 0, 0- Card_W), core::vector3df(0, 1, 0), video::SColor(255, 255, 255, 255), core::vector2d< f32 >(tc_array.u_min, tc_array.v_min));

		Box.reset(Vertices[0].Pos);
		for (s32 i = 1; i<4; ++i) Box.addInternalPoint(Vertices[i].Pos);

		//setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
		setMaterialFlag(video::EMF_LIGHTING, false);
		setMaterialFlag(video::EMF_ZBUFFER, true);
		if(type.m_col == CardColor::Jocker) setMaterialTexture(0, drv->getTexture("./Media/joker.png"));
		else setMaterialTexture(0, drv->getTexture("./Media/classic-cards.png"));
		//setScale(irr::core::vector3df(.4, .4, .4));
	}

	virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();
	}

	virtual void render()
	{
		u16 indices[] = { 0,2,3, 2,1,3, 1,0,3, 2,0,1 };
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(Material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
	}

	virtual const core::aabbox3d<f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual u32 getMaterialCount() const
	{
		return 1;
	}

	virtual video::SMaterial& getMaterial(u32 i)
	{
		return Material;
	}
};