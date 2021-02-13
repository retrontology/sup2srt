configure_file(sup2srtConfig.h.in sup2srtConfig.h)

include_directories("${PROJECT_BINARY_DIR}/src")

set(MINIMUM_TESSERACT_VERSION 4.0.0)
set(MINIMUM_LEPTONICA_VERSION 1.73)

add_subdirectory(pgs)

find_package(PkgConfig REQUIRED)

find_package(TIFF REQUIRED COMPONENTS CXX)
include_directories( ${TIFF_INCLUDE_DIRS} )
link_directories( ${TIFF_LIBRARY_DIRS} )

pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET libavdevice libavformat libavcodec libavutil)

pkg_search_module( LEPTONICA REQUIRED lept )
include_directories( ${LEPTONICA_INCLUDE_DIRS} )
link_directories( ${LEPTONICA_LIBRARY_DIRS} )

pkg_search_module( TESSERACT REQUIRED tesseract )
include_directories( ${TESSERACT_INCLUDE_DIRS} )
link_directories( ${TESSERACT_LIBRARY_DIRS} )

add_executable(sup2srt sup2srt.cpp mkvUtil.cpp srtUtil.cpp)
add_executable(sup2disk sup2disk.cpp mkvUtil.cpp)

target_link_libraries(sup2srt "${TIFF_LIBRARIES}" "${LEPTONICA_LIBRARIES}" "${TESSERACT_LIBRARIES}" "PkgConfig::LIBAV" pgs)
target_link_libraries(sup2disk "PkgConfig::LIBAV")

install(TARGETS sup2srt DESTINATION bin)
install(TARGETS sup2disk DESTINATION bin)

