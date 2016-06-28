#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <SDL.h>

/*
* Get the resource path for resources located in res/subDir
* It's assumed the project directory is structured like:
* bin/
*  the executable
* res/
*  Lesson1/
*  Lesson2/
*
* Paths returned will be Lessons/res/subDir
*/
char* getResourcePath(char* subDir) {
	// 	char* subDir = NULL;
	//We need to choose the path separator properly based on which
	//platform we're running on, since Windows uses a different
	//separator than most systems
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	//This will hold the base resource path: Lessons/res/
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static char* baseRes;
	if (NULL == baseRes) {
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			// 			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			fprintf(stderr, "Error getting resource path: %s\n", SDL_GetError());
			return "";
		}
		//We replace the last bin/ with res/ to get the the resource path
		// 		size_t pos = baseRes.rfind("bin");
#ifdef _DEBUG
		char* pos_t = strstr(baseRes, "Debug");
#else
		char* pos_t = strstr(baseRes, "Release");
#endif
		int len_t = strlen(pos_t);
		int len_b = strlen(baseRes);
		strncpy(pos_t, baseRes, len_b - len_t);
		char* pos = pos_t;
		// 		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
		sprintf(baseRes, "%s%s%c%s%c", pos, "res", PATH_SEP, "res", PATH_SEP);
	}
	//If we want a specific subdirectory path in the resource directory
	//append it to the base path. This would be something like Lessons/res/Lesson0
	// 	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
	// 	return (0 == subDir) ? baseRes : (baseRes + (int)subDir + PATH_SEP);
	if (0 != subDir) {
		sprintf(baseRes, "%s%s%c", baseRes, subDir, PATH_SEP);
	}
	return baseRes;
}//res_path
