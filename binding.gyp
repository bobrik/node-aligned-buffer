{
  "targets": [
    {
      "target_name": "aligned_buffer",
      "sources": [
        "src/aligned-buffer.cc"
      ],
      'conditions': [
        [ 'OS=="linux" or OS=="freebsd" or OS=="openbsd" or OS=="solaris"', {
          'cflags': ['-O2']
        }],
        ['OS=="mac"', {
          'xcode_settings': {
            'OTHER_CFLAGS': ['-O2']
          }
        }]
      ]
    }
  ]
}