
#ifdef NDEBUG
#include <Windows.h>
#endif

#ifdef NDEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int main()
#endif
{
	return 0;
}