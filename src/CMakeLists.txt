add_subdirectory(pgs)
target_include_directories (pgs PUBLIC)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET libavdevice libavfilter libavformat libavcodec libswresample libswscale libavutil)
find_library(TESSERACT NAMES tesseract tess REQUIRED)

add_executable(sup2srt sup2srt.cpp mkvUtil.cpp srtUtil.cpp)

target_link_libraries(sup2srt "${TESSERACT_LIBRARIES}" "PkgConfig::LIBAV" pgs)