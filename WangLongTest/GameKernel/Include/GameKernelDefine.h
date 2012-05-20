/*
*
*/

#ifndef GAMEKERNELDEFINE_H
#define GAMEKERNELDEFINE_H

#ifdef GAMEKERNEL_EXPORTS
	#define KERNEL_DLL __declspec(dllexport)
#else
	#ifndef GAMEKERNEL_STATIC
		#define KERNEL_DLL __declspec(dllimport)
	#else
		#define KERNEL_DLL
	#endif
#endif

typedef void (*DLL_START_PLUGIN)();
typedef void (*DLL_STOP_PLUGIN)();
typedef vector<string> StringVector,*StringVectorPtr;

#define PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void);

#define PROPERTY_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& Get##funName(void);

#define PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void);\
public: virtual void set##funName(varType var);

#define PROPERTY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void);\
public: virtual void set##funName(const varType& var);

#define SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }

#define STATIC_READONLY(varType, varName, funName)\
protected: static varType varName;\
public: inline static varType Get##funName(void) { return varName; }

#define INLINE_STATIC_READONLY(varType, varName, funName)\
protected: static varType varName;\
public: inline varType Get##funName(void) { return varName; }

#define INLINE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }

#define INLINE_CONST_READONLY(varType, varName, funName)\
protected: varType varName;\
public: inline const varType Get##funName(void) const { return varName; }

#define INLINE_READSET(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& Get##funName(void) const { return varName; }

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& Get##funName(void) const { return varName; }\
public: virtual void Set##funName(const varType& var){ varName = var; }

#define SYNTHESIZE_RETAIN(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var)   \
{ \
    CC_SAFE_RETAIN(var); \
    CC_SAFE_RELEASE(varName); \
    varName = var; \
}

#define SafeDelete(pObject)\
do \
{\
	if (0 != pObject)\
	{\
		delete pObject;\
		pObject = 0;\
	}\
} while (false)

#define SafeDeleteArray(pObject)\
do \
{\
	if (0 != pObject)\
	{\
		delete [] pObject;\
		pObject = 0;\
	}\
} while (false)

#define BEGIN_KERNEL namespace GameKernel{
#define END_KERNEL }

typedef enum
{
	CON_NONE = 0,
	CON_INI,
	CON_XML
}ConfigType;

#endif