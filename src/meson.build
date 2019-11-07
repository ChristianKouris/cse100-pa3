subdir('bitStream')
subdir('encoder')


compress_exe = executable('compress.cpp.executable',
    sources : ['compress.cpp'],
    dependencies : [hc_tree_dep, bit_input_stream_dep, bit_output_stream_dep],
    install : true)

uncompress_exe = executable('uncompress.cpp.executable', 
    sources: ['uncompress.cpp'],
    dependencies : [hc_tree_dep, bit_input_stream_dep, bit_output_stream_dep],
    install : true)
