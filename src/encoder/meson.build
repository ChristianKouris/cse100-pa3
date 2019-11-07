hc_tree = library('hc_tree',
                  sources: ['HCTree.cpp', 'HCTree.hpp', 'HCNode.hpp'],
                  dependencies: [bit_input_stream_dep, bit_output_stream_dep])


inc = include_directories('.')


hc_tree_dep = declare_dependency(include_directories: inc, 
    link_with: hc_tree,
    dependencies: [bit_input_stream_dep, bit_output_stream_dep])
