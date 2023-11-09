/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jni_Master */

#ifndef _Included_jni_Master
#define _Included_jni_Master
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jni_Master
 * Method:    parseFiles
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_jni_Master_parseFiles
  (JNIEnv *, jclass, jint);

/*
 * Class:     jni_Master
 * Method:    filter
 * Signature: (Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_jni_Master_filter
  (JNIEnv *, jclass, jstring, jint, jstring, jstring);

/*
 * Class:     jni_Master
 * Method:    getPieData
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_jni_Master_getPieData
  (JNIEnv *, jclass);

/*
 * Class:     jni_Master
 * Method:    getDisciplinesSummerData
 * Signature: (II)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_jni_Master_getDisciplinesSummerData
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jni_Master
 * Method:    getDisciplinesWinterData
 * Signature: (II)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_jni_Master_getDisciplinesWinterData
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jni_Master
 * Method:    getHieghtSummerData
 * Signature: (II)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_jni_Master_getHieghtSummerData
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jni_Master
 * Method:    getHeightWinterData
 * Signature: (II)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_jni_Master_getHeightWinterData
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jni_Master
 * Method:    getWeightSummerData
 * Signature: (II)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_jni_Master_getWeightSummerData
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jni_Master
 * Method:    getWeightWinterData
 * Signature: (II)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_jni_Master_getWeightWinterData
  (JNIEnv *, jclass, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
