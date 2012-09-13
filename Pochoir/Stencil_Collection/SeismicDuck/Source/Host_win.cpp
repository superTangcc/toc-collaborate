//******************************************************************************
// OS dependent portion of Seismic Duck
//
// Copyright 1996-2010 Arch D. Robison
//******************************************************************************

#define WIN32_LEAN_AND_MEAN

#undef UNICODE

#define _WIN32_WINNT 0x400 /* Necessary to get WM_MOUSELEAVE */

#define HAVE_SOUND 0

#include <windows.h>    // Include important windows stuff
#include <windowsx.h>
#include <d3d9.h>  	    // DirectX 9 includes
#include <CommDlg.h>    // Common dialogs
#include <Ole2.h>
#include <gdiplus.h>
#include <stdio.h>
#include <cassert>
#include "resource.h"
#include "AssertLib.h"
#include "TraceLib.h"
#include "Host.h"
#include "NimbleDraw.h"
#include "BuiltFromResource.h"
#include "Game.h"
#include "Config.h"
#if HAVE_SOUND
#include "SimpleSound.h"
#endif /* HAVE_SOUND */

#define WINDOW_CLASS_NAME "WINXCLASS"   // Class name

//! True iff running in exclusive screen mode
/** Use ExclusiveMode=false for interactive debugging. */

#ifdef EXCLUSIVE_MODE
const bool ExclusiveMode = EXCLUSIVE_MODE;
#elif ASSERTIONS
const bool ExclusiveMode = false;
#else
const bool ExclusiveMode = true;
#endif

static int DisplayWidth;
static int DisplayHeight;
static short WindowWidth = ExclusiveMode ? 1024 : 1024;
static short WindowHeight = ExclusiveMode ? 768 : 768;

//! Set to true between time that a WM_SIZE message is received and GameResizeOrMove is called.
static bool ResizeOrMove = false;	

#if CREATE_LOG
FILE* LogFile;
#endif /* CREATE_LOG */

//! Handle for main window
static HWND MainWindowHandle;	
static HINSTANCE MainHinstance;

// The DirectDraw object from which the device is created.
static IDirect3D9* d3d = NULL;

// Device upon which to draw
static IDirect3DDevice9* Device = NULL;

//! Return the greater of i rounded to a multiple of four or 128;
/** Rounds down in the case of a number that is of the form 4k+2 */
static int RoundAndClip( int i ) {
    int j = (i+1)>>2<<2;
    if( j<128 ) j=128;
	return j;
}

