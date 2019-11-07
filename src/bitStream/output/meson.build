bit_output_stream = library('bit_output_stream',
                            sources: ['BitOutputStream.cpp', 
                                      'BitOutputStream.hpp'])


inc = include_directories('.')


bit_output_stream_dep = declare_dependency(include_directories: inc,
    link_with: bit_output_stream)
