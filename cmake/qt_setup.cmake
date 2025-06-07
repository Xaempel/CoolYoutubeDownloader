find_package(Qt6 REQUIRED COMPONENTS Widgets)

function(setup_target TARGET_NAME)
    target_link_libraries(${TARGET_NAME} PUBLIC Qt6::Widgets)
    set_target_properties(${TARGET_NAME} PROPERTIES AUTOUIC_SEARCH_PATHS "./src/frontend")
endfunction()