static const char* Decode( HRESULT hr ) {
	switch( hr ) {
		case D3DERR_DEVICELOST:
			return "D3DERR_DEVICELOST";
		case D3DERR_INVALIDCALL:
			return "D3DERR_INVALIDCALL";
		case D3DERR_NOTAVAILABLE:
			return "D3DERR_NOTAVAILABLE";
		case D3DERR_OUTOFVIDEOMEMORY:
			return "D3DERR_OUTOFVIDEOMEMORY";
		default:
			return "<unknown>";
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, 
						    UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam);		// Prototype shuts up warnings

void HostExit() {
    PostMessage(MainWindowHandle, WM_DESTROY,0,0);
}

static bool RequestedTrackMouseEvent = false;

LRESULT CALLBACK WindowProc(HWND hwnd,
						    UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{                       
    // this is the main message handler of the system
    PAINTSTRUCT	ps;		   // used in WM_PAINT
    HDC			hdc;	   // handle to a device context

    // what is the message
    switch(msg) {
        case WM_LBUTTONDOWN:
		case WM_LBUTTONUP: {
			NimblePoint p;
 	        p.x = (int)LOWORD(lparam);
		    p.y = (int)HIWORD(lparam);
	    	if( msg==WM_LBUTTONDOWN )
                GameMouseButtonDown( p, 0 );
            else
                GameMouseButtonUp( p, 0 );
            break;
		}
        case WM_MOUSELEAVE:
            RequestedTrackMouseEvent = false;
            HostShowCursor(true);
            break;

		case WM_MOUSEMOVE: {

            if (!RequestedTrackMouseEvent) {
                // First time mouse entered my window:
                // Request leave notification
                TRACKMOUSEEVENT tme;
                tme.cbSize = sizeof(tme);
                tme.hwndTrack = hwnd;
                tme.dwFlags = TME_LEAVE;
                TrackMouseEvent(&tme);
                RequestedTrackMouseEvent = true;
            }

	        NimblePoint p;
			p.x = (int)LOWORD(lparam);
		    p.y = (int)HIWORD(lparam);
	    	GameMouseMove( p );
            break;
		}
	    case WM_CREATE:
		    // Do initialization stuff here
		    return 0;

        case WM_PAINT:
            // Start painting
            hdc = BeginPaint(hwnd,&ps);

            // End painting
            EndPaint(hwnd,&ps);
            return 0;
        
        case WM_MOVE:
    	    return 0;
    	
	    case WM_SIZE:
		    // Extract new window size
		    // Round to multiple of four, because some of our loop unrollings depend upon such.
		    WindowWidth = RoundAndClip(LOWORD(lparam));
		    WindowHeight = HIWORD(lparam);
		    ResizeOrMove = true;
		    return 0;
		
	    case WM_COMMAND:
		    break;

	    case WM_DESTROY:
		    // Kill the application
		    PostQuitMessage(0);
	    	return 0;

		case WM_CHAR: {
 			if( GameKeyDown(wparam) )
				PostMessage(hwnd, WM_DESTROY,0,0);
			return 0;
		}
    	default:
            break;

    } // end switch

    // Process any messages that we didn't take care of
    return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc

static void ProductionAssert( bool predicate, const char * msg ) {
	if( !predicate ) {
		char* lpMsgBuf;
		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(char*)&lpMsgBuf,
			0,
			NULL
			);
		// Display the string.
		MessageBoxA( NULL, msg, lpMsgBuf, MB_OK | MB_ICONINFORMATION );
		// Free the buffer.
		LocalFree( lpMsgBuf );
		exit(1);
	}
}

class HostResourceLoader {
public:
	static void loadResourceBitmaps(HINSTANCE hInstance);
private:
    //! Load given item from a resource of type PNG
    static void loadFromPNG( BuiltFromResourcePixMap& item );
};

void HostResourceLoader::loadFromPNG( BuiltFromResourcePixMap& item ) {
    HRSRC x = ::FindResourceA(  NULL, item.resourceName, "PNG" );
    ProductionAssert(x,item.resourceName);
    DWORD n = SizeofResource( NULL, x); 
    Assert(n);
    HGLOBAL g = ::LoadResource( NULL, x );
    Assert(g);
    const void* r=LockResource(g);
    Assert(r!=NULL);
    HGLOBAL buf = ::GlobalAlloc(GMEM_MOVEABLE, n);
    Assert(buf);
    char* png = (char*)::GlobalLock(buf);
    Assert(png);
    memcpy(png,r,n);
    // Following assertion check that it is a PNG resource.
    Assert(memcmp(png+1,"PNG",3)==0 );
    IStream* s = NULL;
    HRESULT streamCreationStatus = CreateStreamOnHGlobal(buf,FALSE,&s);
    Assert( streamCreationStatus==S_OK );
    Assert(s);
    Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromStream(s,FALSE);
    ProductionAssert(bitmap,"Gdiplus::Bitmap::FromStream returned false");
    Gdiplus::Status fromStreamStatus = bitmap->GetLastStatus();
    ProductionAssert(fromStreamStatus==Gdiplus::Ok,"Gdiplus::Bitmap::FromStream failed");
    s->Release();
    ::GlobalUnlock(buf);
    ::GlobalFree(buf);

    int w=bitmap->GetWidth();
    int h=bitmap->GetHeight();
    const Gdiplus::Rect rect(0,0,w,h);
    Gdiplus::BitmapData lockedBits;
    Gdiplus::Status lockStatus = bitmap->LockBits(&rect,0,PixelFormat32bppARGB,&lockedBits);
	Assert( lockStatus==Gdiplus::Ok);
    NimblePixMap map(w,h,8*sizeof(NimblePixel),lockedBits.Scan0,lockedBits.Stride);
    item.buildFrom(map);
	Gdiplus::Status unlockStatus = bitmap->UnlockBits(&lockedBits);
	delete bitmap;
	Assert(unlockStatus==Gdiplus::Ok);
    return;
}

void HostResourceLoader::loadResourceBitmaps(HINSTANCE hInstance) {
	ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    for( BuiltFromResourcePixMap* p = BuiltFromResourcePixMap::theRoot; p; p=p->next ) {
        loadFromPNG(*p);
    }
    Gdiplus::GdiplusShutdown(gdiplusToken);
}

// Borland floating point initialization
#include <math.h>
#include <float.h>

void initfp(void)
{
    // disable floating point exceptions
    _control87(MCW_EM,MCW_EM);
}

extern "C" int _matherr(struct _exception  *)
{
    return 1;
}

double HostClockTime() {
    LARGE_INTEGER count, freq;
	BOOL status = QueryPerformanceCounter(&count);    
	status = QueryPerformanceFrequency(&freq);     
    return double(count.QuadPart)/double(freq.QuadPart); 
}

double HostSleepUntil( double absoluteTime ) {  
	for(;;) {
		double t1 = HostClockTime();
		if( t1>=absoluteTime ) return t1;
		DWORD remainder = (absoluteTime-t1)*1000;
		// For very short waits, calling Sleep is risky because it may sleep too long.
		// So call Sleep only if wait is relatively long.
		// The value of 16 corresponds to 1/60th of a second, and was found experimentally.
		const int tiny = 16;
		if( remainder>=tiny ) 
		    Sleep( remainder-tiny );
	}
}

bool HostIsKeyDown( int key ) {
	switch( key ) {
		case HOST_KEY_LEFT:  key=VK_LEFT;  break;
		case HOST_KEY_RIGHT: key=VK_RIGHT; break;
		case HOST_KEY_UP:    key=VK_UP;    break;
		case HOST_KEY_DOWN:  key=VK_DOWN;  break;
	}
	return GetKeyState(key)<0;
}

static void SetPresentParameters( D3DPRESENT_PARAMETERS& present ) {
	ZeroMemory( &present, sizeof(D3DPRESENT_PARAMETERS) );
    present.BackBufferCount           = 2;
    present.SwapEffect                = D3DSWAPEFFECT_DISCARD;
    present.BackBufferFormat          = D3DFMT_X8R8G8B8;
	present.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
    present.Windowed                  = !ExclusiveMode;
#if 0
	present.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
#endif
#if 0
	present.PresentationInterval = D3DPRESENT_INTERVAL_TWO;
#endif

	if( ExclusiveMode ) {
		present.BackBufferHeight = DisplayHeight;
		present.BackBufferWidth = DisplayWidth;
	}
}

void HostSetFrameIntervalRate( int limit ) {
    D3DPRESENT_PARAMETERS present;
	SetPresentParameters(present);
	present.PresentationInterval = limit==0 ? D3DPRESENT_INTERVAL_IMMEDIATE : 
		                           limit==1 ? D3DPRESENT_INTERVAL_DEFAULT : 
								              D3DPRESENT_INTERVAL_TWO;
	Device->Reset(&present);
}

static bool InitializeDirectX( HWND hwnd ) {
	HRESULT hr;

	// Create the Direct3D interface object.
	d3d = Direct3DCreate9( D3D_SDK_VERSION );
	Assert(d3d);

	// Get device capabilities
	D3DCAPS9 displayCaps;
    hr = d3d->GetDeviceCaps(0,D3DDEVTYPE_HAL,&displayCaps);
	Assert(hr==D3D_OK);

	// Get resolution of current display mode
	D3DDISPLAYMODE displayMode;
	hr = d3d->GetAdapterDisplayMode(0,&displayMode);
	Assert(hr==D3D_OK);
	DisplayHeight = displayMode.Height;
	DisplayWidth = displayMode.Width;
    if( DisplayHeight>DISPLAY_HEIGHT_MAX || DisplayWidth>DISPLAY_WIDTH_MAX ) {
        char buffer[200];
        sprintf(buffer,"Display is too big (%dx%d).\n"
                       "Please set your display to a 32-bit color mode no bigger than %dx%d.\n"
                       "Then restart Seismic Duck.\n",
                DisplayWidth,DisplayHeight,DISPLAY_WIDTH_MAX,DISPLAY_HEIGHT_MAX);
        MessageBoxA(hwnd,buffer,NULL,MB_OK|MB_ICONWARNING);
        return false;
    }

    if( DisplayHeight<DISPLAY_HEIGHT_MIN || DisplayWidth<DISPLAY_WIDTH_MIN ) {
        char buffer[200];
        sprintf(buffer,"Display is too small (%dx%d).\n"
                       "Please set your display to a 32-bit color mode no smaller than %dx%d.\n"
                       "Then restart Seismic Duck.\n",
                DisplayWidth,DisplayHeight,DISPLAY_WIDTH_MIN,DISPLAY_HEIGHT_MIN);
        MessageBoxA(hwnd,buffer,NULL,MB_OK|MB_ICONWARNING);
        return false;
    }


	// Create the device
	D3DPRESENT_PARAMETERS present;
    SetPresentParameters(present);
    hr = d3d->CreateDevice( 
        D3DADAPTER_DEFAULT, 
        D3DDEVTYPE_HAL, 
        hwnd, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &present,
        &Device
    );
	if ( hr!=D3D_OK  ) {
        char buffer[200];
        sprintf(buffer,"Internal error: d3d->CreateDevice returned %s\n",Decode(hr));
        MessageBoxA(hwnd,buffer,NULL,MB_OK|MB_ICONWARNING);
		return false;
	}

	return true;
}


//! Release all resources allocated to DirectX
static void ShutdownDirectX() {
	if( Device ) 
		Device->Release();
	if( d3d )
		d3d->Release();
} 

static void UpdateAndDraw( HWND hwnd ) {
    HRESULT hr;
	Device->BeginScene();
    IDirect3DSurface9* backBuffer=0;
	hr = Device->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backBuffer);
	Assert(hr==D3D_OK);
	D3DSURFACE_DESC desc;
	hr = backBuffer->GetDesc(&desc);
	Assert(hr==D3D_OK);
	D3DLOCKED_RECT lockedRect;
	hr = backBuffer->LockRect(&lockedRect,NULL,D3DLOCK_NOSYSLOCK|D3DLOCK_DISCARD);
	Assert(hr==D3D_OK);
	NimblePixMap pixmap(desc.Width,desc.Height,32,lockedRect.pBits,lockedRect.Pitch);
	if( ResizeOrMove ) {
		GameResizeOrMove( pixmap );
		ResizeOrMove = false;
	}
	GameUpdateDraw( pixmap, NimbleUpdate|NimbleDraw );
	hr = backBuffer->UnlockRect();
	Assert(hr==D3D_OK);
	backBuffer->Release();
    Device->EndScene();
    hr = Device->Present( 0, 0, 0, 0 );
	if( hr!=D3D_OK ) {
		Decode(hr);
	}
}

void HostShowCursor( bool show ) {
    static bool CursorIsVisible = true;
    if( show!=CursorIsVisible ) {
        CursorIsVisible = show;
        ShowCursor(show);
    }
}

#if HAVE_GAME_FILES

void GameOutFile::write( const void* buffer, size_t nbyte ) {
    DWORD bytesWritten;
    WriteFile( hFile, buffer, DWORD(nbyte), &bytesWritten, NULL );
    Assert( bytesWritten==nbyte );
}

static void InitializeOPENFILENAME( OPENFILENAME& ofn, char filename[MAX_PATH] ) {
    memset(&ofn,0,sizeof(OPENFILENAME));
    ofn.lStructSize=sizeof(OPENFILENAME);
    ofn.hwndOwner = MainWindowHandle;
    ofn.lpstrFile = filename;
    ofn.lpstrFile[0] = '\0';
    ofn.lpstrFilter = "All\0*.*\0EcoMunch\0*.eco\0";
    ofn.nFilterIndex = 2;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFile = MAX_PATH;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrDefExt="eco";
}

bool GameOutFile::open() {
    char filename[MAX_PATH];
    OPENFILENAME ofn;
    InitializeOPENFILENAME( ofn, filename );
    ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
    ofn.lpstrTitle = "Save As";
    if( GetSaveFileName(&ofn) ) {
        hFile = CreateFile(filename,               // File to open
                           GENERIC_WRITE,          // Open for writing
                           0,                      // Do not share
                           NULL,                   // Default security
                           CREATE_ALWAYS,          // Overwrite existing
                           FILE_ATTRIBUTE_NORMAL,  // Normal file
                           NULL);                  // No attribute template
        doAfterOpen();
        return true;
    } else {
        DWORD err = CommDlgExtendedError();
        hFile = 0;
        return false;
    }
}

void GameOutFile::close() {
    doBeforeClose();
    CloseHandle(hFile);
    hFile = 0;
}

size_t GameInFile::read( void* buffer, size_t nbyte ) {
    DWORD bytesRead;
    ReadFile( hFile, buffer, DWORD(nbyte), &bytesRead, NULL );
    return nbyte;
}

bool GameInFile::open() {
    char filename[MAX_PATH];
    OPENFILENAME ofn;
    InitializeOPENFILENAME( ofn, filename );
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.lpstrTitle = "Open File";
    if( GetOpenFileName(&ofn) ) {
        hFile = CreateFile(filename,          // File to open
                           GENERIC_READ,          // Open for reading
                           FILE_SHARE_READ,       // Share for reading
                           NULL,                  // Default security
                           OPEN_EXISTING,         // Existing file only
                           FILE_ATTRIBUTE_NORMAL, // Normal file
                           NULL);                 // No attribute template
        doAfterOpen();
        return true;
    } else {
        DWORD err = CommDlgExtendedError();
        hFile = 0;
        return false;
    }
}

void GameInFile::close() {
    doBeforeClose();
    CloseHandle(hFile);
    hFile = 0;
}
#endif /* HAVE_GAME_FILES */

#if 0
BOOL CALLBACK VanityDialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_INITDIALOG:
			return TRUE;
		case WM_DESTROY:
destroy:
           EndDialog(hDlg,0);
           return TRUE;
		case WM_COMMAND: {
			int code = wParam>>16;
			int which = wParam & 0xFFFF;
			switch( which ) {
				case 1: {
					char buffer[64];
					buffer[0]=0;
					HWND b = GetDlgItem(hDlg,501);	// FIXME - should create symbol for 501
					GetWindowTextA(b,buffer,sizeof(buffer));
					// Filter out weirdness.
					char* q=buffer;
					for( char* p=buffer; char c = *p; ++p ) {
						if( isspace(c) *q++ = ' ';
					    else if( isprint(c) ) *q++ = c;
				    }
					*p++ = '\0';
					goto destroy;
				}
				break;
			}
			break;
		}
   }
   return FALSE;
}
#endif

