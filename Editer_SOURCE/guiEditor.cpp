#include "guiEditor.h"
#include "..\\Engine_SOURCE\\kmMesh.h"
#include "..\\Engine_SOURCE\\kmMesh.h"
#include "..\\Engine_SOURCE\\kmResources.h"
#include "..\\Engine_SOURCE\\kmTransform.h"
#include "..\\Engine_SOURCE\\kmMeshRenderer.h"
#include "..\\Engine_SOURCE\\kmMaterial.h"
#include "..\\Engine_SOURCE\\kmRenderer.h"

#include "kmGridScript.h"

namespace gui
{
	using namespace km::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugOjbects = {};

	void Editor::Initialize()
	{
		mDebugOjbects.resize((UINT)eColliderType::End);

		std::shared_ptr<km::Mesh> mesh
			= km::Resources::Find<km::Mesh>(L"DebugRect");
		std::shared_ptr<km::Material> material
			= km::Resources::Find<km::Material>(L"DebugMaterial");

		mDebugOjbects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<km::Transform>();
		km::MeshRenderer* mr
			= mDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<km::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComponent<km::MeshRenderer>();
		mr->SetMesh(km::Resources::Find<km::Mesh>(L"RectMesh"));
		mr->SetMaterial(km::Resources::Find<km::Material>(L"GridMaterial"));
		km::GridScript* gridSc = grid->AddComponent<km::GridScript>();
		gridSc->SetCamera(renderer::cameras[0]);

		mEditorObjects.push_back(grid);
	}

	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}

	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}

	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const km::graphics::DebugMesh& mesh
			: renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
	}

	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugOjbects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void Editor::DebugRender(const km::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugOjbects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		km::Transform* tr = debugObj->GetComponent<km::Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		tr->LateUpdate();

		/*km::MeshRenderer * mr
			= debugObj->GetComponent<km::MeshRenderer>();*/
			// main camera
		km::Camera* mainCamara = renderer::mainCamera;

		km::Camera::SetGpuViewMatrix(mainCamara->GetViewMatrix());
		km::Camera::SetGpuProjectionMatrix(mainCamara->GetProjectionMatrix());

		debugObj->Render();
	}
}