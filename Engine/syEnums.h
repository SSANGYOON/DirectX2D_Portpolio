#pragma once

namespace sy::enums
{
	enum class LayerType
	{
		None = 0,
		/*Only Used in 2D*/ BackGround,
		Camera,
		Grid,
		Monster,
		Player,
		UI,
		End = 16,
	};

	enum class ComponentType
	{
		None,
		Transform,
		Camera,
		Mesh,
		Collider,
		MeshRenderrer,
		SpriteRenderrer,
		UI,
		Script,
		End,
	};

	enum class ResourceType
	{
		Mesh,
		Texture,
		Material,
		SpriteAnimation,
		Sound,
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};
}