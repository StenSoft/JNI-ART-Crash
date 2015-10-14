#include <jni.h>

extern "C"
void Java_cz_acrobits_bugreport_art_CrashActivity_crash(JNIEnv* env, jobject self)
{
    jclass annotationCls = env->FindClass("cz/acrobits/bugreport/art/CrashActivity$Annotation");

    // getAnnotation() method
    jclass annotatedElementCls = env->FindClass("java/lang/reflect/AnnotatedElement");
    jmethodID getAnnotation = env->GetMethodID(annotatedElementCls, "getAnnotation", "(Ljava/lang/Class;)Ljava/lang/annotation/Annotation;");

    // Get the annotation instance
    jclass annotatedCls = env->FindClass("cz/acrobits/bugreport/art/CrashActivity$Annotated");
    jvalue params[1];
    params[0].l = annotationCls;
    jobject annotation = env->CallObjectMethodA(annotatedCls, getAnnotation, params);

    // Call the annotation instance
    jmethodID value = env->GetMethodID(annotationCls, "value", "()I");
    params[0].l = (jobject)0xdeadbeef; // Method without parameters, this should not be read
    env->CallIntMethodA(annotation, value, params); // BOOM!
}
