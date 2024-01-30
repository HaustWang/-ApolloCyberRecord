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

#ifndef _Included_com_apollo_cyber_tools
#define _Included_com_apollo_cyber_tools

#include <string>
#include <jni.h>

#ifdef __cplusplus
extern "C"
{
#endif
    static std::string jstring_to_utf8(JNIEnv *env, jstring j_str)
    {
        jsize length = env->GetStringUTFLength(j_str);
        const char *const base = env->GetStringUTFChars(j_str, NULL);
        if (base == NULL)
        {
            return "";
        }
        std::string value(base, length);
        env->ReleaseStringUTFChars(j_str, base);
        return value;
    }

    static jfieldID get_handle_FieldID(JNIEnv *env, jobject obj)
    {
        jclass cls = env->GetObjectClass(obj);
        jfieldID fid = env->GetFieldID(cls, "handle", "J");
        return fid;
    }

    static long get_handle(JNIEnv *env, jobject obj)
    {
        jclass cls = env->GetObjectClass(obj);
        jfieldID fid = env->GetFieldID(cls, "handle", "J");
        return env->GetLongField(obj, fid);
    }

#ifdef __cplusplus
}
#endif
#endif // !_Included_com_apollo_cyber_tools