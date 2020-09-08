#include "samples-workflow.hpp"

#include <Windows.h>
#include <chrono>

using time_point = std::chrono::high_resolution_clock;

LRESULT DefaultWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

workflows::core::samples_workflow::samples_workflow(const samples_workflow_status& status) :
	mStatus(status)
{
	const auto hInstance = GetModuleHandle(nullptr);
	const auto class_name = mStatus.name;
	
	WNDCLASS appInfo;

	appInfo.style = CS_DBLCLKS;
	appInfo.lpfnWndProc = DefaultWindowProc;
	appInfo.cbClsExtra = 0;
	appInfo.cbWndExtra = 0;
	appInfo.hInstance = hInstance;
	appInfo.hIcon = static_cast<HICON>(LoadImage(nullptr, "", IMAGE_ICON, 0, 0, LR_LOADFROMFILE));
	appInfo.hCursor = LoadCursor(nullptr, IDC_ARROW);
	appInfo.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	appInfo.lpszMenuName = nullptr;
	appInfo.lpszClassName = &class_name[0];

	RegisterClass(&appInfo);

	RECT rect;

	rect.top = 0;
	rect.left = 0;
	rect.right = static_cast<UINT>(mStatus.width);
	rect.bottom = static_cast<UINT>(mStatus.height);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	mStatus.handle = CreateWindow(&class_name[0], &class_name[0], WS_OVERLAPPEDWINDOW ^
		WS_SIZEBOX ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);

	mStatus.living = true;

	ShowWindow(static_cast<HWND>(mStatus.handle), SW_SHOW);
}

workflows::core::null workflows::core::samples_workflow::start(const null& input)
{
	auto current = time_point::now();

	while (mStatus.living == true) {
		MSG message;

		message.hwnd = static_cast<HWND>(mStatus.handle);

		while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);

			if (message.message == WM_QUIT) mStatus.living = false;
		}

		if (mStatus.living == false) break;

		auto duration = std::chrono::duration_cast<
			std::chrono::duration<float>>(time_point::now() - current);

		current = time_point::now();
	}
	
	return null();
}
