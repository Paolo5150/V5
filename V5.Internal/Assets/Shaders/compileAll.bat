glslangValidator.exe -G src/colorOnly.vert -o bin/colorOnly.vert.spv
glslangValidator.exe -G src/colorOnly.frag -o bin/colorOnly.frag.spv

glslangValidator.exe -G src/textureOnly.vert -o bin/textureOnly.vert.spv
glslangValidator.exe -G src/textureOnly.frag -o bin/textureOnly.frag.spv

pause