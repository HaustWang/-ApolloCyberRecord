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
#include <string>
#include "com_apollo_cyber_tools.hpp"
#include "com_apollo_cyber_RecordWriter.h"

using apollo::cyber::record::PyRecordWriter;

#ifdef __cplusplus
extern "C"
{
#endif
/*
 * Class:     com_apollo_cyber_RecordWriter
 * Method:    createWriter
 * Signature: (Ljava/lang/String;)Z
 */
  JNIEXPORT jboolean JNICALL Java_com_apollo_cyber_RecordWriter_createWriter(JNIEnv *env, jobject obj, jstring file_path)
  {
    PyRecordWriter *writer = new PyRecordWriter();
    if (NULL == writer)
    {
      return false;
    }

    bool opened = writer->Open(jstring_to_utf8(env, file_path));
    if (!opened)
    {
      delete writer;
      return false;
    }

    jfieldID fid = get_handle_FieldID(env, obj);
    env->SetLongField(obj, fid, (jlong)writer);
    return true;
  }

/*
 * Class:     com_apollo_cyber_RecordWriter
 * Method:    destroyWriter
 * Signature: ()V
 */
  JNIEXPORT void JNICALL Java_com_apollo_cyber_RecordWriter_destroyWriter(JNIEnv *env, jobject obj)
  {
    PyRecordWriter *writer = (PyRecordWriter *)get_handle(env, obj);
    if (NULL == writer)
    {
      return;
    }

    writer->Close();
    delete writer;
  }

/*
 * Class:     com_apollo_cyber_RecordWriter
 * Method:    writeChannel
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
  JNIEXPORT jboolean JNICALL Java_com_apollo_cyber_RecordWriter_writeChannel(JNIEnv *env, jobject obj, jstring channel, jstring type, jstring proto_desc)
  {
    PyRecordWriter *writer = (PyRecordWriter *)get_handle(env, obj);
    if (NULL == writer)
    {
      return false;
    }

    return writer->WriteChannel(jstring_to_utf8(env, channel), jstring_to_utf8(env, type), jstring_to_utf8(env, proto_desc));
  }

/*
 * Class:     com_apollo_cyber_RecordWriter
 * Method:    writeMessage
 * Signature: (Ljava/lang/String;[BJLjava/lang/String;)Z
 */
  JNIEXPORT jboolean JNICALL Java_com_apollo_cyber_RecordWriter_writeMessage(JNIEnv *env, jobject obj, jstring channel, jbyteArray rawmessage, jlong time, jstring proto_desc)
  {
    PyRecordWriter *writer = (PyRecordWriter *)get_handle(env, obj);
    if (NULL == writer)
    {
      return false;
    }

    int len = env->GetArrayLength(rawmessage);
    std::string msg;
    msg.reserve(len);
    env->GetByteArrayRegion(rawmessage, 0, len, reinterpret_cast<jbyte *>((char *)(msg.data())));
    return writer->WriteMessage(jstring_to_utf8(env, channel), msg, time, jstring_to_utf8(env, proto_desc));
  }

/*
 * Class:     com_apollo_cyber_RecordWriter
 * Method:    setSizeOfFileSegmentation
 * Signature: (J)Z
 */
  JNIEXPORT jboolean JNICALL Java_com_apollo_cyber_RecordWriter_setSizeOfFileSegmentation(JNIEnv *env, jobject obj, jlong size_kilobytes)
  {
    PyRecordWriter *writer = (PyRecordWriter *)get_handle(env, obj);
    if (NULL == writer)
    {
      return false;
    }

    return writer->SetSizeOfFileSegmentation(size_kilobytes);
  }

/*
 * Class:     com_apollo_cyber_RecordWriter
 * Method:    setIntervalOfFileSegmentation
 * Signature: (J)Z
 */
  JNIEXPORT jboolean JNICALL Java_com_apollo_cyber_RecordWriter_setIntervalOfFileSegmentation(JNIEnv *env, jobject obj, jlong time_sec)
  {
    PyRecordWriter *writer = (PyRecordWriter *)get_handle(env, obj);
    if (NULL == writer)
    {
      return false;
    }

    return writer->SetIntervalOfFileSegmentation(time_sec);
  }

/*
 * Class:     com_apollo_cyber_RecordWriter
 * Method:    getMessageNumber
 * Signature: (Ljava/lang/String;)J
 */
  JNIEXPORT jlong JNICALL Java_com_apollo_cyber_RecordWriter_getMessageNumber(JNIEnv *env, jobject obj, jstring channel)
  {
    PyRecordWriter *writer = (PyRecordWriter *)get_handle(env, obj);
    if (NULL == writer)
    {
      return 0;
    }

    return writer->GetMessageNumber(jstring_to_utf8(env, channel));
  }

/*
 * Class:     com_apollo_cyber_RecordWriter
 * Method:    getMessageType
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
  JNIEXPORT jstring JNICALL Java_com_apollo_cyber_RecordWriter_getMessageType(JNIEnv *env, jobject obj, jstring channel)
  {
    PyRecordWriter *writer = (PyRecordWriter *)get_handle(env, obj);
    if (NULL == writer)
    {
      return NULL;
    }

    std::string message_type = writer->GetMessageType(jstring_to_utf8(env, channel));
    return env->NewStringUTF(message_type.c_str());
  }

/*
 * Class:     com_apollo_cyber_RecordWriter
 * Method:    getProtoDesc
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
  JNIEXPORT jstring JNICALL Java_com_apollo_cyber_RecordWriter_getProtoDesc(JNIEnv *env, jobject obj, jstring channel)
  {
    PyRecordWriter *writer = (PyRecordWriter *)get_handle(env, obj);
    if (NULL == writer)
    {
      return NULL;
    }

    std::string proto_desc = writer->GetProtoDesc(jstring_to_utf8(env, channel));
    return env->NewStringUTF(proto_desc.c_str());
  }

#ifdef __cplusplus
}
#endif
