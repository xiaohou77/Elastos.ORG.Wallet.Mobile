// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ElaUtils.h"
#include "MasterWalletManager.h"

using namespace Elastos::ElaWallet;

#define  CLASS_MASTERWALLET   "com/elastos/spvcore/IMasterWallet"
#define  FIELD_MASTERWALLET   "mMasterProxy"

extern const char* ToStringFromJson(const nlohmann::json& jsonValue);
extern nlohmann::json ToJosnFromString(const char* str);

static jlong JNICALL nativeInitMasterWalletManager(JNIEnv *env, jobject clazz, jstring jrootPath)
{
    const char* rootPath = env->GetStringUTFChars(jrootPath, NULL);

    MasterWalletManager* walletManager = new MasterWalletManager(rootPath);

    env->ReleaseStringUTFChars(jrootPath, rootPath);
    return (jlong)walletManager;
}

static void JNICALL nativeDisposeNative(JNIEnv *env, jobject clazz, jlong jWalletMgr)
{
    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    delete walletManager;
}

//"(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J"
static jlong JNICALL nativeCreateMasterWallet(JNIEnv *env, jobject clazz, jlong jWalletMgr, jstring jmasterWalletId
    , jstring jmnemonic, jstring jphrasePassword, jstring jpayPassword, jstring jlanguage)
{
    const char* masterWalletId = env->GetStringUTFChars(jmasterWalletId, NULL);
    const char* mnemonic = env->GetStringUTFChars(jmnemonic, NULL);
    const char* phrasePassword = env->GetStringUTFChars(jphrasePassword, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);
    const char* language = env->GetStringUTFChars(jlanguage, NULL);

    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    IMasterWallet* masterWallet = walletManager->CreateMasterWallet(masterWalletId, mnemonic, phrasePassword, payPassword,language);

    env->ReleaseStringUTFChars(jmasterWalletId, masterWalletId);
    env->ReleaseStringUTFChars(jmnemonic, mnemonic);
    env->ReleaseStringUTFChars(jphrasePassword, phrasePassword);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    env->ReleaseStringUTFChars(jlanguage, language);
    return (jlong)masterWallet;
}

static void JNICALL nativeDestroyWallet(JNIEnv *env, jobject clazz, jlong jWalletMgr, jstring jmasterWalletId)
{
    const char* masterWalletId = env->GetStringUTFChars(jmasterWalletId, NULL);

    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    walletManager->DestroyWallet(masterWalletId);

    env->ReleaseStringUTFChars(jmasterWalletId, masterWalletId);
}

static jlong JNICALL nativeImportWalletWithKeystore(JNIEnv *env, jobject clazz, jlong jWalletMgr, jstring jmasterWalletId, jstring jkeystoreContent,
        jstring jbackupPassword, jstring jpayPassword, jstring jphrasePassword)
{
    const char* masterWalletId = env->GetStringUTFChars(jmasterWalletId, NULL);
    const char* keystoreContent = env->GetStringUTFChars(jkeystoreContent, NULL);
    const char* backupPassword = env->GetStringUTFChars(jbackupPassword, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);
    const char* phrasePassword = env->GetStringUTFChars(jphrasePassword, NULL);

    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    IMasterWallet* masterWallet = walletManager->ImportWalletWithKeystore(masterWalletId, ToJosnFromString(keystoreContent), backupPassword, payPassword, phrasePassword);

    env->ReleaseStringUTFChars(jmasterWalletId, masterWalletId);
    env->ReleaseStringUTFChars(jkeystoreContent, keystoreContent);
    env->ReleaseStringUTFChars(jbackupPassword, backupPassword);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    env->ReleaseStringUTFChars(jphrasePassword, phrasePassword);
    return (jlong)masterWallet;
}

static jlong JNICALL nativeImportWalletWithMnemonic(JNIEnv *env, jobject clazz, jlong jWalletMgr, jstring jmasterWalletId,
        jstring jmnemonic, jstring jphrasePassword, jstring jpayPassword, jstring jlanguage)
{
    const char* masterWalletId = env->GetStringUTFChars(jmasterWalletId, NULL);
    const char* mnemonic = env->GetStringUTFChars(jmnemonic, NULL);
    const char* phrasePassword = env->GetStringUTFChars(jphrasePassword, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);
    const char* language = env->GetStringUTFChars(jlanguage, NULL);

    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    IMasterWallet* masterWallet = walletManager->ImportWalletWithMnemonic(masterWalletId, mnemonic, phrasePassword, payPassword, language);

    env->ReleaseStringUTFChars(jmasterWalletId, masterWalletId);
    env->ReleaseStringUTFChars(jmnemonic, mnemonic);
    env->ReleaseStringUTFChars(jphrasePassword, phrasePassword);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    env->ReleaseStringUTFChars(jlanguage, language);
    return (jlong)masterWallet;
}

