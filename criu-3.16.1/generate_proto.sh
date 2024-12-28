#!/bin/bash

# 设置 proto 文件的搜索路径
PROTO_PATH="./images:./test/zdtm/static:./test/others/unix-callback:./test/others/rpc"

# 查找所有 .proto 文件并生成对应的 C 代码
find . -name "*.proto" | while read proto_file; do
    # 生成 C 代码，指定 proto_path
    protoc-c --proto_path=$PROTO_PATH --c_out=. "$proto_file"
done


