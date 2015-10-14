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
    jvalue p1[1];
    p1[0].l = annotationCls;
    jobject annotation = env->CallObjectMethodA(annotatedCls, getAnnotation, p1);

    // Call the annotation instance
    jmethodID value = env->GetMethodID(annotationCls, "value", "()I");
    jvalue p0[0];
    env->CallIntMethodA(annotation, value, p0); // BOOM!
}
