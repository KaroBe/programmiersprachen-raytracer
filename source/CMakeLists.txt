add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)

#raxtracer
add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

#raxtracer
add_executable(raytracer_loop raytracer_loop.cpp)

target_link_libraries(raytracer_loop ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer_loop glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer_loop DESTINATION .)


#sdf_creator
add_executable(sdf_creator sdf_creator.cpp)

target_link_libraries(sdf_creator ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(sdf_creator glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS sdf_creator DESTINATION .)



# Build tests
add_executable(tests
  tests.cpp)
target_link_libraries(tests
  ${GLFW_LIBRARIES}
  ${FRAMEWORK_NAME}
  )

# add_executable(aufgabe5 
# aufgabe5.cpp)
# target_link_libraries(tests
#   ${GLFW_LIBRARIES}
#   ${FRAMEWORK_NAME}
#   )

