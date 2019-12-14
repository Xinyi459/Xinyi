project(final)

add_executable(BVTreeCollisionDetection BVTreeCollisionDetection.c bouncingBoxTree.c BVTreeTraversal.c getCond_new.c inputData.c)
target_link_libraries(BVTreeCollisionDetection m)
