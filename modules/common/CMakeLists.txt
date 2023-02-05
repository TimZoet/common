set(NAME common)
set(TYPE module)
set(INCLUDE_DIR "include/common")
set(SRC_DIR "src")

set(HEADERS
    ${INCLUDE_DIR}/aligned_alloc.h
    ${INCLUDE_DIR}/ansi_colors.h
    ${INCLUDE_DIR}/enum_classes.h
    ${INCLUDE_DIR}/is_detected.h
    ${INCLUDE_DIR}/static_assert.h
    ${INCLUDE_DIR}/type_traits.h
)
 
set(SOURCES
    ${SRC_DIR}/aligned_alloc.cpp
)

make_target(
    NAME ${NAME}
    TYPE ${TYPE}
    VERSION ${COMMON_VERSION}
    HEADERS "${HEADERS}"
    SOURCES "${SOURCES}"
)

install_target(
    NAME ${NAME}
    TYPE ${TYPE}
    VERSION ${COMMON_VERSION}
    HEADERS "${HEADERS}"
)