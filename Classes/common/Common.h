//
//  Common.h
//  CrazyWord
//
//  Created by jintao on 14-8-8.
//
//

#ifndef __CrazyWord__Common__
#define __CrazyWord__Common__

#define SINGLETON(className)\
public:\
className(){};\
virtual bool init();\
public:\
static className* _shared;\
static className* shared(){\
if(!_shared) {_shared = new className();_shared->init();}\
return _shared;\
};\
void destroy() {if(_shared) {delete _shared; _shared = NULL;}};\

#define SINGLETON_IMPL(className)\
className* className::_shared = NULL;\

#define BS_SAFE_REMOVE(node)\
if (node && node->getParent()) {\
node->removeFromParentAndCleanup(true);\
node = NULL;\
}

#define BS_SET_OPACITY_ALL_CHILDREN(node, opacity) node->setOpacity(opacity);\
for (unsigned int i = 0; i < node->getChildrenCount(); i++) {\
dynamic_cast<CCSprite*>(node->getChildren()->objectAtIndex(i))->setOpacity(opacity);\
}\

#define BS_CREATE_FUNC(className)\
public:\
virtual bool init();\
static className* create();\

#define BS_CREATE_FUNC_IMPL(className)\
className* className::create() {\
className* node = new className();\
node->init();\
node->autorelease();\
return node;\
}\

#define BS_CCB_LOADER(className)\
class CCBReader;\
class className##Loader : public cocos2d::extension::CCLayerLoader\
{\
public:\
CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(className##Loader, loader);\
protected:\
CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(className);\
};\


#endif /* defined(__CrazyWord__Common__) */
