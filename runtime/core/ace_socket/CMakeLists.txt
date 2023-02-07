add_library(ace_socket STATIC
  participant_acceptor.cc
  participant.cc
  protocol_hub.cc
  recorder.cc
)
target_link_libraries(ace_socket PUBLIC decoder ACE)
