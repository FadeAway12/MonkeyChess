#include <jni.h>
	
extern "C" {

	JNIEXPORT int JNICALL poop
	(JNIEnv*, int x, int y) {
		return x + y;
	}

}