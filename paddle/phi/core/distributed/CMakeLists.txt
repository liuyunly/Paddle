add_subdirectory(check)
add_subdirectory(store)
add_subdirectory(auto_parallel)

set(DISTRIBUTED_COMMON_SRCS comm_context_manager.cc)

if(WITH_NCCL OR WITH_RCCL)
  list(APPEND DISTRIBUTED_COMMON_SRCS nccl_comm_context.cc)
endif()

if(WITH_GLOO)
  list(APPEND DISTRIBUTED_COMMON_SRCS gloo_utils.cc gloo_comm_context.cc)
endif()

collect_srcs(core_srcs SRCS ${DISTRIBUTED_COMMON_SRCS})
