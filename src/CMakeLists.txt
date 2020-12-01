# Specify minimum version
set(MINIMUM_TESSERACT_VERSION 4.0.0)
set(MINIMUM_LEPTONICA_VERSION 1.74)

add_subdirectory(pgs)
target_include_directories (pgs PUBLIC)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET libavdevice libavformat libavcodec libavutil)
pkg_search_module( LEPTONICA REQUIRED lept )
pkg_search_module( TESSERACT REQUIRED tesseract )
include_directories( ${LEPTONICA_INCLUDE_DIRS} )
include_directories( ${TESSERACT_INCLUDE_DIRS} )
link_directories( ${LEPTONICA_LIBRARY_DIRS} )
link_directories( ${TESSERACT_LIBRARY_DIRS} )

add_executable(sup2srt sup2srt.cpp mkvUtil.cpp srtUtil.cpp)

target_link_libraries(sup2srt pgs "${LEPTONICA_LIBRARIES}" "${TESSERACT_LIBRARIES}" "PkgConfig::LIBAV")