static jstring JNICALL nativeExportWalletWithKeystore(JNIEnv *env, jobject clazz, jlong jWalletMgr, jobject jmasterWallet,
        jstring jbackupPassword, jstring jpayPassword)
{
    const char* backupPassword = env->GetStringUTFChars(jbackupPassword, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);

    jclass cls = env->FindClass(CLASS_MASTERWALLET);
    long masterProxy = GetJavaLongField(env, cls, jmasterWallet, FIELD_MASTERWALLET);
    CheckErrorAndLog(env, "nativeExportWalletWithKeystore", __LINE__);
    IMasterWallet* masterWallet = (IMasterWallet*)masterProxy;
    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    nlohmann::json result = walletManager->ExportWalletWithKeystore(masterWallet, backupPassword, payPassword);

    env->ReleaseStringUTFChars(jbackupPassword, backupPassword);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    return env->NewStringUTF(ToStringFromJson(result));
}

static jstring JNICALL nativeExportWalletWithMnemonic(JNIEnv *env, jobject clazz, jlong jWalletMgr,
        jobject jmasterWallet, jstring jpayPassword)
{
    jclass cls = env->FindClass(CLASS_MASTERWALLET);
    long masterProxy = GetJavaLongField(env, cls, jmasterWallet, FIELD_MASTERWALLET);
    CheckErrorAndLog(env, "nativeExportWalletWithMnemonic", __LINE__);
    IMasterWallet* masterWallet = (IMasterWallet*)masterProxy;

    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);

    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    std::string str = walletManager->ExportWalletWithMnemonic(masterWallet, payPassword);
    jstring jstr = env->NewStringUTF(str.c_str());

    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    return jstr;
}

//"(J)[J"
static jlongArray JNICALL nativeGetAllMasterWallets(JNIEnv *env, jobject clazz, jlong jWalletMgr)
{
    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    std::vector<IMasterWallet *> array = walletManager->GetAllMasterWallets();

    const int length = array.size();
    jlong* proxies = new jlong[length];
    for (int i = 0; i < length; ++i) {
        proxies[i] = (jlong)array[i];
    }

    jlongArray jarray = env->NewLongArray(length);
    env->SetLongArrayRegion(jarray, 0, length, proxies);
    delete[] proxies;
    return jarray;
}

//"(JLjava/lang/String;)Ljava/lang/String;"
static jstring JNICALL nativeGenerateMnemonic(JNIEnv *env, jobject clazz, jlong jWalletMgr, jstring jlanguage)
{
    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    const char* language = env->GetStringUTFChars(jlanguage, NULL);
    std::string mnemonic = walletManager->GenerateMnemonic(language);
    env->ReleaseStringUTFChars(jlanguage, language);
    return env->NewStringUTF(mnemonic.c_str());
}

//"()V"
static void JNICALL nativeSaveConfigs(JNIEnv *env, jobject clazz, jlong jWalletMgr)
{
    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    walletManager->SaveConfigs();
}


static const JNINativeMethod gMethods[] = {
    {"nativeInitMasterWalletManager", "(Ljava/lang/String;)J", (void*)nativeInitMasterWalletManager},
    {"nativeCreateMasterWallet", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J"
            , (void*)nativeCreateMasterWallet},
    {"nativeDisposeNative", "(J)V", (void*)nativeDisposeNative},
    {"nativeDestroyWallet", "(JLjava/lang/String;)V", (void*)nativeDestroyWallet},
    {"nativeImportWalletWithKeystore", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J", (void*)nativeImportWalletWithKeystore},
    {"nativeImportWalletWithMnemonic", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J", (void*)nativeImportWalletWithMnemonic},
    {"nativeExportWalletWithKeystore", "(JLcom/elastos/spvcore/IMasterWallet;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)nativeExportWalletWithKeystore},
    {"nativeExportWalletWithMnemonic", "(JLcom/elastos/spvcore/IMasterWallet;Ljava/lang/String;)Ljava/lang/String;", (void*)nativeExportWalletWithMnemonic},
    {"nativeGetAllMasterWallets", "(J)[J", (void*)nativeGetAllMasterWallets},
    {"nativeGenerateMnemonic", "(JLjava/lang/String;)Ljava/lang/String;", (void*)nativeGenerateMnemonic},
    {"nativeSaveConfigs", "(J)V", (void*)nativeSaveConfigs},
};

int register_elastos_spv_IMasterWalletManager(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "com/elastos/spvcore/MasterWalletManager",
        gMethods, NELEM(gMethods));
}