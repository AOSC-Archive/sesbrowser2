#include "sesbrowser.h"

JSClassRef SESdotJS::SES_ClassCreate(JSContextRef ctx)
{
	JSStaticFunction SESStaticFunctions[] = {
		{ "show", SES_Show, kJSPropertyAttributeNone | kJSPropertyAttributeDontDelete },
		{ "print", SES_Print, kJSPropertyAttributeNone | kJSPropertyAttributeDontDelete },
	{ 0, 0, 0 }};

	JSClassDefinition classdef = {//kJSClassDefinitionEmpty;
		0,	//version
		kJSClassAttributeNone,	//attributes
		"SES",
		0,	//parent class
		0,	//staticValues
		SESStaticFunctions,	//function
		SES_Initialize,//SES_Initialize,
		SES_Finalize,//SES_Finalize,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};

	return JSClassCreate(&classdef);
}

void SESdotJS::SES_Initialize(JSContextRef ctx, JSObjectRef object)
{
}

void SESdotJS::SES_Finalize(JSObjectRef object)
{
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
	
	printf("%s\n", utf8);
	
	return JSValueMakeNumber(ctx, size);
}

SESdotJS::SESdotJS (JSGlobalContextRef ctx)
{
	printf ("	Initing SES.JS\n");	
	
	/*JSStringRef name = JSStringCreateWithUTF8CString("SES");
	JSObjectRef obj = JSObjectMake (ctx, this->SES_ClassCreate(ctx), NULL);
	JSObjectSetProperty (ctx, JSContextGetGlobalObject(ctx), name, obj, kJSPropertyAttributeNone, NULL);*/
	JSObjectRef globalObj = JSContextGetGlobalObject(ctx);
	JSClassRef cls = SES_ClassCreate(ctx);
	JSObjectRef jsObj = JSObjectMake(ctx, cls, NULL);
	JSStringRef name = JSStringCreateWithUTF8CString("SES");
	JSObjectSetProperty (ctx, globalObj, name, jsObj, kJSClassAttributeNone | kJSPropertyAttributeDontDelete, 0);
}
