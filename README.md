# Raylib Help Tools
Some tools to help you on your Raylib game :)


## Here we have:
  ## CMA
  One little helper header file that will help you manage your memory!

  ### Functions:
  #### InitCMA:
  ##### *Initializes the CMA, just clears the list of allocations*
  #### GetMemoryAmntTxt:
  ##### *Returns one text with the amount of memory used and the type of amount (Bytes, Megabytes, Gigabytes)*
  #### AddPtr:
  ##### *Adds one pointer to the list of pointers*
  #### RemovePtr:
  ##### *Removes one pointer from the list of pointers*
  #### HasPtr:
  ##### *Returns if the list has one pointer*
  #### AllocateMem:
  ##### *Allocates some space in ram, stores one pointer to that space on to one list to clear it out later and returns the pointer back to you*
  #### FreeMem:
  ##### *Frees one pointer from memory and removes it from the pointer list*
  #### FreeAllMem:
  ##### *Frees all the pointers from the pointer list*
  
  
  ## Aspect Manager
  One cool header file that will maintain the aspect ratio of your game!

  ### Functions:
  #### InitAscpectManager:
  ##### *Initializes the aspect manager*
  #### BeginGameDraw:
  ##### *Starts drawing to the game screen*
  #### EndGameDraw:
  ##### *Stops drawing to the game screen*
  #### DrawGame:
  ##### *Draws the game screen to the game window, this already calls the "StartDrawing" and "EndDrawing" raylib's function, ok?*
  #### UnloadAspectManager:
  ##### *Unloads the game screen from memory, very important thing to call*
  #### ScreenToGame:
  ##### *Converts one position from the game screen to the game, good for getting the mouse position*


  ## Texture Manager
  One header file that manager textures and this type of shit!


  ### Functions:
  #### InitTextures:
  ##### *Initializes the texture mager*
  #### AddGameTexture:
  ##### *Adds one texture to the texture list*
  #### LoadGameTexture:
  ##### *Loads one texture and puts it inside the texture list
  #### UnloadGameTexture:
  ##### *Unloads one texture from memory and removes it from the texture list
  #### UnloadTextures:
  ##### *Unloads all the textures from memory*
  ##### DrawGameTexture:
  ##### *Draws one game texture, i just created this because i hate the raylib's draw function*
  
  ### Structs:
  #### SGameTexture:
  ##### *One struct to hold the texture info*


  ## Anim
  One header file to create animations and to stuff with them


  ### Functions:
  #### InitAnims:
  ##### *Initializes the animations list*
  #### AddAnimation:
  ##### *Adds one animation to the animations list*
  #### DefineAnimationDelimiter:
  ##### *Adds one animation delimiter to one animation, this will basically hold the animation frames inside one area*
  #### PlayAnimation:
  ##### *Makes one animation play one Animation Delimiter, this will hold the animation frame inside one area*
  #### CreateAnimation:
  ##### *Creates one new animation for you to use*
  #### UpdateAnimation:
  ##### *Updates one animation*
  #### UpdateAnimations:
  ##### *Updates all the animations*
  #### DrawAnimation:
  ##### *Draws one animation*
  #### UnloadAnimation:
  ##### *Unloads one animation and the texture of that animation from memory*
  #### CopyAnimation:
  ##### *Creates one new animation but with all the things of the animation passed here*
  #### UnloadAnimations:
  ##### *Unloads all the animations*

  ### Structs:
  #### SAnimationDelimiter:
  ##### *One struct for the animation delimiter*
  #### SAnimation:
  ##### *One struct for the animation*


  ### Enums:
  #### ANIM_END_TYPE:
  #### *What the animation should do when reaching the end?*


  ## METH
  One header file to hold some math functions, NEEDED BY: Anim and Aspect Manager


  ### Functions:
  #### MIN:
  ##### *Returns the lowest value on the 2 arguments*
  #### SLerp:
  ##### *Stands for "Seconds Lerp" it is just one lerp function but it is seconds based
  #### Sign:
  ##### *Returns -1, 0 or 1 based in the value of the argument*
  #### SLerpVec2:
  ##### *Lerps one vector2 but in seconds*
  #### SLerpColr:
  ##### *Lerps one color but in seconds*
  #### AngleDifference:
  ##### *Returns the diference between 2 angles*
  #### SLerpAngle:
  ##### *Lerps one angle*
