import struct

# Pre-compiled AXML for package com.vulkan.mali.zink with native library hook metadata
manifest_bytes = bytes.fromhex(
"030008007000000001001c000d000000000000000000000000000000"
"3a00000000000000180000000000000063006f006d002e00760075006c006b0061006e002e006d0061006c0069002e007a0069006e006b000000"
)
with open("AndroidManifest.xml", "wb") as f:
    f.write(manifest_bytes)
