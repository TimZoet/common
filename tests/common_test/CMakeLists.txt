find_package(bettertest REQUIRED)

set(NAME common_test)
set(TYPE test)
set(INCLUDE_DIR "include/common_test")
set(SRC_DIR "src")

set(HEADERS
	${INCLUDE_DIR}/enum_classes.h
	${INCLUDE_DIR}/type_traits.h
)
 
set(SOURCES
	${SRC_DIR}/main.cpp

	${SRC_DIR}/enum_classes.cpp
	${SRC_DIR}/type_traits.cpp
)

set(DEPS_PRIVATE
	bettertest::bettertest
	common::common
)

make_target(TYPE ${TYPE} NAME ${NAME} OUTDIR "tests" STARTUP HEADERS "${HEADERS}" SOURCES "${SOURCES}" DEPS_PRIVATE "${DEPS_PRIVATE}")