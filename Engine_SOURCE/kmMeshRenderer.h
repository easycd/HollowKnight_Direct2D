#pragma once
#include "kmComponent.h"
#include "kmMesh.h"
#include "kmMaterial.h"

namespace km
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }
		std::shared_ptr<Material> GetMaterial() { return mMaterial; }


	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;




		Vector3 mScale;
	};
}
