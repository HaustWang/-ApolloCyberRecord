/******************************************************************************
 * Copyright 2023, Wang Yanyin<wyy123_2008@qq.com>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

package com.apollo.cyber;

class RecordReader {
    // 创建文件读取句柄
    public native boolean createReader(String filePath);

    // 销毁读取句柄
    public native void destroyReader();

    // 读取消息
    public native RecordBagMessage readMessage(long beginTime, long endTime);

    // 读取消息
    public RecordBagMessage readMessage(long beginTime) {
        return readMessage(beginTime, Long.MAX_VALUE);
    }

    // 读取消息
    public RecordBagMessage readMessage() {
        return readMessage(0);
    }

    // 获取数据包中的消息数量
    public native int getMessageNumber(String channelName);

    // 获取对应话题的protobuf类型名
    public native String getMessageType(String channelName);

    // 获取对应的话题通道的protobuf的描述
    public native byte[] getProtoDesc(String channelName);

    // 获取文件头信息，返回二进制信息，实际是protobuf的序列化后内容
    public native byte[] getHeaderString();

    // 获取文件头信息，返回Json信息
    public native String getHeaderJson();

    // 重置读取
    public native void reset();

    // 获取话题通道列表
    public native String[] getChannelList();

    // 文件读取句柄
    private long handle;
}
