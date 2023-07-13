#pragma once
#include "..\\Engine_SOURCE\\CommonInclude.h"
#include "..\\Engine_SOURCE\\GameEngine.h"
#include "..\\Engine_SOURCE\\kmGraphics.h"

#include "guiWidget.h"
#include "guiEditorObject.h"
#include "guiDebugObject.h"

namespace gui
{
	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const km::graphics::DebugMesh& mesh);

	private:
		static std::vector<Widget*> mWidgets;
		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugObject*> mDebugOjbects;
	};
}

