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

#include "cyber/python/internal/py_record.h"

#include <jni.h>
#include <set>
#include <string>
#include "com_apollo_cyber_tools.hpp"
#include "com_apollo_cyber_RecordReader.h"

using apollo::cyber::record::PyRecordReader;

#ifdef __cplusplus
extern "C"
{
#endif
/*
 * Class:     com_apollo_cyber_RecordReader
 * Method:    createReader
 * Signature: (Ljava/lang/String;)Z
 */
  JNIEXPORT jboolean JNICALL Java_com_apollo_cyber_RecordReader_createReader(JNIEnv *env, jobject obj, jstring filePath)
  {
    PyRecordReader *reader = new PyRecordReader(jstring_to_utf8(env, filePath));
    if (NULL == reader)
    {
      return false;
    }

    jfieldID fid = get_handle_FieldID(env, obj);
    env->SetLongField(obj, fid, (jlong)reader);
    return true;
  }

/*
 * Class:     com_apollo_cyber_RecordReader
 * Method:    destroyReader
 * Signature: ()V
 */
  JNIEXPORT void JNICALL Java_com_apollo_cyber_RecordReader_destroyReader(JNIEnv *env, jobject obj)
  {
    PyRecordReader *reader = (PyRecordReader *)get_handle(env, obj);
    if (NULL == reader)
    {
      return;
    }
    delete reader;
  }

/*
 * Class:     com_apollo_cyber_RecordReader
 * Method:    readMessage
 * Signature: (JJ)Lcom/apollo/cyber/RecordBagMessage;
 */
  JNIEXPORT jobject JNICALL Java_com_apollo_cyber_RecordReader_readMessage(JNIEnv *env, jobject obj, jlong beginTime, jlong endTime)
  {
    PyRecordReader *reader = (PyRecordReader *)get_handle(env, obj);
    if (NULL == reader)
    {
      return NULL;
    }

    apollo::cyber::record::BagMessage msg = reader->ReadMessage(beginTime, endTime);
    if (msg.end)
    {
      return NULL;
    }

    jclass bagcls = env->FindClass("com/apollo/cyber/RecordBagMessage");
    jmethodID constructor = env->GetMethodID(bagcls, "<init>", "()V");
    jobject ret = env->NewObject(bagcls, constructor);
    env->SetLongField(ret, env->GetFieldID(bagcls, "timestamp", "J"), msg.timestamp);
    env->SetObjectField(ret, env->GetFieldID(bagcls, "channelName", "Ljava/lang/String;"),
                        env->NewStringUTF(msg.channel_name.c_str()));
    env->SetObjectField(ret, env->GetFieldID(bagcls, "dataType", "Ljava/lang/String;"),
                        env->NewStringUTF(msg.data_type.c_str()));
    jbyteArray contents = env->NewByteArray(msg.data.length());
    env->SetByteArrayRegion(contents, 0, msg.data.length(), (const jbyte *)(msg.data.c_str()));
    env->SetObjectField(ret, env->GetFieldID(bagcls, "data", "[B"), contents);
    return ret;
  }

/*
 * Class:     com_apollo_cyber_RecordReader
 * Method:    getMessageNumber
 * Signature: (Ljava/lang/String;)I
 */
  JNIEXPORT jint JNICALL Java_com_apollo_cyber_RecordReader_getMessageNumber(JNIEnv *env, jobject obj, jstring channelName)
  {
    PyRecordReader *reader = (PyRecordReader *)get_handle(env, obj);
    if (NULL == reader)
    {
      return 0;
    }

    return reader->GetMessageNumber(jstring_to_utf8(env, channelName));
  }

/*
 * Class:     com_apollo_cyber_RecordReader
 * Method:    getMessageType
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
  JNIEXPORT jstring JNICALL Java_com_apollo_cyber_RecordReader_getMessageType(JNIEnv *env, jobject obj, jstring channelName)
  {
    PyRecordReader *reader = (PyRecordReader *)get_handle(env, obj);
    if (NULL == reader)
    {
      return NULL;
    }

    std::string message_type = reader->GetMessageType(jstring_to_utf8(env, channelName));
    return env->NewStringUTF(message_type.c_str());
  }

/*
 * Class:     com_apollo_cyber_RecordReader
 * Method:    getProtoDesc
 * Signature: (Ljava/lang/String;)[B
 */
  JNIEXPORT jbyteArray JNICALL Java_com_apollo_cyber_RecordReader_getProtoDesc(JNIEnv *env, jobject obj, jstring channelName)
  {
    PyRecordReader *reader = (PyRecordReader *)get_handle(env, obj);
    if (NULL == reader)
    {
      return NULL;
    }

    std::string proto_desc = reader->GetProtoDesc(jstring_to_utf8(env, channelName));
    jbyteArray ret = env->NewByteArray(proto_desc.length());
    env->SetByteArrayRegion(ret, 0, proto_desc.length(), (const jbyte *)(proto_desc.c_str()));
    return ret;
  }

/*
 * Class:     com_apollo_cyber_RecordReader
 * Method:    getHeaderString
 * Signature: ()[B
 */
  JNIEXPORT jbyteArray JNICALL Java_com_apollo_cyber_RecordReader_getHeaderString(JNIEnv *env, jobject obj)
  {
    PyRecordReader *reader = (PyRecordReader *)get_handle(env, obj);
    if (NULL == reader)
    {
      return NULL;
    }

    std::string header_string = reader->GetHeaderString();
    jbyteArray ret = env->NewByteArray(header_string.length());
    env->SetByteArrayRegion(ret, 0, header_string.length(), (const jbyte *)(header_string.c_str()));
    return ret;
  }

/*
 * Class:     com_apollo_cyber_RecordReader
 * Method:    getHeaderJson
 * Signature: ()Ljava/lang/String;
 */
  JNIEXPORT jstring JNICALL Java_com_apollo_cyber_RecordReader_getHeaderJson(JNIEnv *env, jobject obj)
  {
    PyRecordReader *reader = (PyRecordReader *)get_handle(env, obj);
    if (NULL == reader)
    {
      return NULL;
    }

    std::string header_json = reader->GetHeaderJson();
    return env->NewStringUTF(header_json.c_str());
  }

/*
 * Class:     com_apollo_cyber_RecordReader
 * Method:    reset
 * Signature: ()V
 */
  JNIEXPORT void JNICALL Java_com_apollo_cyber_RecordReader_reset(JNIEnv *env, jobject obj)
  {
    PyRecordReader *reader = (PyRecordReader *)get_handle(env, obj);
    if (NULL == reader)
    {
      return;
    }

    reader->Reset();
  }

/*
 * Class:     com_apollo_cyber_RecordReader
 * Method:    getChannelList
 * Signature: ()[Ljava/lang/String;
 */
  JNIEXPORT jobjectArray JNICALL Java_com_apollo_cyber_RecordReader_getChannelList(JNIEnv *env, jobject obj)
  {
    PyRecordReader *reader = (PyRecordReader *)get_handle(env, obj);
    if (NULL == reader)
    {
      return NULL;
    }

    std::set<std::string> channel_list = reader->GetChannelList();
    jclass strcls = env->FindClass("java/lang/String");
    jobjectArray ret = env->NewObjectArray(channel_list.size(), strcls, NULL);
    int i = 0;
    for (std::string str : channel_list)
    {
        env->SetObjectArrayElement(ret, i++, env->NewStringUTF(str.c_str()));
    }
    return ret;
  }
#ifdef __cplusplus
}
#endif