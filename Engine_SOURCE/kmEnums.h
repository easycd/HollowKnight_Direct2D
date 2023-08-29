#pragma once

namespace km::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Collider2D,
		Ground,
		Particle,
		MeshRenderer,
		Animator,
		Script,
		Light,
		Camera,
		Rigidbody,
		End,
	};

	enum class eLayerType
	{
		Grid,
		Ground,
		Player,
		Effect,
		Monster,
		Boss,
		BossObj,
		Camera,
		Light,
		UI,
		BG,
		End = 16,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};
}