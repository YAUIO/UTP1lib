/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class Game */

#ifndef _Included_Game
#define _Included_Game
#ifdef __cplusplus
extern "C" {
#endif
#undef Game_MIN_PRIORITY
#define Game_MIN_PRIORITY 1L
#undef Game_NORM_PRIORITY
#define Game_NORM_PRIORITY 5L
#undef Game_MAX_PRIORITY
#define Game_MAX_PRIORITY 10L
#undef Game_NO_INHERIT_THREAD_LOCALS
#define Game_NO_INHERIT_THREAD_LOCALS 4L

/*
 * Class:     Game
 * Method:    fetchInternal
 * Signature: (II)[[I
 */
JNIEXPORT jobjectArray JNICALL Java_Game_fetchInternal
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     Game
 * Method:    initialize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_Game_initialize
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif