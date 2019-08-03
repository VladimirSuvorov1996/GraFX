#pragma once
//This header exists for one purpose only: 
//to undef glfw preprocessor defenitions, 
//wich are ugly, just because of preprocessor global scope defs.
//
#ifdef _glfw3_h_

#undef GLFW_VERSION_MAJOR          

#undef GLFW_VERSION_MINOR     
#undef GLFW_VERSION_REVISION      
#undef GLFW_TRUE   
#undef GLFW_FALSE 
#undef GLFW_RELEASE 
#undef GLFW_PRESS
#undef GLFW_REPEAT 
#undef GLFW_KEY_UNKNOWN
#undef GLFW_KEY_SPACE              
#undef GLFW_KEY_APOSTROPHE           
#undef GLFW_KEY_COMMA            
#undef GLFW_KEY_MINUS              
#undef GLFW_KEY_PERIOD            
#undef GLFW_KEY_SLASH             
#undef GLFW_KEY_0                  
#undef GLFW_KEY_1                  
#undef GLFW_KEY_2                  
#undef GLFW_KEY_3                  
#undef GLFW_KEY_4                  
#undef GLFW_KEY_5                  
#undef GLFW_KEY_6                  
#undef GLFW_KEY_7                  
#undef GLFW_KEY_8                  
#undef GLFW_KEY_9                  
#undef GLFW_KEY_SEMICOLON            
#undef GLFW_KEY_EQUAL                
#undef GLFW_KEY_A                  
#undef GLFW_KEY_B                  
#undef GLFW_KEY_C                  
#undef GLFW_KEY_D                  
#undef GLFW_KEY_E                  
#undef GLFW_KEY_F                  
#undef GLFW_KEY_G                  
#undef GLFW_KEY_H                  
#undef GLFW_KEY_I                  
#undef GLFW_KEY_J                  
#undef GLFW_KEY_K                  
#undef GLFW_KEY_L                  
#undef GLFW_KEY_M                  
#undef GLFW_KEY_N                  
#undef GLFW_KEY_O                  
#undef GLFW_KEY_P                  
#undef GLFW_KEY_Q                  
#undef GLFW_KEY_R                  
#undef GLFW_KEY_S                  
#undef GLFW_KEY_T                  
#undef GLFW_KEY_U                  
#undef GLFW_KEY_V                  
#undef GLFW_KEY_W                  
#undef GLFW_KEY_X                  
#undef GLFW_KEY_Y                  
#undef GLFW_KEY_Z                  
#undef GLFW_KEY_LEFT_BRACKET         
#undef GLFW_KEY_BACKSLASH            
#undef GLFW_KEY_RIGHT_BRACKET        
#undef GLFW_KEY_GRAVE_ACCENT         
#undef GLFW_KEY_WORLD_1           
#undef GLFW_KEY_WORLD_2            

