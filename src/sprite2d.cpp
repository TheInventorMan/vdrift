#include "sprite2d.h"
#include "texturemanager.h"

void SPRITE2D::Unload(SCENENODE & parent)
{
	if (node.valid())
	{
		SCENENODE & noderef = GetNode(parent);
		noderef.GetDrawlist().twodim.erase(draw);
		parent.Delete(node);
	}
	node.invalidate();
	draw.invalidate();
	
	varray.Clear();
}

bool SPRITE2D::Load(
	SCENENODE & parent,
	const std::string & texturefile,
	const std::string & texturesize,
	TEXTUREMANAGER & textures,
	float draworder,
	std::ostream & error_output)
{
	Unload(parent);

	assert(!draw.valid());
	assert(!node.valid());

	TEXTUREINFO texinfo;
	texinfo.mipmap = false;
	texinfo.repeatu = false;
	texinfo.repeatv = false;
	texinfo.npot = false;
	texinfo.size = texturesize;
	std::tr1::shared_ptr<TEXTURE> texture;
	if (!textures.Load(texturefile, texinfo, texture)) return false;

	node = parent.AddNode();
	SCENENODE & noderef = parent.GetNode(node);
	draw = noderef.GetDrawlist().twodim.insert(DRAWABLE());
	DRAWABLE & drawref = GetDrawableFromNode(noderef);

	drawref.SetDiffuseMap(texture);
	drawref.SetVertArray(&varray);
	drawref.SetDrawOrder(draworder);
	drawref.SetCull(false, false);
	drawref.SetColor(r,g,b,a);

	//std::cout << "Sprite draworder: " << draworder << std::endl;

	return true;
}

bool SPRITE2D::Load(
	SCENENODE & parent,
	std::tr1::shared_ptr<TEXTURE> texture2d,
	float draworder,
	std::ostream & error_output)
{
	Unload(parent);

	assert(!draw.valid());
	assert(!node.valid());

	node = parent.AddNode();
	SCENENODE & noderef = parent.GetNode(node);
	draw = noderef.GetDrawlist().twodim.insert(DRAWABLE());
	DRAWABLE & drawref = GetDrawableFromNode(noderef);

	drawref.SetDiffuseMap(texture2d);
	drawref.SetVertArray(&varray);
	drawref.SetDrawOrder(draworder);
	drawref.SetCull(false, false);
	drawref.SetColor(r,g,b,a);
	
	return true;
}