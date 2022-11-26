cmake_minimum_required(VERSION 3.1.0)

project(cpp-backend CXX)

set(FILTER_FILES    CheckLoginFilter.h
                    TimeoutFilter.h
                    CommonFilters.h
    )

set(HANDLER_FILES   UserController.h
                    ContentController.h
                    #UserController.cpp
                    RedirectController.h
                    RedirectController.cpp
    )

set(GENERAL_SRC_FILES   JsonResponse.h
                        Error.h)

set(ALL_FILTERS)
foreach(FILTER IN LISTS FILTER_FILES)
    set(ALL_FILTERS ${FILTERS} filters/${FILTER})
endforeach()

set(ALL_HANDLERS)
foreach(HANDLER IN LISTS HANDLER_FILES)
    set(ALL_HANDLERS ${HANDLERS} handlers/${HANDLER})
endforeach()

set(ALL_GENERAL_SRC)
foreach(SRC IN LISTS GENERAL_SRC_FILES)
    set(ALL_GENERAL_SRC ${ALL_GENERAL_SRC} general_src/${SRC})
endforeach()

add_subdirectory(third_party/drogon)

add_executable  (cpp-backend    main.cpp
                                ${ALL_GENERAL_SRC}
                                ${ALL_FILTERS}
                                ${ALL_HANDLERS}
                )

set_property(TARGET drogon PROPERTY CXX_STANDARD 17)

target_include_directories(cpp-backend PRIVATE general_src filters handlers)
target_compile_features(cpp-backend PUBLIC cxx_std_20)
target_link_libraries(cpp-backend PRIVATE drogon)