#undef GLFW_KEY_ESCAPE             
#undef GLFW_KEY_ENTER              
#undef GLFW_KEY_TAB                
#undef GLFW_KEY_BACKSPACE          
#undef GLFW_KEY_INSERT             
#undef GLFW_KEY_DELETE             
#undef GLFW_KEY_RIGHT              
#undef GLFW_KEY_LEFT               
#undef GLFW_KEY_DOWN               
#undef GLFW_KEY_UP                 
#undef GLFW_KEY_PAGE_UP            
#undef GLFW_KEY_PAGE_DOWN          
#undef GLFW_KEY_HOME               
#undef GLFW_KEY_END                
#undef GLFW_KEY_CAPS_LOCK          
#undef GLFW_KEY_SCROLL_LOCK        
#undef GLFW_KEY_NUM_LOCK           
#undef GLFW_KEY_PRINT_SCREEN       
#undef GLFW_KEY_PAUSE              
#undef GLFW_KEY_F1                 
#undef GLFW_KEY_F2                 
#undef GLFW_KEY_F3                 
#undef GLFW_KEY_F4                 
#undef GLFW_KEY_F5                 
#undef GLFW_KEY_F6                 
#undef GLFW_KEY_F7                 
#undef GLFW_KEY_F8                 
#undef GLFW_KEY_F9                 
#undef GLFW_KEY_F10                
#undef GLFW_KEY_F11                
#undef GLFW_KEY_F12                
#undef GLFW_KEY_F13                
#undef GLFW_KEY_F14                
#undef GLFW_KEY_F15                
#undef GLFW_KEY_F16                
#undef GLFW_KEY_F17                
#undef GLFW_KEY_F18                
#undef GLFW_KEY_F19                
#undef GLFW_KEY_F20                
#undef GLFW_KEY_F21                
#undef GLFW_KEY_F22                
#undef GLFW_KEY_F23                
#undef GLFW_KEY_F24                
#undef GLFW_KEY_F25                
#undef GLFW_KEY_KP_0               
#undef GLFW_KEY_KP_1               
#undef GLFW_KEY_KP_2               
#undef GLFW_KEY_KP_3               
#undef GLFW_KEY_KP_4               
#undef GLFW_KEY_KP_5               
#undef GLFW_KEY_KP_6               
#undef GLFW_KEY_KP_7               
#undef GLFW_KEY_KP_8               
#undef GLFW_KEY_KP_9               
#undef GLFW_KEY_KP_DECIMAL         
#undef GLFW_KEY_KP_DIVIDE          
#undef GLFW_KEY_KP_MULTIPLY        
#undef GLFW_KEY_KP_SUBTRACT        
#undef GLFW_KEY_KP_ADD             
#undef GLFW_KEY_KP_ENTER           
#undef GLFW_KEY_KP_EQUAL           
#undef GLFW_KEY_LEFT_SHIFT         
#undef GLFW_KEY_LEFT_CONTROL       
#undef GLFW_KEY_LEFT_ALT           
#undef GLFW_KEY_LEFT_SUPER         
#undef GLFW_KEY_RIGHT_SHIFT        
#undef GLFW_KEY_RIGHT_CONTROL      
#undef GLFW_KEY_RIGHT_ALT          
#undef GLFW_KEY_RIGHT_SUPER        
#undef GLFW_KEY_MENU               

#undef GLFW_KEY_LAST               


#undef GLFW_MOD_SHIFT 
#undef GLFW_MOD_CONTROL  
#undef GLFW_MOD_ALT    
#undef GLFW_MOD_SUPER  

#undef GLFW_MOUSE_BUTTON_1         
#undef GLFW_MOUSE_BUTTON_2         
#undef GLFW_MOUSE_BUTTON_3         
#undef GLFW_MOUSE_BUTTON_4         
#undef GLFW_MOUSE_BUTTON_5         
#undef GLFW_MOUSE_BUTTON_6         
#undef GLFW_MOUSE_BUTTON_7         
#undef GLFW_MOUSE_BUTTON_8         
#undef GLFW_MOUSE_BUTTON_LAST      
#undef GLFW_MOUSE_BUTTON_LEFT      
#undef GLFW_MOUSE_BUTTON_RIGHT     
#undef GLFW_MOUSE_BUTTON_MIDDLE    

#undef GLFW_JOYSTICK_1             
#undef GLFW_JOYSTICK_2             
#undef GLFW_JOYSTICK_3             
#undef GLFW_JOYSTICK_4             
#undef GLFW_JOYSTICK_5             
#undef GLFW_JOYSTICK_6             
#undef GLFW_JOYSTICK_7             
#undef GLFW_JOYSTICK_8             
#undef GLFW_JOYSTICK_9             
#undef GLFW_JOYSTICK_10            
#undef GLFW_JOYSTICK_11            
#undef GLFW_JOYSTICK_12            
#undef GLFW_JOYSTICK_13            
#undef GLFW_JOYSTICK_14            
#undef GLFW_JOYSTICK_15            
#undef GLFW_JOYSTICK_16            
#undef GLFW_JOYSTICK_LAST          

#undef GLFW_NOT_INITIALIZED        
#undef GLFW_NO_CURRENT_CONTEXT     
#undef GLFW_INVALID_ENUM           
#undef GLFW_INVALID_VALUE          
#undef GLFW_OUT_OF_MEMORY          
#undef GLFW_API_UNAVAILABLE        
#undef GLFW_VERSION_UNAVAILABLE    
#undef GLFW_PLATFORM_ERROR         
#undef GLFW_FORMAT_UNAVAILABLE     
#undef GLFW_NO_WINDOW_CONTEXT      


