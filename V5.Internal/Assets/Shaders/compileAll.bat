glslangValidator.exe -G src/textureOnly.vert -o bin/textureOnly.vert.spv
glslangValidator.exe -G src/textureOnly.frag -o bin/textureOnly.frag.spv

glslangValidator.exe -G src/textureOnlyInstanced.vert -o bin/textureOnlyInstanced.vert.spv
glslangValidator.exe -G src/textureOnlyInstanced.frag -o bin/textureOnlyInstanced.frag.spv

glslangValidator.exe -G src/textureOnlyBatched.vert -o bin/textureOnlyBatched.vert.spv
glslangValidator.exe -G src/textureOnlyBatched.frag -o bin/textureOnlyBatched.frag.spv

glslangValidator.exe -G src/tileTextureOnlyInstanced.vert -o bin/tileTextureOnlyInstanced.vert.spv
glslangValidator.exe -G src/tileTextureOnlyInstanced.frag -o bin/tileTextureOnlyInstanced.frag.spv

pause