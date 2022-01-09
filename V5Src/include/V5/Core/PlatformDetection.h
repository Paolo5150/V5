// Platform detection using predefined macros

#define V5_GRAPHICS_API_VULKAN
//#define V5_GRAPHICS_API_OPENGL

#ifdef _WIN64
#define V5_PLATFORM_WINDOWS
#else
#define V5_PLATFORM_ANDROID
#endif