#undef GLFW_FOCUSED                
#undef GLFW_ICONIFIED              
#undef GLFW_RESIZABLE              
#undef GLFW_VISIBLE                
#undef GLFW_DECORATED              
#undef GLFW_AUTO_ICONIFY           
#undef GLFW_FLOATING               
#undef GLFW_MAXIMIZED              

#undef GLFW_RED_BITS               
#undef GLFW_GREEN_BITS             
#undef GLFW_BLUE_BITS              
#undef GLFW_ALPHA_BITS             
#undef GLFW_DEPTH_BITS             
#undef GLFW_STENCIL_BITS           
#undef GLFW_ACCUM_RED_BITS         
#undef GLFW_ACCUM_GREEN_BITS       
#undef GLFW_ACCUM_BLUE_BITS        
#undef GLFW_ACCUM_ALPHA_BITS       
#undef GLFW_AUX_BUFFERS            
#undef GLFW_STEREO                 
#undef GLFW_SAMPLES                
#undef GLFW_SRGB_CAPABLE           
#undef GLFW_REFRESH_RATE           
#undef GLFW_DOUBLEBUFFER           

#undef GLFW_CLIENT_API             
#undef GLFW_CONTEXT_VERSION_MAJOR  
#undef GLFW_CONTEXT_VERSION_MINOR  
#undef GLFW_CONTEXT_REVISION       
#undef GLFW_CONTEXT_ROBUSTNESS     
#undef GLFW_OPENGL_FORWARD_COMPAT  
#undef GLFW_OPENGL_DEBUG_CONTEXT   
#undef GLFW_OPENGL_PROFILE         
#undef GLFW_CONTEXT_RELEASE_BEHAVIOR 
#undef GLFW_CONTEXT_NO_ERROR       
#undef GLFW_CONTEXT_CREATION_API   

#undef GLFW_NO_API                          
#undef GLFW_OPENGL_API             
#undef GLFW_OPENGL_ES_API          

#undef GLFW_NO_ROBUSTNESS                   
#undef GLFW_NO_RESET_NOTIFICATION  
#undef GLFW_LOSE_CONTEXT_ON_RESET  

#undef GLFW_OPENGL_ANY_PROFILE              
#undef GLFW_OPENGL_CORE_PROFILE    
#undef GLFW_OPENGL_COMPAT_PROFILE  

#undef GLFW_CURSOR                 
#undef GLFW_STICKY_KEYS            
#undef GLFW_STICKY_MOUSE_BUTTONS

#undef GLFW_CURSOR_NORMAL          
#undef GLFW_CURSOR_HIDDEN          
#undef GLFW_CURSOR_DISABLED        

#undef GLFW_ANY_RELEASE_BEHAVIOR            
#undef GLFW_RELEASE_BEHAVIOR_FLUSH 
#undef GLFW_RELEASE_BEHAVIOR_NONE  

#undef GLFW_NATIVE_CONTEXT_API     
#undef GLFW_EGL_CONTEXT_API        

#undef GLFW_ARROW_CURSOR          
#undef GLFW_IBEAM_CURSOR          
#undef GLFW_CROSSHAIR_CURSOR       
#undef GLFW_HAND_CURSOR            
#undef GLFW_HRESIZE_CURSOR         
#undef GLFW_VRESIZE_CURSOR        

#undef GLFW_CONNECTED              
#undef GLFW_DISCONNECTED           

#undef GLFW_DONT_CARE              

	/*************************************************************************
	* Global definition cleanup
	*************************************************************************/

	/* ------------------- BEGIN SYSTEM/COMPILER SPECIFIC -------------------- */

#ifdef GLFW_WINGDIAPI_DEFINED
#undef WINGDIAPI
#undef GLFW_WINGDIAPI_DEFINED
#endif

#ifdef GLFW_CALLBACK_DEFINED
#undef CALLBACK
#undef GLFW_CALLBACK_DEFINED
#endif

	/* -------------------- END SYSTEM/COMPILER SPECIFIC --------------------- */



#endif /* _glfw3_h_ */

