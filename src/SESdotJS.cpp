#include "sesbrowser.h"

void SESdotJS::SES_Initialize(JSContextRef ctx, JSObjectRef object)
{
	printf ("	Initing SES.JS, \n");	
}

void SESdotJS::SES_Finalize(JSObjectRef object)
{
	printf ("	Stopping SES.JS\n");
}

JSValueRef SESdotJS::SES_GetVerbose(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef *exception)
{
	// verbose is false
	return JSValueMakeBoolean(ctx, false);
}

JSValueRef SESdotJS::SES_GetVersion(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef *exception)
{
	// verbose is false
	static JSStringRef version = NULL;
	if (version == NULL)
	{
		version = JSStringCreateWithUTF8CString("0.1");
	}
	printf ("	SESJs Version: %s\n", "0.1");
	return JSValueMakeString(ctx, version);
}

JSValueRef SESdotJS::SES_Show(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	JSStringRef str = JSValueToStringCopy(ctx, arguments[0], exception);
	size_t size = JSStringGetMaximumUTF8CStringSize(str);
	char* utf8 = (char*) malloc(sizeof(char) * size);
	
	JSStringGetUTF8CString(str, utf8, size);
	
	GtkWidget *dia = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, utf8);

	gtk_dialog_run((GtkDialog*) dia);
	
	gtk_widget_destroy(dia);

	return JSValueMakeNumber(ctx, size);
}

JSValueRef SESdotJS::SES_Print(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)
{
	JSStringRef str = JSValueToStringCopy(ctx, arguments[0], exception);
	size_t size = JSStringGetMaximumUTF8CStringSize(str);
	char* utf8 = (char*) malloc(sizeof(char) * size);
	
	JSStringGetUTF8CString(str, utf8, size);
	
	printf("%s", utf8);
	
	return JSValueMakeNumber(ctx, size);
}

JSClassRef SESdotJS::SES_ClassCreate(JSContextRef ctx)
{
	const JSStaticFunction SESStaticFunctions[] = {
		{ "show", SES_Show, kJSPropertyAttributeNone | kJSPropertyAttributeDontDelete },
		{ "print", SES_Print, kJSPropertyAttributeNone | kJSPropertyAttributeDontDelete },
	{ 0, 0, 0 }};

	JSStaticValue StaticValues[] = {
	{ "Version", SES_GetVersion, NULL, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
	{ "Verbose", SES_GetVerbose, NULL, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
	{ NULL, 0, 0, 0}};

	JSClassDefinition classdef;
	classdef.version = 0;
	classdef.attributes = kJSClassAttributeNone;
	classdef.className = "SES";
	classdef.staticValues = StaticValues;
	classdef.staticFunctions = SESStaticFunctions;
	classdef.initialize = SES_Initialize;
	classdef.finalize = SES_Finalize;

	return JSClassCreate(&classdef);
}

SESdotJS::SESdotJS (JSGlobalContextRef ctx)
{
	JSObjectRef globalObj = JSContextGetGlobalObject(ctx);
	JSClassRef cls = this->SES_ClassCreate(ctx);
	JSObjectRef jsObj = JSObjectMake(ctx, cls, NULL);
	JSStringRef name = JSStringCreateWithUTF8CString("SES");
	JSObjectSetProperty (ctx, globalObj, name, jsObj, kJSClassAttributeNone | kJSPropertyAttributeDontDelete, 0);
}
