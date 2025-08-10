
#ifdef NDEBUG
#include <Windows.h>
#endif

#include "Engine.h"

#ifdef NDEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int main()
#endif
{
	Engine::RunEngine();
	return 0;
}