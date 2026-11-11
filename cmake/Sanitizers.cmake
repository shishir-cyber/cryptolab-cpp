function(cryptolab_enable_sanitizers target)
  if(CRYPTOLAB_SANITIZE AND NOT MSVC)
    target_compile_options(${target} PUBLIC
      -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(${target} PUBLIC -fsanitize=address,undefined)
  endif()
endfunction()
