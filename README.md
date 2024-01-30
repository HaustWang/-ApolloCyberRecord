# ApolloCyberRecord

### 介绍
该代码是对百度Apollo的CyberRecord文件进行解析和写入的Java库。该代码是从Apollo的开源代码中抽取了CyberRecord的代码，并在py_record.h提供的接口上进行的JNI接口封装，并采用Maven进行编译管理。

### 使用说明

#### 方式一：
1. 从git上下载该代码
2. 将代码中的record_jni的目录拷贝到自己的代码中。可以按照自己的要求修改包名等。
3. install该库到本地的repo中。
4. 在使用的项目的pom.xml中引入依赖。
5. 在使用前调用NarSystem.loadLibrary()方法。

#### 方式二：
1. 从git上下载该代码
2. install该库到本地的repo中。 
3. 在使用的项目的pom.xml中引入依赖。 
4. 在使用前调用NarSystem.loadLibrary()方法。

***使用可以参照test_record_jni***

### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Requests

### 特殊说明

1. 编译c++库使用了nar-maven-plugin，参照：https://maven-nar.github.io/index.html
2. 在使用nar-maven-plugin中，c++依赖库使用<configuration>下的<linker>配置。
