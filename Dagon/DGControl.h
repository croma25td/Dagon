////////////////////////////////////////////////////////////
//
// DAGON - An Adventure Game Engine
// Copyright (c) 2011 Senscape s.r.l.
// All rights reserved.
//
// NOTICE: Senscape permits you to use, modify, and
// distribute this file in accordance with the terms of the
// license agreement accompanying it.
//
////////////////////////////////////////////////////////////

#ifndef DG_CONTROL_H
#define DG_CONTROL_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "DGPlatform.h"

////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////

#define DGInfoMargin 5
#define DGMaxHotKeys 12

class DGCamera;
class DGConfig;
class DGFont;
class DGFeedManager;
class DGFontManager;
class DGLog;
class DGNode;
class DGRoom;
class DGRender;
class DGScript;
class DGState;
class DGSystem;
class DGTextureManager;
class DGTimerManager;

enum DGEvents {
	DGEventEnterNode = 1,
	DGEventLeaveNode,
	DGEventEnterRoom,
	DGEventLeaveRoom,
	DGEventPreRender,
	DGEventPostRender,
	DGEventMouseButton,	
	DGEventMouseMove	
};

typedef struct {
	bool hasEnterNode;
    int	enterNode;
	bool hasLeaveNode;
	int	leaveNode;
	bool hasEnterRoom;
    int	enterRoom;
	bool hasLeaveRoom;
	int	leaveRoom;
	bool hasPreRender;
    int	preRender;
	bool hasPostRender;
	int	postRender;
	bool hasMouseMove;
    int	mouseMove;
	bool hasMouseButton;
	int	mouseButton;	
} DGEventsLuaFunctions;

typedef struct {
	bool enabled;
	int value;
	char line[DGMaxLogLength];
} DGHotKeyData;

typedef struct {
	int x;
	int y;
    int color;
	bool onSpot;
} DGMouseData;

////////////////////////////////////////////////////////////
// Interface - Singleton class
////////////////////////////////////////////////////////////

class DGControl {
    DGConfig* config;
    DGFeedManager* feedManager;
    DGFontManager* fontManager;    
    DGLog* log;
    DGScript* script;
    DGSystem* system;
    DGTimerManager* timerManager;
    
    std::vector<DGRoom*> _arrayOfRooms;
    DGRoom* _currentRoom;
    
    DGCamera* _camera;
    DGFont* _consoleFont;
    DGRender* _render;
    DGState* _state;
    DGTextureManager* _textureManager;
    
    DGEventsLuaFunctions _eventsLuaFunctions;
    DGHotKeyData _hotKeyData[DGMaxHotKeys];
    DGMouseData _mouseData;
    
    // This boolean helps to simplify our lengthy update cycle
    bool _canDrawSpots;
    int _fpsCount;
    int _fpsLastCount;
    bool _isInitialized;
    
    void _drawScene();
    void _scanSpots();
    
    // Private constructor/destructor
    DGControl();
    ~DGControl();
    // Stop the compiler generating methods of copy the object
    DGControl(DGControl const& copy);            // Not implemented
    DGControl& operator=(DGControl const& copy); // Not implemented
    
public:
    static DGControl& getInstance() {
        // The only instance
        // Guaranteed to be lazy initialized
        // Guaranteed that it will be destroyed correctly
        static DGControl instance;
        return instance;
    }
    
    void init();
    DGNode* currentNode();
    DGRoom* currentRoom();
    void processKey(int aKey, bool isModified);
    void processMouse(int x, int y, bool isButtonPressed);
    void registerGlobalHandler(int forEvent, int handlerForLua);
    void registerHotKey(int aKey, const char* luaCommandToExecute);
    void registerObject(DGObject* theTarget);    
    void reshape(int width, int height);
    void sleep(int forMilliseconds);
    // TODO: Add an explicit switchToNode() method
    void switchTo(DGObject* theTarget); 
    void takeSnapshot();
    
    // These methods are called asynchronously
    void profiler();
    void update();
};

#endif // DG_CONTROL_H
