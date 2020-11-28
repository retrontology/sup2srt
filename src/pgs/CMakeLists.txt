find_library(TIFF NAMES tiff REQUIRED COMPONENTS CXX)

add_library(pgs compositionObject.cpp displaySegment.cpp objectDefinitionSegment.cpp paletteDefinitionSegment.cpp paletteSegment.cpp pgsParser.cpp pgsSegment.cpp pgsSegmentHeader.cpp pgsUtil.cpp presentationCompositionSegment.cpp windowDefinitionSegment.cpp windowSegment.cpp)

target_link_libraries(pgs "${TIFF_LIBRARIES}")