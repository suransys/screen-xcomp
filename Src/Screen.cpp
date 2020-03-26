/* $Header: svn://svn.omnis.net/branches/Studio10.1/Studio/EXTCOMP/GENERIC/GENERIC.CPP 2785 2012-12-13 12:04:13Z bmitchell $ */
#include <extcomp.he>
#include <extfval.he>
#include <hwnd.he>
#include <gdi.he>
#include "Screen.he"
#include <vector>

// Screen is a framework you can use to develop OMNIS external components.
// It does not support any extra calls. See other Screen samples for extra support,
// such as properties, functions, events etc.
//
// When this Screen object is added to a window in window design mode, it will have
// only standard properties that apply to all window objects. e.g. left,top etc.

// Your Screen object constructor



const qlong screensFunctionId = 1;
const qlong dockFunctionId = 2;
const qlong currentScreensFunctionId = 3;
const qlong screenObjectId = 4;

const qlong NUMBER_OF_STATIC_METHODS = 2;
const qlong NUMBER_OF_METHODS = 1;


ECOmethodEvent screensStaticMethod[] = {
    screensFunctionId, 8000, fftList, 0, NULL, 0, 0,
    dockFunctionId,    8001, fftList, 0, NULL, 0, 0,
};

ECOmethodEvent screensMethod[] = {
    currentScreensFunctionId, 7000, fftInteger, NULL, 0,0
};

ECOobject screenObject[] = {
    screenObjectId, 7001, 0, 0
};

void staticOnScreenChanged(std::vector<Screen> screens, void* userInfo){
    ScreenObject * screenUserInfo = (ScreenObject*)userInfo;
    if (screenUserInfo){
        screenUserInfo -> onScreenChanged(screens);
    }
}

ScreenObject::ScreenObject(){
    updatingScreen = UpdatingScreen();
    currentScreens = updatingScreen.getCurrentScreens();
    updatingScreen.setScreenChangeCallback(staticOnScreenChanged, this);
    updatingScreen.screenRunLoop();
}

ScreenObject::~ScreenObject(){
    updatingScreen.removeScreenChangedCallback();
}

EXTfldval ScreenObject::staticMethodCall(qlong methodId){
    EXTfldval fval;
    switch (methodId) {
        case screensFunctionId:
            fval.setList(retrieveScreens(), qtrue);
            break;
        case dockFunctionId:
            fval.setList(retrieveDock(), qtrue);
            break;
    }
    return fval;
}

EXTfldval ScreenObject::methodCall(qlong methodId){
    EXTfldval fval;
    switch (methodId) {
        case currentScreensFunctionId:
            fval.setList(getCurrentScreens(), qtrue);
            break;
    }
    return fval;
}

EXTqlist * ScreenObject::emptyScreenList(){
    EXTqlist * staticScreenList = new EXTqlist(listVlen);
    str255 startXName = QTEXT("startX");
    staticScreenList -> addCol(1, fftInteger, 0, 10, NULL, &startXName);
    str255 startYName = QTEXT("startY");
    staticScreenList -> addCol(2, fftInteger, 0, 10, NULL, &startYName);
    str255 pixelHeightName = QTEXT("pixelHeight");
    staticScreenList -> addCol(3, fftInteger, 0, 10, NULL, &pixelHeightName);
    str255 pixelWidthName = QTEXT("pixelWidth");
    staticScreenList -> addCol(4, fftInteger, 0, 10, NULL, &pixelWidthName);
    str255 usableXName = QTEXT("usableX");
    staticScreenList -> addCol(5, fftInteger, 0, 10, NULL, &usableXName);
    str255 usableYName = QTEXT("usableY");
    staticScreenList -> addCol(6, fftInteger, 0, 10, NULL, &usableYName);
    str255 usablePixelHeightName = QTEXT("usablePixelHeight");
    staticScreenList -> addCol(7, fftInteger, 0, 10, NULL, &usablePixelHeightName);
    str255 usablePixelWidthName = QTEXT("usablePixelWidth");
    staticScreenList -> addCol(8, fftInteger, 0, 10, NULL, &usablePixelWidthName);
    str255 isMainMonitorName = QTEXT("isMainMonitor");
    staticScreenList -> addCol(9, fftBoolean, dpDefault, 10, NULL, &isMainMonitorName);
    str255 resolutionName = QTEXT("resolutionScale");
    staticScreenList -> addCol(10, fftInteger, dpDefault, 10, NULL, &resolutionName);
    
    return staticScreenList;
}

