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

public class RecordWriter {
    // 创建数据包写入句柄
    public native boolean createWriter(String filePath);

    // 删除数据包写入句柄
    public native void destroyWriter();

    // 向数据包中写入通道的信息，包括通道的类型名和类型描述。该描述是protobuf的描述
    public native boolean writeChannel(String channel, String type, String protoDesc);

    // 向数据包中写入对应通道的数据。time为数据的时间戳
    public native boolean writeMessage(String channel, byte[] rawmessage, long time, String protoDesc);

    // 向数据包中写入对应通道的数据。time为数据的时间戳
    public boolean writeMessage(String channel, byte[] rawmessage, long time)
    {
        return writeMessage(channel, rawmessage, time, "");
    }

    // 设置数据包文件分片大小
    public native boolean setSizeOfFileSegmentation(long sizeKilobytes);

    // 设置数据包文件分片的时间长度
    public native boolean setIntervalOfFileSegmentation(long timeSec);

    // 获取写入的对应通道的消息数量
    public native long getMessageNumber(String channel);

    // 获取写入的对应通道的消息类型名
    public native String getMessageType(String channel);

    // 获取写入的对应通道的消息类描述
    public native String getProtoDesc(String channel);

    // 写入句柄
    private long handle;
}