void HostWarning( const char* msg ) {
	MessageBoxA(MainWindowHandle,msg,"WARNING",MB_OK|MB_ICONWARNING);
}

int WINAPI WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
					LPSTR lpcmdline,
					int ncmdshow)
{
#if CREATE_LOG
	LogFile = fopen("log.txt","w");
	fprintf(LogFile,"enter WinMain\n");
	fflush(LogFile);
#endif /* CREATE_LOG */
    MainHinstance = hinstance;

    initfp();
	WNDCLASS winclass;	// this will hold the class we create
	HWND	 hwnd;		// generic window handle
	MSG		 msg;		// generic message

	// first fill in the window class stucture
	winclass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= WINDOW_CLASS_NAME;


	// Register the window class
	if (!RegisterClass(&winclass)) {
#if CREATE_LOG
		fprintf(LogFile,"cannot register class\n");
		fclose(LogFile);
#endif /* CREATE_LOG */
		return 0;
	}
	HostResourceLoader::loadResourceBitmaps(hinstance);
#if CREATE_LOG
	fprintf(LogFile,"loaded resource bitmap\n");
	fflush(LogFile);
#endif /* CREATE_LOG */
	
#if USE_HOST_MENU_SYSTEM
	MainMenuHandle = LoadMenu(hinstance,"GAMEBAR");
#endif

#if CREATE_LOG
	fprintf(LogFile,"loaded MainMenuHandle=%p GameMenuHandle=%p PracticeMenuHandle=%p\n",
		    MainMenuHandle, GameMenuHandle, PracticeMenuHandle );
	fflush(LogFile);
#endif /* CREATE_LOG */

	// Create the window, note the use of WS_POPUP
	hwnd = CreateWindow(WINDOW_CLASS_NAME, 		            // class
							  GameTitle(),	 	// title
							  WS_POPUP|(ExclusiveMode?0:WS_VISIBLE)|(ExclusiveMode?0:WS_SIZEBOX|WS_BORDER|WS_CAPTION)/*WS_OVERLAPPEDWINDOW | WS_VISIBLE*/,
						 	  0,			            // x
						 	  0,						// y
							  WindowWidth,              // width
	                          WindowHeight,             // height
							  NULL,	                    // handle to parent
							  NULL,	                    // handle to menu
							  hinstance,                // instance
							  NULL);	                // creation parms
	if( !hwnd ) {
#if CREATE_LOG
		fprintf(LogFile,"cannot create main window\n");
		fclose(LogFile);
#endif /* CREATE_LOG */
		return 0;
	}
#if CREATE_LOG
	fprintf(LogFile,"registered main window\n");
	fflush(LogFile);
#endif /* CREATE_LOG */
	srand(2);
	MainWindowHandle = hwnd;
#if USE_HOST_MENU_SYSTEM
	HostSetMenuBar(0);
	UpdateMenu();
#endif

	// Perform DirectX intialization
	if( !InitializeDirectX(hwnd) )
        return 0;

#if HAVE_SOUND
	if( !InitializeDirectSound(hwnd) ) 
		return 0;
#endif /* HAVE_SOUND */

	// Perform all game console specific initialization
	if( !GameInitialize() )
        return 0;
	
	// enter main event loop
	for(;;) {
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) { 
			// Test if this is a quit
	        if (msg.message == WM_QUIT)
	           break;
		
			// Translate any accelerator keys
			TranslateMessage(&msg);
	
			// Send the message to the window proc
			DispatchMessage(&msg);
		} // end if
	    
		// Main game processing goes here
		UpdateAndDraw(hwnd);

	} // end while
	
	// Shutdown game and release all resources
#if HAVE_SOUND
	ShutdownDirectSound();
#endif /* HAVE_SOUND */
	ShutdownDirectX();

	// Return to Windows 
	return msg.wParam;

} // end WinMain

//=================================================================

