# select the 3D backend for sokol_gfx.h and sokol_app.h
# the sokol_config() macro is in the top-level CMakeLists.txt file!
sokol_config()

fips_ide_group(Samples/clear)
fips_begin_app(clear-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(clear-sapp.c)
    fips_deps(sokol)
fips_end_app()
fips_begin_app(clear-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(clear-sapp.c)
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(clear-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/triangle)
fips_begin_app(triangle-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(triangle-sapp.c)
    sokol_shader(triangle-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(triangle-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(triangle-sapp.c)
    sokol_shader(triangle-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(triangle-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/quad)
fips_begin_app(quad-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(quad-sapp.c)
    sokol_shader(quad-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(quad-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(quad-sapp.c)
    sokol_shader(quad-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(quad-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/bufferoffsets)
fips_begin_app(bufferoffsets-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(bufferoffsets-sapp.c)
    sokol_shader(bufferoffsets-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(bufferoffsets-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(bufferoffsets-sapp.c)
    sokol_shader(bufferoffsets-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(bufferoffsets-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/cube)
fips_begin_app(cube-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(cube-sapp.c)
    sokol_shader(cube-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(cube-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(cube-sapp.c)
    sokol_shader(cube-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(cube-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/noninterleaved)
fips_begin_app(noninterleaved-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(noninterleaved-sapp.c)
    sokol_shader(noninterleaved-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(noninterleaved-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(noninterleaved-sapp.c)
    sokol_shader(noninterleaved-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(noninterleaved-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/texcube)
fips_begin_app(texcube-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(texcube-sapp.c)
    sokol_shader(texcube-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(texcube-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(texcube-sapp.c)
    sokol_shader(texcube-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(texcube-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/offscreen)
fips_begin_app(offscreen-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(offscreen-sapp.c)
    sokol_shader(offscreen-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(offscreen-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(offscreen-sapp.c)
    sokol_shader(offscreen-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(offscreen-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/instancing)
fips_begin_app(instancing-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(instancing-sapp.c)
    sokol_shader(instancing-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(instancing-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(instancing-sapp.c)
    sokol_shader(instancing-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(instancing-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/mrt)
fips_begin_app(mrt-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(mrt-sapp.c)
    sokol_shader(mrt-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(mrt-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(mrt-sapp.c)
    sokol_shader(mrt-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(mrt-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/arraytex)
fips_begin_app(arraytex-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(arraytex-sapp.c)
    sokol_shader(arraytex-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(arraytex-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(arraytex-sapp.c)
    sokol_shader(arraytex-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(arraytex-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/dyntex)
fips_begin_app(dyntex-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(dyntex-sapp.c)
    sokol_shader(dyntex-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(dyntex-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(dyntex-sapp.c)
    sokol_shader(dyntex-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(dyntex-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/mipmap)
fips_begin_app(mipmap-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(mipmap-sapp.c)
    sokol_shader(mipmap-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(mipmap-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(mipmap-sapp.c)
    sokol_shader(mipmap-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(mipmap-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/blend)
fips_begin_app(blend-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(blend-sapp.c)
    sokol_shader(blend-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(blend-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(blend-sapp.c)
    sokol_shader(blend-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(blend-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/uvwrap)
fips_begin_app(uvwrap-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(uvwrap-sapp.c)
    sokol_shader(uvwrap-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(uvwrap-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(uvwrap-sapp.c)
    sokol_shader(uvwrap-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(uvwrap-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/fontstash)
fips_begin_app(fontstash-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(fontstash-sapp.c)
    fips_deps(sokol)
    fips_dir(data)
    fipsutil_copy(fontstash.yml)
fips_end_app()
fips_begin_app(fontstash-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(fontstash-sapp.c)
    fips_deps(sokol dbgui imgui)
    fips_dir(data)
    fipsutil_copy(fontstash.yml)
fips_end_app()
target_compile_definitions(fontstash-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/imgui)
fips_begin_app(imgui-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(imgui-sapp.cc)
    fips_deps(sokol imgui)
    if (FIPS_IOS)
        fips_files(ios-info.plist)
    endif()
fips_end_app()

fips_begin_app(imgui-highdpi-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(imgui-highdpi-sapp.cc)
    fips_deps(sokol imgui)
    if (FIPS_IOS)
        fips_files(ios-info.plist)
    endif()
fips_end_app()

fips_begin_app(cimgui-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(cimgui-sapp.c)
    fips_deps(sokol cimgui)
    if (FIPS_IOS)
        fips_files(ios-info.plist)
    endif()
fips_end_app()

fips_begin_app(imgui-usercallback-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(imgui-usercallback-sapp.c)
    sokol_shader(imgui-usercallback-sapp.glsl ${slang})
    fips_deps(sokol cimgui)
    if (FIPS_IOS)
        fips_files(ios-info.plist)
    endif()
fips_end_app()

fips_ide_group(Samples/saudio)
fips_begin_app(saudio-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(saudio-sapp.c)
    fips_deps(sokol)
    if (FIPS_IOS)
        fips_files(ios-info.plist)
    endif()
fips_end_app()

fips_ide_group(Samples/events)
fips_begin_app(events-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(events-sapp.cc)
    fips_deps(sokol imgui)
    if (FIPS_IOS)
        fips_files(ios-info.plist)
    endif()
fips_end_app()

fips_ide_group(Samples/pixelformats)
fips_begin_app(pixelformats-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(pixelformats-sapp.c)
    sokol_shader(pixelformats-sapp.glsl ${slang})
    fips_deps(sokol cimgui)
    if (FIPS_IOS)
        fips_files(ios-info.plist)
    endif()
fips_end_app()

# on emscripten, build a second pixelformats simple which enforces WebGL
if (FIPS_EMSCRIPTEN)
fips_begin_app(pixelformats-gles2-sapp windowed)
    fips_files(pixelformats-sapp.c)
    sokol_shader(pixelformats-sapp.glsl ${slang})
    fips_deps(sokol cimgui)
fips_end_app()
target_compile_definitions(pixelformats-gles2-sapp PRIVATE USE_GLES2)
endif()

fips_ide_group(Samples/modplay)
fips_begin_app(modplay-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(modplay-sapp.c)
    if (FIPS_IOS)
        fips_files(ios-info.plist)
    endif()
    fips_dir(data)
    fipsutil_embed(mods.yml mods.h)
    fips_deps(sokol libmodplug)
fips_end_app()

fips_ide_group(Samples/sgl)
fips_begin_app(sgl-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(sgl-sapp.c)
    fips_deps(sokol)
fips_end_app()
fips_begin_app(sgl-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(sgl-sapp.c)
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(sgl-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/sgl-lines)
fips_begin_app(sgl-lines-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(sgl-lines-sapp.c)
    fips_deps(sokol)
fips_end_app()
fips_begin_app(sgl-lines-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(sgl-lines-sapp.c)
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(sgl-lines-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/sgl-microui)
fips_begin_app(sgl-microui-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(sgl-microui-sapp.c)
    fips_deps(sokol microui)
fips_end_app()
# NOTE: this uses cimgui
fips_begin_app(sgl-microui-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(sgl-microui-sapp.c)
    fips_deps(sokol cdbgui cimgui microui)
fips_end_app()
target_compile_definitions(sgl-microui-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/loadpng)
fips_begin_app(loadpng-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(loadpng-sapp.c)
    sokol_shader(loadpng-sapp.glsl ${slang})
    fips_dir(data)
    fipsutil_copy(loadpng-assets.yml)
    fips_deps(sokol stb)
fips_end_app()
fips_begin_app(loadpng-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(loadpng-sapp.c)
    sokol_shader(loadpng-sapp.glsl ${slang})
    fips_dir(data)
    fipsutil_copy(loadpng-assets.yml)
    fips_deps(sokol dbgui imgui stb)
fips_end_app()
target_compile_definitions(loadpng-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/cubemaprt)
fips_begin_app(cubemaprt-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(cubemaprt-sapp.c)
    sokol_shader(cubemaprt-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()

#fips_begin_app(cubemaprt-sapp-ui windowed)
#    fips_vs_warning_level(3)
#    fips_files(cubemaprt-sapp.c)
#    fips_deps(sokol dbgui imgui)
#fips_end_app()
#target_compile_definitions(cubemaprt-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/sdf)
fips_begin_app(sdf-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(sdf-sapp.c)
    sokol_shader(sdf-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(sdf-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(sdf-sapp.c)
    sokol_shader(sdf-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(sdf-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/plmpeg)
fips_begin_app(plmpeg-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(plmpeg-sapp.c)
    sokol_shader(plmpeg-sapp.glsl ${slang})
    fips_dir(data)
    fipsutil_copy(plmpeg-assets.yml)
    fips_deps(sokol)
fips_end_app()
fips_begin_app(plmpeg-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(plmpeg-sapp.c)
    sokol_shader(plmpeg-sapp.glsl ${slang})
    fips_dir(data)
    fipsutil_copy(plmpeg-assets.yml)
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(plmpeg-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/cgltf)
fips_begin_app(cgltf-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(cgltf-sapp.c)
    sokol_shader(cgltf-sapp.glsl ${slang})
    fips_dir(data)
    fipsutil_copy(cgltf-assets.yml)
    fips_deps(sokol basisu)
fips_end_app()
fips_begin_app(cgltf-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(cgltf-sapp.c)
    sokol_shader(cgltf-sapp.glsl ${slang})
    fips_dir(data)
    fipsutil_copy(cgltf-assets.yml)
    fips_deps(sokol dbgui imgui basisu)
fips_end_app()
target_compile_definitions(cgltf-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/debugtext)
fips_begin_app(debugtext-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(debugtext-sapp.c)
    fips_deps(sokol)
fips_end_app()
fips_begin_app(debugtext-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(debugtext-sapp.c)
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(debugtext-sapp-ui PRIVATE USE_DBG_UI)
fips_begin_app(debugtext-printf-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(debugtext-printf-sapp.c)
    fips_deps(sokol)
fips_end_app()
fips_begin_app(debugtext-printf-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(debugtext-printf-sapp.c)
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(debugtext-printf-sapp-ui PRIVATE USE_DBG_UI)
fips_begin_app(debugtext-userfont-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(debugtext-userfont-sapp.c)
    fips_deps(sokol)
fips_end_app()
fips_begin_app(debugtext-userfont-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(debugtext-userfont-sapp.c)
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(debugtext-userfont-sapp-ui PRIVATE USE_DBG_UI)
fips_begin_app(debugtext-context-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(debugtext-context-sapp.c)
    sokol_shader(debugtext-context-sapp.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(debugtext-context-sapp-ui windowed)
    fips_vs_warning_level(3)
    fips_files(debugtext-context-sapp.c)
    sokol_shader(debugtext-context-sapp.glsl ${slang})
    fips_deps(sokol dbgui imgui)
fips_end_app()
target_compile_definitions(debugtext-context-sapp-ui PRIVATE USE_DBG_UI)

fips_ide_group(Samples/restart)
fips_begin_app(restart-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(restart-sapp.c)
    sokol_shader(restart-sapp.glsl ${slang})
    fips_dir(data)
    fipsutil_copy(restart-assets.yml)
    fips_deps(sokol-memtrack stb)
fips_end_app()

if (NOT FIPS_ANDROID)
fips_ide_group(Samples/noentry)
fips_begin_app(noentry-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(noentry-sapp.c)
    sokol_shader(noentry-sapp.glsl ${slang})
    fips_deps(sokol-noentry)
fips_end_app()
endif()

if (FIPS_WINDOWS)
fips_ide_group(Samples/noentry-dll)
fips_begin_app(noentry-dll-sapp windowed)
    fips_vs_warning_level(3)
    fips_files(noentry-dll-sapp.c)
    sokol_shader(noentry-dll-sapp.glsl ${slang})
    fips_deps(sokol-dll)
fips_end_app()
endif()

