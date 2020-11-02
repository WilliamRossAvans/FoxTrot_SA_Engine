#pragma once

#ifndef ERRORCODES__H
#define ERRORCODES__H

#define ERROR_CODE_something										0x00
#define ERROR_CODE_SCENE_NO_OBJECT_FOUND							0x01
#define ERROR_CODE_SCENE_NO_LAYERS_TO_SWITCH						0x02

#define ERROR_CODE_SCENEMANAGER_NO_CURRENT_SCENE					0x03
#define ERROR_CODE_SCENEMANAGER_SCENE_ALREADY_EXISTS				0x04
#define ERROR_CODE_SCENEMANAGER_SCENES_IS_EMPTY						0x05
#define ERROR_CODE_SCENEMANAGER_CANT_FIND_SCENE_WITH_ID				0x06
#define ERROR_CODE_SCENEMANAGER_OBJECTID_DOES_NOT_EXIST_IN_CURRENT_SCENE				0x07

#define ERROR_CODE_SVIFACADE_CANT_CREATE_RENDERER					0x08
#define ERROR_CODE_SVIFACADE_CANT_CREATE_WINDOW						0x09
#define ERROR_CODE_SVIFACADE_CANT_INITIALIZE_SDL_IMAGE				0x0A
#define ERROR_CODE_SVIFACADE_LOADIMAGE_SPRITE_ID_IS_NULL			0x0B
#define ERROR_CODE_SVIFACADE_FILENAME_IS_NULL						0x0C
#define ERROR_CODE_SVIFACADE_RENDERCOPY_SPRITE_ID_IS_NULL			0x0D
#define ERROR_CODE_SVIFACADE_RENDERCOPY_XPOS_IS_NULL				0x0E
#define ERROR_CODE_SVIFACADE_RENDERCOPY_YPOS_IS_NULL				0x0F
#define ERROR_CODE_SVIFACADE_RENDERCOPY_HEIGHT_IS_NULL				0x10
#define ERROR_CODE_SVIFACADE_RENDERCOPY_WIDTH_IS_NULL				0x11
#define ERROR_CODE_SVIFACADE_RENDERCOPY_ROTATION_IS_NULL			0x12
#define ERROR_CODE_IMAGE_FILE_NOT_FOUND								0x13

#define PHYSICS_ENGINE_OBJECT_DOESNT_EXIST							0x14
#define PHYSICS_FACADE_OBJECT_DOESNT_EXIST							0x15
#define PHYSICS_FACADE_BODY_DOESNT_EXIST							0x16

#define ERROR_CODE_SVIFACADE_SOUND_FILE_NOT_FOUND					0x17
#define ERROR_CODE_SVIFACADE_SOUND_IDENTIFIER_NOT_FOUND				0x18
#define ERROR_CODE_SVIFACADE_NO_MUSIC_LOADED						0x19
#define ERROR_CODE_SVIFACADE_INVALID_FADETIME						0x1A
#define ERROR_CODE_SPRITE_DOESNT_EXIST								0x1B

#define ERROR_CODE_SDL2FACADE_SPRITE_DOESNT_EXISTS					0x1C
#define ERROR_CODE_IMAGE_CANNOT_BE_SAVED							0x1D

#endif

static const char* ERRORCODES[] =
{
	"ERROR_CODE_something",
	"ERROR_CODE_SCENE_NO_OBJECT_FOUND",
	"ERROR_CODE_SCENE_NO_LAYERS_TO_SWITCH",

	"ERROR_CODE_SCENEMANAGER_NO_CURRENT_SCENE",
	"ERROR_CODE_SCENEMANAGER_SCENE_ALREADY_EXISTS",
	"ERROR_CODE_SCENEMANAGER_SCENES_IS_EMPTY",
	"ERROR_CODE_SCENEMANAGER_CANT_FIND_SCENE_WITH_ID",
	"ERROR_CODE_SCENEMANAGER_OBJECTID_DOES_NOT_EXIST_IN_CURRENT_SCENE",

	"ERROR_CODE_SVIFACADE_CANT_CREATE_RENDERER",
	"ERROR_CODE_SVIFACADE_CANT_CREATE_WINDOW",
	"ERROR_CODE_SVIFACADE_CANT_INITIALIZE_SDL_IMAGE",
	"ERROR_CODE_SVIFACADE_LOADIMAGE_SPRITE_ID_IS_NULL",
	"ERROR_CODE_SVIFACADE_FILENAME_IS_NULL",
	"ERROR_CODE_SVIFACADE_RENDERCOPY_SPRITE_ID_IS_NULL",
	"ERROR_CODE_SVIFACADE_RENDERCOPY_XPOS_IS_NULL",
	"ERROR_CODE_SVIFACADE_RENDERCOPY_YPOS_IS_NULL",
	"ERROR_CODE_SVIFACADE_RENDERCOPY_HEIGHT_IS_NULL",
	"ERROR_CODE_SVIFACADE_RENDERCOPY_WIDTH_IS_NULL",
	"ERROR_CODE_SVIFACADE_RENDERCOPY_ROTATION_IS_NULL",
	"ERROR_CODE_IMAGE_FILE_NOT_FOUND",

	"PHYSICS_ENGINE_OBJECT_DOESNT_EXIST",
	"PHYSICS_FACADE_OBJECT_DOESNT_EXIST",
	"PHYSICS_FACADE_BODY_DOESNT_EXIST",

	"ERROR_CODE_SVIFACADE_SOUND_FILE_NOT_FOUND",
	"ERROR_CODE_SVIFACADE_SOUND_IDENTIFIER_NOT_FOUND",
	"ERROR_CODE_SVIFACADE_NO_MUSIC_LOADED",
	"ERROR_CODE_SVIFACADE_INVALID_FADETIME",
	"ERROR_CODE_SPRITE_DOESNT_EXIST",

	"ERROR_CODE_SDL2FACADE_SPRITE_DOESNT_EXISTS",
	"ERROR_CODE_IMAGE_CANNOT_BE_SAVED"
};
