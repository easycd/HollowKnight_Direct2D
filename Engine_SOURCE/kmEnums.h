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
		AudioListener,
		AudioSource,
		End,
	};

	enum class eLayerType
	{
		Grid,
		Ground,
		Wall,
		Player,
		Skill,
		Effect,
		Monster,
		Boss,
		BossObj,
		Npc,
		Camera,
		Light,
		UI,
		BG,
		End,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		AudioClip,
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