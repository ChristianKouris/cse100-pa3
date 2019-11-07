bit_input_stream = library('bit_input_stream',
                           sources: ['BitInputStream.cpp', 
                                     'BitInputStream.hpp'])


inc = include_directories('.')


bit_input_stream_dep = declare_dependency(include_directories: inc,
    link_with: bit_input_stream)
