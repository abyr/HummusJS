/*
 Source File : PDFNullDriver.h
 
 
 Copyright 2013 Gal Kahana HummusJS
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 */
#include "PDFNullDriver.h"
#include "RefCountPtr.h"

using namespace v8;

Persistent<Function> PDFNullDriver::constructor;
Persistent<FunctionTemplate> PDFNullDriver::constructor_template;

void PDFNullDriver::Init()
{
    Local<FunctionTemplate> t = FunctionTemplate::New(New);
    constructor_template = Persistent<FunctionTemplate>::New(t);
    constructor_template->SetClassName(String::NewSymbol("PDFNull"));
    constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
    constructor_template->InstanceTemplate()->SetAccessor(String::NewSymbol("value"),GetValue);
    
    PDFObjectDriver::Init(constructor_template);
    
    constructor = Persistent<Function>::New(constructor_template->GetFunction());
}

Handle<Value> PDFNullDriver::NewInstance()
{
    HandleScope scope;
    
    Local<Object> instance = constructor->NewInstance();
    
    return scope.Close(instance);
}

bool PDFNullDriver::HasInstance(Handle<Value> inObject)
{
    return inObject->IsObject() &&
    constructor_template->HasInstance(inObject->ToObject());
}

Handle<Value> PDFNullDriver::New(const Arguments& args)
{
    HandleScope scope;
    
    PDFNullDriver* driver = new PDFNullDriver();
    driver->Wrap(args.This());
    return args.This();
}

PDFObject* PDFNullDriver::GetObject()
{
    return TheObject.GetPtr();
}

Handle<Value> PDFNullDriver::GetValue(Local<String> property,const AccessorInfo &info)
{
    HandleScope scope;
    return scope.Close(Undefined());
}