EXTqlist * ScreenObject::retrieveScreens(){
    return screenListFromVector(Screen::screenList());
}

EXTqlist * ScreenObject::getCurrentScreens(){
    return screenListFromVector(currentScreens);
}

EXTqlist * ScreenObject::screenListFromVector(std::vector<Screen> screenVector){
    EXTqlist * staticScreenList = ScreenObject::emptyScreenList();
    for (int i = 0; i < screenVector.size(); i ++){
        Screen screenData = screenVector[i];
        staticScreenList -> insertRow(i+1);
        
        EXTfldval startXVal;
        startXVal.setLong(screenData.startX);
        staticScreenList -> putColVal(i+1, 1, startXVal);
        
        EXTfldval startYVal;
        startYVal.setLong(screenData.startY);
        staticScreenList -> putColVal(i+1, 2, startYVal);
        
        EXTfldval pixelHeightVal;
        pixelHeightVal.setLong(screenData.pixelHeight);
        staticScreenList -> putColVal(i+1, 3, pixelHeightVal);
        
        EXTfldval pixelWidthVal;
        pixelWidthVal.setLong(screenData.pixelWidth);
        staticScreenList -> putColVal(i+1, 4, pixelWidthVal);
        
        EXTfldval usableXVal;
        usableXVal.setLong(screenData.usableX);
        staticScreenList -> putColVal(i+1, 5, usableXVal);
        
        EXTfldval usableYVal;
        usableYVal.setLong(screenData.usableY);
        staticScreenList -> putColVal(i+1, 6, usableYVal);
        
        EXTfldval usablePixelHeightVal;
        usablePixelHeightVal.setLong(screenData.usablePixelHeight);
        staticScreenList -> putColVal(i+1, 7, usablePixelHeightVal);
        
        EXTfldval usablePixelWidthVal;
        usablePixelWidthVal.setLong(screenData.usablePixelWidth);
        staticScreenList -> putColVal(i+1, 8, usablePixelWidthVal);
        
        EXTfldval isMainMonitorVal;
        isMainMonitorVal.setBool(screenData.isMainMonitor ? 2 : 1);
        staticScreenList -> putColVal(i+1, 9, isMainMonitorVal);
        
        EXTfldval resolutionScaleVal;
        resolutionScaleVal.setLong(screenData.resolutionMultiplier);
        staticScreenList -> putColVal(i+1, 10, resolutionScaleVal);
    }
    return staticScreenList;
}

EXTqlist * ScreenObject::emptyDockList(){
    EXTqlist * dockList = new EXTqlist(listVlen);
    str255 positionName = QTEXT("position");
    dockList -> addCol(1, fftInteger, 0, 10, NULL, &positionName);
    
    str255 heightName = QTEXT("height");
    dockList -> addCol(2, fftInteger, 0, 10, NULL, &heightName);
    
    return dockList;
}

EXTqlist *ScreenObject::retrieveDock(){
    EXTqlist * dockList = ScreenObject::emptyDockList();
    int dockPosition = Screen::dockPosition();
    if (dockPosition != -1 && dockPosition != 0 && dockPosition != 1) return NULL;
    std::vector<Screen> screenVector = Screen::screenList();
    int dockHeight = 0;
    for (int i = 0; i < screenVector.size(); i ++){
        Screen screenData = screenVector[i];
        if (dockPosition == 0){
            int remainingHeight = screenData.pixelHeight - ABS(screenData.usableY - screenData.startY) - screenData.usablePixelHeight;
            if (remainingHeight > 0){
                dockHeight = remainingHeight;
                break;
            }
        }
        int remainingHeight = screenData.pixelWidth - screenData.usablePixelWidth;
        if (remainingHeight > 0){
            dockHeight = remainingHeight;
        }
    }
    dockList -> insertRow();
    
    EXTfldval positionVal;
    positionVal.setLong(dockPosition);
    dockList -> putColVal(1, 1, positionVal);
    
    EXTfldval heightVal;
    heightVal.setLong(dockHeight);
    dockList -> putColVal(1, 2, heightVal);
    
    return dockList;
}

