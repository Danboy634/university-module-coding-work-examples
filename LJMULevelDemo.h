#pragma once

#include "Application.h"

#include "Win32RenderWindow.h"
#include "RendererDX11.h"

#include "ViewPerspective.h"
#include "FileSystem.h"

//Hieroglyph Includes
#include "Camera.h"
#include "Scene.h"
#include "GeometryActor.h"
#include "TextActor.h"
#include "PointLight.h"

//STL Includes
#include <vector>

//LJMU Framework Includes
#include "LJMUTextOverlay.h"
#include "LJMUMeshOBJ.h"
#include "LJMUShaderMaker.h"
#include "LJMUTwoDOverlay.h"
#include "LJMUMateriaParams.h"
#include "LJMUH3Util.h"


using namespace Glyph3;

//	TYPE DEFINITIONS OF OUR MESH COMPRISED OF BASIC VERTEX OBJECTS
typedef std::shared_ptr<Glyph3::DrawExecutorDX11<Glyph3::BasicVertexDX11::Vertex>> BasicMeshPtr;

namespace LJMUDX
{
	//////////////////////////////////////
	//LJMULevelDemo.H
	//Class Application for a DirectX 11
	//Driven Application using the DirectX Toolkit
	//Hieroglyph 3 Rendering Engine and LUA.
	//
	//
	//AUTHORS:  DR Po Yang
	//			DR CHRIS CARTER
	//////////////////////////////////////
	class LJMULevelDemo : public Application //Inherit from the Hieroglyph Base Class
	{

	public:
		//------------CONSTRUCTORS------------------------------------------------
		LJMULevelDemo();	//Standard Empty Constructor which builds the object

	public:
		//------------INHERITED METHODS-------------------------------------------
		virtual void Initialize();					//Initialise the DirectX11 Scene
		virtual void Update();						//Update the DirectX Scene
		virtual void Shutdown();					//Shutdown the DirectX11 Scene

		virtual bool ConfigureEngineComponents();	//Initialise Hieroglyph and DirectX TK Modules
		virtual void ShutdownEngineComponents();	//Destroy Hieroglyph and DirectX TK Modules

		virtual void TakeScreenShot();				//Allow a screenshot to be generated

		virtual bool HandleEvent(EventPtr pEvent);	//Handle an I/O Event
		virtual std::wstring GetName();				//Get the Name of this App Instance

		//------------CUSTOM METHODS-----------------------------------------------
		void inputAssemblyStage();					//Stage to setup our VB and IB Info
		
		std::wstring outputFPSInfo();				//Convert the timer's Frames Per Second to a formatted string
		std::wstring outputDebugInfo(const GeometryActor& pactor);
		std::wstring outputDebugInfoAll();

		std::wstring outputDebugMatrix(const GeometryActor& pactor);

		std::wstring outputDebugTransform(const Matrix4f& pmatrix, Vector3f ppoint);
		std::wstring outputDebugTransform(const GeometryActor& pactor, Vector3f ppoint);


	    protected:
		//-------------CLASS MEMBERS-----------------------------------------------
		RendererDX11*			_obj_renderer11;	//Pointer to our DirectX 11 Device
		Win32RenderWindow*		_obj_window;		//Pointer to our Windows-Based Window

		int						_swap_index;		//Index of our Swap Chain 
		ResourcePtr				_tgt_render;		//Pointer to the GPU Render Target for Colour
		ResourcePtr				_tgt_depth;			//Pointer to the GPU Render Target for Depth

		LJMUResourceHelper				_local_content;

		void setupInitialState();					//setup the Initial State of our Virtual Scene (Apply Static Transforms)

		//-------------HELPER METHODS----------------------------------------------

		BasicMeshPtr generateOBJMesh(std::wstring pmesh, Vector4f pcolour = Vector4f(0, 0, 0, 1));

		FileSystem              _fs;

		//--------------HIEROGLYPH OBJECTS-----------------------------------------
		ViewPerspective*			_render_view;	//3D Output View - DirectX 11 Accelerated
		std::vector<GeometryActor*>	_objects;
		std::vector<TextActor*>		_text_elems;
		GeometryActor*				_floor;
		PointLight*					_light;
		
		std::vector<GeometryActor*>		_list_objects;
		std::vector<TextActor*>			_list_text_3D;
		std::vector<PointLight*>		_list_lights;


		LJMUTextOverlay*            _render_text;	//2D Output View - DirectX 11 Accelerated
		Camera*						_obj_camera;	//Camera Object

		std::vector<Actor*>					_list_models;
		std::vector<BasicMeshPtr>			_list_meshes;
		std::vector<LJMUMaterialParams*>	_list_params;


		unsigned int				_curr_obj;

		ResourcePtr                 _texture;
		ResourcePtr                 _texture2;
		ResourcePtr                 _texture3;
		ResourcePtr                 _texture4;
		ResourcePtr                 _texture5;
		ResourcePtr                 _texture6;
		ResourcePtr                 _texture7;
		ResourcePtr                 _texture8;
		ResourcePtr                 _texture9;
		ResourcePtr                 _texture10;




		int                         object_2_direction;
		int                         object_3_direction; // object will move to Y positive and X positive, otherwise direction == 1
		int                         object_5_direction;
		int                         object_obj_direction;
		int                         object_6_direction;
		int                         object_7_direction;



	};

}
/*


*/