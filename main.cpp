#include <iostream>
#include <jni.h>

int main() {
  JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
  JNIEnv *env;                      // Pointer to native interface
  //================== prepare loading of Java VM ============================
  JavaVMInitArgs vm_args;                        // Initialization arguments
  JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
  options[0].optionString = "-Djava.class.path=./java";   // where to find java .class
  vm_args.version = JNI_VERSION_1_6;             // minimum Java version
  vm_args.nOptions = 1;                          // number of options
  vm_args.options = options;
  vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
  //=============== load and initialize Java VM and JNI interface =============
  jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
  delete options;    // we then no longer need the initialisation options.
  if (rc != JNI_OK) {
    // TO DO: error processing...
    exit(EXIT_FAILURE);
  }
  //=============== Display JVM version =======================================
  std::cout << "JVM load succeeded: Version ";
  jint ver = env->GetVersion();
  std::cout << ((ver>>16)&0x0f) << "."<<(ver&0x0f) << std::endl;

  // TO DO: add the code that will use JVM <============  (see next steps)
  // SetByteArrayRegion to copy to a Java Array
  jclass cls2 = env->FindClass("MyExpt");  // try to find the class
  if(cls2 == nullptr) {
      std::cerr << "ERROR: class not found !";
  } else {                                  // if class found, continue
    std::cout << "Class MyTest found" << std::endl;
    jmethodID mid = env->GetStaticMethodID(cls2, "mymain", "()V");  // find method
    if(mid == nullptr)
      std::cerr << "ERROR: method void mymain() not found !" << std::endl;
    else {
      env->CallStaticVoidMethod(cls2, mid);                      // call method
      std::cout << std::endl;
    }
}

  jvm->DestroyJavaVM();

  return 0;
}