void ScreenObject::onScreenChanged(std::vector<Screen> screens){
    currentScreens = screens;
}


// Component library entry point (name as declared in resource 31000 )
extern "C" LRESULT OMNISWNDPROC ScreenWndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam, EXTCompInfo* eci)
{
    // Initialize callback tables - THIS MUST BE DONE
    ECOsetupCallbacks(hwnd, eci);
    switch (Msg)
    {

        // ECM_CONNECT - this message is sent once per OMNIS session and should not be confused
        // with ECM_OBJCONSTRUCT which is sent once per object. ECM_CONNECT can be used if load other libraries
        // once or other general global actions that need to be done only once.
        //
        // For most components this can be removed - see other BLYTH component examples
        case ECM_CONNECT:
        {
            return EXT_FLAG_LOADED|EXT_FLAG_ALWAYS_USABLE|EXT_FLAG_NVOBJECTS; // Return external flags
        }
        case ECM_OBJCONSTRUCT:{
            ScreenObject * screenObject = new ScreenObject();
            ECOinsertObject(eci, hwnd, (void*)screenObject);
            return qtrue;
        }
        case ECM_OBJDESTRUCT:{
            ScreenObject * screenObject = (ScreenObject*)ECOremoveObject( eci, hwnd );
            if (screenObject){
                delete screenObject;
            }
            return qtrue;
        }

        // ECM_DISCONNECT - this message is sent only once when the OMNIS session is ending and should not be confused
        // with ECM_OBJDESTRUCT which is sent once per object. ECM_DISCONNECT can be used to free other libraries
        // loaded on ECM_CONNECT or other general global actions that need to be done only once.
        //
        // For most components this can be removed - see other BLYTH component examples
        case ECM_DISCONNECT:
        {
            return qtrue;
        }

        // ECM_GETCOMPLIBINFO - this is sent by OMNIS to find out the name of the library, and
        // the number of components this library supports
        case ECM_GETCOMPLIBINFO:
        {
            return ECOreturnCompInfo( gInstLib, eci, LIB_RES_NAME, OBJECT_COUNT );
        }

        // ECM_GETCOMPICON - this is sent by OMNIS to get an icon for the OMNIS component store and
        // external component browser. You need to always supply an icon in your resource file.
        case ECM_GETCOMPICON:
        {
        // OMNIS will call you once per component for an icon.
        // GENERIC_ICON is defined in the header and included in the resource file
            if ( eci->mCompId==OBJECT_ID1 ) return ECOreturnIcon( gInstLib, eci, GENERIC_ICON );
            return qfalse;
        }
        case ECM_GETSTATICOBJECT:{
            return ECOreturnMethods(gInstLib, eci, &screensStaticMethod[0], NUMBER_OF_STATIC_METHODS);
        }
        case ECM_GETMETHODNAME:{
            return ECOreturnMethods(gInstLib, eci, &screensMethod[0], NUMBER_OF_METHODS);
        }
        case ECM_GETOBJECT:{
            return ECOreturnObjects(gInstLib, eci, &screenObject[0], OBJECT_COUNT);
        }
//        case ECM_GETMETHODNAME:
//            return ECOreturnMethods(gInstLib, eci, &screensFunction[0], NUMBER_OF_METHODS);
        case ECM_METHODCALL:{
            ScreenObject * object = (ScreenObject*)ECOfindObject(eci, hwnd);
            if (!object) {
                EXTfldval fval = ScreenObject::staticMethodCall(ECOgetId(eci));
                ECOaddParam(eci,&fval);
                return 1L;
            }
            EXTfldval fval = object -> methodCall(ECOgetId(eci));
            ECOaddParam(eci, &fval);
            return 1L;
        }
    }

    // As a final result this must ALWAYS be called. It handles all other messages that this component
    // decides to ignore.
    return WNDdefWindowProc(hwnd,Msg,wParam,lParam,eci);
}

    
