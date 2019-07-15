//------------Include the Application Header File----------------------------
#include "LJMULevelDemo.h"

//------------DX TK AND STD/STL Includes-------------------------------------
#include <sstream>
#include <iomanip>
//------------Include Hieroglyph Engine Files--------------------------------

//Include the Logging System
#include "Log.h"

//Include the Event System
#include "EventManager.h"
#include "EvtFrameStart.h"
#include "EvtChar.h"
#include "EvtKeyUp.h"
#include "EvtKeyDown.h"
#include "ScriptManager.h"

//Include the DirectX Rendering Components
#include "PipelineManagerDX11.h"
#include "BlendStateConfigDX11.h"
#include "BufferConfigDX11.h"
#include "DepthStencilStateConfigDX11.h"
#include "RasterizerStateConfigDX11.h"
#include "SwapChainConfigDX11.h"
#include "Texture2dConfigDX11.h"
#include "MaterialGeneratorDX11.h"

#include "FirstPersonCamera.h"

#include "LJMUMeshOBJ.h" 

//Add a Using Directive to avoid typing Glyph3 for basic constructs
using namespace Glyph3;
//Include our own application Namespace
using namespace LJMUDX;

LJMULevelDemo AppInstance; 

//---------CONSTRUCTORS-------------------------------------------------------

///////////////////////////////////////
//
///////////////////////////////////////
LJMULevelDemo::LJMULevelDemo()
//_render_text(nullptr),
//_render_view(nullptr),
//_obj_camera(nullptr),
//_obj_renderer11(nullptr),
//_obj_window(nullptr),
//_swap_index(0),
//_tgt_depth(nullptr),
//_tgt_render(nullptr)
{
	this->_curr_obj = 0;

	this->object_2_direction = 0;

	this->object_3_direction = 0;
}

//---------METHODS------------------------------------------------------------

//////////////////////////////////////
// Get the Window Name of this Application
//////////////////////////////////////
std::wstring LJMULevelDemo::GetName()
{
	return(std::wstring(L"5108COMP: DirectX Level Demonstration - AS1"));
}


void LJMULevelDemo::setupInitialState()
{
	Vector3f tscale(0.1f, 0.1f, 0.1f);
	this->_list_models[0]->GetBody()->Scale() = tscale;
	this->_list_models[0]->GetBody()->Position() = Vector3f(-20, 10, 0);
}

/////////////////////////////////////
// Assemble our Input Layouts for this
// Stage of the Pipeline.
/////////////////////////////////////
void LJMULevelDemo::inputAssemblyStage()
{
	//-----SETUP OUR GEOMETRY FOR THIS SCENE-----------------------------------------

	this->_texture = RendererDX11::Get()->LoadTexture(L"magma.jfif");

	this->_texture2 = RendererDX11::Get()->LoadTexture(L"background.png");

	this->_texture3 = RendererDX11::Get()->LoadTexture(L"background2.png");

	this->_texture4 = RendererDX11::Get()->LoadTexture(L"background3.png");
	
	this->_texture5 = RendererDX11::Get()->LoadTexture(L"Sun.jpg");

	this->_texture6 = RendererDX11::Get()->LoadTexture(L"Block.png");

	this->_texture7 = RendererDX11::Get()->LoadTexture(L"Ball.png");

	this->_texture8 = RendererDX11::Get()->LoadTexture(L"brickblock.png");

	this->_texture9 = RendererDX11::Get()->LoadTexture(L"Tiles.png");

	this->_texture10 = RendererDX11::Get()->LoadTexture(L"floor.png");


	//this->_sprite_tex = RendererDX11::Get()->LoadTexture(L"Face.png");

	//Setup Floor
	GeometryActor* BottomBoard = new GeometryActor();
	BottomBoard->SetColor(Vector4f(0.1f, 0.4f, 0.1f, 1.0f));
	BottomBoard->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(50.0f, 0.1f, 50.0f));
	BottomBoard->UseSolidMaterial();
	BottomBoard->GetNode()->Position() = Vector3f(0.0f, -5.0f, 0.0f);
	


	this->m_pScene->AddActor(BottomBoard);

	GeometryActor* TopBoard = new GeometryActor();
	TopBoard->SetColor(Vector4f(0.1f, 0.1f, 0.1f, 1.0f));
	TopBoard->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(50.0f, 0.1f, 50.0f));
	TopBoard->UseSolidMaterial();
	TopBoard->GetNode()->Position() = Vector3f(0.0f, 45.0f, 0.0f);


	TopBoard->UseTexturedMaterial(this->_texture2);


	this->m_pScene->AddActor(TopBoard);

	GeometryActor* RightBoard = new GeometryActor();
	RightBoard->SetColor(Vector4f(0.1f, 0.1f, 0.1f, 1.0f));
	RightBoard->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(25.0f, 0.1f, 50.0f));
	RightBoard->UseSolidMaterial();
	RightBoard->GetNode()->Position() = Vector3f(50.0f, 20.0f, 0.0f);


	RightBoard->GetNode()->Rotation().RotationZ(3.1415926 * 0.5);

	RightBoard->UseTexturedMaterial(this->_texture3);

	this->m_pScene->AddActor(RightBoard);

	
	GeometryActor* LeftBoard = new GeometryActor();
	LeftBoard->SetColor(Vector4f(0.1f, 0.1f, 0.1f, 1.0f));
	LeftBoard->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(25.0f, 0.1f, 50.0f));
	LeftBoard->UseSolidMaterial();
	LeftBoard->GetNode()->Position() = Vector3f(-50.0f, 20.0f, 0.0f);


	LeftBoard->GetNode()->Rotation().RotationZ(3.1415926 * 0.5);

	LeftBoard->UseTexturedMaterial(this->_texture4);

	this->m_pScene->AddActor(LeftBoard);
	
	
	GeometryActor* BackBoard = new GeometryActor();
	BackBoard->SetColor(Vector4f(0.1f, 0.1f, 0.1f, 1.0f));
	BackBoard->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(50.25f, 0.1f, 22.5f));
	BackBoard->UseSolidMaterial();
	BackBoard->GetNode()->Position() = Vector3f(0.0f, 22.5f, 50.0f);


	BackBoard->GetNode()->Rotation().RotationX(3.1415926 * 0.5);

	
	//BackBoard->SetColor(Vector4f(1, 1, 1, 1));

	BackBoard->UseTexturedMaterial(this->_texture2);


	this->m_pScene->AddActor(BackBoard);

	this->_local_content.loadImage(1, std::wstring(L"reptile_diff.png"));
	this->_local_content.loadImage(2, std::wstring(L"reptile_diff_alt.png"));

	
	BasicMeshPtr tmesh = this->generateOBJMesh(L"reptile.obj", Vector4f(1, 1, 1, 1));
	this->_list_meshes.push_back(tmesh);


	Vector3f tscale(0.05f, 0.05f, 0.05f);


	Actor* tmeshactor = new Actor();
	MaterialPtr tmtl = LJMUShaderMaker::MakeActorTextured(*this->_obj_renderer11);
	tmtl->Parameters.SetShaderResourceParameter(L"ColorTexture", this->_local_content.getImage(2));
	tmeshactor->GetBody()->SetGeometry(this->_list_meshes[0]);
	tmeshactor->GetBody()->SetMaterial(tmtl);


	tmeshactor->GetBody()->Position() = Vector3f(-30, 4, 0);
	tmeshactor->GetBody()->Rotation().RotationY(1.75f);
	tmeshactor->GetBody()->Scale() = tscale;
	
	this->_list_models.push_back(tmeshactor);
	

	BasicMeshPtr tmesh2 = this->generateOBJMesh(L"reptile.obj", Vector4f(1, 1, 1, 1));
	this->_list_meshes.push_back(tmesh2);


	Vector3f tscale2(0.05f, 0.05f, 0.05f);


	Actor* tmeshactor2 = new Actor();
	MaterialPtr tmtl2 = LJMUShaderMaker::MakeActorTextured(*this->_obj_renderer11);
	tmtl2->Parameters.SetShaderResourceParameter(L"ColorTexture", this->_local_content.getImage(1));
	tmeshactor2->GetBody()->SetGeometry(this->_list_meshes[0]);
	tmeshactor2->GetBody()->SetMaterial(tmtl2);


	tmeshactor2->GetBody()->Position() = Vector3f(41, 23, -5);
	tmeshactor2->GetBody()->Rotation().RotationY(-1.75f);
	tmeshactor2->GetBody()->Scale() = tscale2;

	this->_list_models.push_back(tmeshactor2);




	BasicMeshPtr tmesh3 = this->generateOBJMesh(L"reptile.obj", Vector4f(1, 1, 1, 1));
	this->_list_meshes.push_back(tmesh3);


	Vector3f tscale3(0.05f, 0.05f, 0.05f);


	Actor* tmeshactor3 = new Actor();
	MaterialPtr tmtl3 = LJMUShaderMaker::MakeActorPhong(*this->_obj_renderer11);
	//tmtl3->Parameters.SetShaderResourceParameter(L"ColorTexture", this->_local_content.getImage(1));
	tmeshactor3->GetBody()->SetGeometry(this->_list_meshes[0]);
	tmeshactor3->GetBody()->SetMaterial(tmtl3);


	tmeshactor3->GetBody()->Position() = Vector3f(0, 4, 0);
	tmeshactor3->GetBody()->Rotation().RotationY(-1.75f);
	tmeshactor3->GetBody()->Scale() = tscale3;

	this->_list_models.push_back(tmeshactor3);


	//--------------POPULATE SCENE USING OUR DATA STRUCTURES---------------------------------------
	for (auto it = this->_list_objects.begin(); it != this->_list_objects.end(); ++it)
	{
		this->m_pScene->AddActor((*it));

	}

	for (auto it = this->_list_text_3D.begin(); it != this->_list_text_3D.end(); ++it)
	{
		this->m_pScene->AddActor((*it));
	}

	for (auto it = this->_list_lights.begin(); it != this->_list_lights.end(); ++it)
	{
		this->m_pScene->AddLight((*it));
	}

	for (auto it = this->_list_models.begin(); it != this->_list_models.end(); ++it)
	{
		this->m_pScene->AddActor((*it));
	}


	/*for (int i = 0; i < 2; i++)
	{*/
	//Create our Primitive, specifying the Local Space lccation and size of object
	/*if (i % 3 == 0)
	{
	tactor->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(3.0f, 3.0f, 3.0f));
	}*/
	/*	else if (i % 3 == 1)
	{
	tactor->DrawCylinder(Vector3f(0.0f, -3.0f, 0.0f), Vector3f(0.0f, 3.0f, 0.0f), 3, 3);
	}
	else
	{
	tactor->DrawSphere(Vector3f(5.0f, 5.0f, 5.0f), 4.0f, 20, 20);
	}*/

		//Create our Geometry Actor object
		GeometryActor* tactor = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor = Vector3f::Random();
		tcolor.Clamp();
		Vector4f tfullcolor;
		tfullcolor.x = tcolor.x;
		tfullcolor.y = tcolor.y;
		tfullcolor.z = tcolor.z;
		tfullcolor.w = 1;
		//tactor->SetColor(tfullcolor);

		tactor->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(50.0f, 3.0f, 50.0f));

		//tactor->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(3.0f, 3.0f, 3.0f));

		//tactor->SetColor(Vector4f(1, 1, 1, 1));
		tactor->UseTexturedMaterial(this->_texture);

		//tactor->UseSolidMaterial();

		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor);


		//Create our Geometry Actor object
		GeometryActor* tactor2 = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor2 = Vector3f::Random();
		tcolor2.Clamp();
		Vector4f tfullcolor2;
		tfullcolor2.x = tcolor2.x;
		tfullcolor2.y = tcolor2.y;
		tfullcolor2.z = tcolor2.z;
		tfullcolor2.w = 1;
		//tactor2->SetColor(tfullcolor2);

		tactor2->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(13.0f, 2.0f, 25.0f));


		//tactor->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(3.0f, 3.0f, 3.0f));

		//tactor2->UseSolidMaterial();

		tactor2->UseTexturedMaterial(this->_texture10);


		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor2);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor2);


		//Create our Geometry Actor object
		GeometryActor* tactor3 = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor3 = Vector3f::Random();
		tcolor3.Clamp();
		Vector4f tfullcolor3;
		tfullcolor3.x = tcolor3.x;
		tfullcolor3.y = tcolor3.y;
		tfullcolor3.z = tcolor3.z;
		tfullcolor3.w = 1;
		/*tactor3->SetColor(tfullcolor3);*/


		tactor3->DrawSphere(Vector3f(5.0f, 5.0f, 5.0f), 4.0f, 20, 20);

		//tactor3->UseSolidMaterial();

		tactor3->UseTexturedMaterial(this->_texture5);



		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor3);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor3);

		//Create our Geometry Actor object
		GeometryActor* tactor4 = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor4 = Vector3f::Random();
		tcolor4.Clamp();
		Vector4f tfullcolor4;
		tfullcolor4.x = tcolor4.x;
		tfullcolor4.y = tcolor4.y;
		tfullcolor4.z = tcolor4.z;
		tfullcolor4.w = 1;
		//tactor4->SetColor(tfullcolor4);

		tactor4->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(3.0f, 3.0f, 3.0f));

		//tactor4->UseSolidMaterial();

		tactor4->UseTexturedMaterial(this->_texture6);


		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor4);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor4);

		//Create our Geometry Actor object
		GeometryActor* tactor5 = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor5 = Vector3f::Random();
		tcolor5.Clamp();
		Vector4f tfullcolor5;
		tfullcolor5.x = tcolor5.x;
		tfullcolor5.y = tcolor5.y;
		tfullcolor5.z = tcolor5.z;
		tfullcolor5.w = 1;
		tactor5->SetColor(tfullcolor5);

		tactor5->DrawCylinder(Vector3f(0.0f, -3.0f, 0.0f), Vector3f(0.0f, 3.0f, 0.0f), 3, 3);

		tactor5->UseSolidMaterial();

		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor5);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor5);



		//Create our Geometry Actor object
		GeometryActor* tactor6 = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor6 = Vector3f::Random();
		tcolor6.Clamp();
		Vector4f tfullcolor6;
		tfullcolor6.x = tcolor6.x;
		tfullcolor6.y = tcolor6.y;
		tfullcolor6.z = tcolor6.z;
		tfullcolor6.w = 1;
		//tactor6->SetColor(tfullcolor6);

		tactor6->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(13.0f, 4.0f, 10.0f));

		//tactor6->UseSolidMaterial();

		tactor6->UseTexturedMaterial(this->_texture10);
		


		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor6);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor6);



		//Create our Geometry Actor object
		GeometryActor* tactor7 = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor7 = Vector3f::Random();
		tcolor7.Clamp();
		Vector4f tfullcolor7;
		tfullcolor7.x = tcolor7.x;
		tfullcolor7.y = tcolor7.y;
		tfullcolor7.z = tcolor7.z;
		tfullcolor7.w = 1;
		//tactor7->SetColor(tfullcolor7);

		tactor7->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(3.0f, 3.0f, 10.0f));

		//tactor7->UseSolidMaterial();


		tactor7->UseTexturedMaterial(this->_texture8);


		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor7);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor7);

		//Create our Geometry Actor object
		GeometryActor* tactor8 = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor8 = Vector3f::Random();
		tcolor8.Clamp();
		Vector4f tfullcolor8;
		tfullcolor8.x = tcolor8.x;
		tfullcolor8.y = tcolor8.y;
		tfullcolor8.z = tcolor8.z;
		tfullcolor8.w = 1;
		//tactor7->SetColor(tfullcolor7);

		tactor8->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(3.0f, 3.0f, 10.0f));

		//tactor7->UseSolidMaterial();


		tactor8->UseTexturedMaterial(this->_texture8);


		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor8);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor8);


		//Create our Geometry Actor object
		GeometryActor* tactor9 = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor9 = Vector3f::Random();
		tcolor9.Clamp();
		Vector4f tfullcolor9;
		tfullcolor9.x = tcolor9.x;
		tfullcolor9.y = tcolor9.y;
		tfullcolor9.z = tcolor9.z;
		tfullcolor9.w = 1;
		//tactor9->SetColor(tfullcolor9);

		tactor9->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(6.0f, 2.0f, 10.0f));

		//tactor9->UseSolidMaterial();

		tactor9->UseTexturedMaterial(this->_texture10);

		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor9);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor9);

		//Create our Geometry Actor object
		GeometryActor* tactor10 = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor10 = Vector3f::Random();
		tcolor10.Clamp();
		Vector4f tfullcolor10;
		tfullcolor10.x = tcolor10.x;
		tfullcolor10.y = tcolor10.y;
		tfullcolor10.z = tcolor10.z;
		tfullcolor10.w = 1;
		//tactor10->SetColor(tfullcolor10);

		tactor10->DrawSphere(Vector3f(5.0f, 5.0f, 5.0f), 0.75f, 20, 20);

		//tactor10->UseSolidMaterial();

		tactor10->UseTexturedMaterial(this->_texture7);


		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor10);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor10);


		//TextActor* ttext = new TextActor();
		//ttext->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//ttext->GetNode()->Position() = tactor->GetNode()->Position() + Vector3f(0, 15, 0);
		//ttext->SetLineJustification(LineJustification::CENTER);
		//ttext->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		//this->_text_elems.push_back(ttext);
		//this->m_pScene->AddActor(ttext);
	
		//TextActor* ttext2 = new TextActor();
		//ttext2->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//ttext2->GetNode()->Position() = tactor2->GetNode()->Position() + Vector3f(0, 15, 0);
		//ttext2->SetLineJustification(LineJustification::CENTER);
		//ttext2->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		//this->_text_elems.push_back(ttext2);
		//this->m_pScene->AddActor(ttext2);

		//TextActor* ttext3 = new TextActor();
		//ttext3->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//ttext3->GetNode()->Position() = tactor3->GetNode()->Position() + Vector3f(0, 15, 0);
		//ttext3->SetLineJustification(LineJustification::CENTER);
		//ttext3->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		//this->_text_elems.push_back(ttext3);
		//this->m_pScene->AddActor(ttext3);


		//TextActor* ttext4 = new TextActor();
		//ttext4->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//ttext4->GetNode()->Position() = tactor4->GetNode()->Position() + Vector3f(0, 15, 0);
		//ttext4->SetLineJustification(LineJustification::CENTER);
		//ttext4->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		//this->_text_elems.push_back(ttext4);
		//this->m_pScene->AddActor(ttext4);


		//TextActor* ttext5 = new TextActor();
		//ttext5->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//ttext5->GetNode()->Position() = tactor5->GetNode()->Position() + Vector3f(0, 15, 0);
		//ttext5->SetLineJustification(LineJustification::CENTER);
		//ttext5->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		//this->_text_elems.push_back(ttext5);
		//this->m_pScene->AddActor(ttext5);

		//TextActor* ttext6 = new TextActor();
		//ttext6->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//ttext6->GetNode()->Position() = tactor6->GetNode()->Position() + Vector3f(0, 15, 0);
		//ttext6->SetLineJustification(LineJustification::CENTER);
		//ttext6->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		//this->_text_elems.push_back(ttext6);
		//this->m_pScene->AddActor(ttext6);

		//TextActor* ttext7 = new TextActor();
		//ttext7->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//ttext7->GetNode()->Position() = tactor7->GetNode()->Position() + Vector3f(0, 15, 0);
		//ttext7->SetLineJustification(LineJustification::CENTER);
		//ttext7->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		//this->_text_elems.push_back(ttext7);
		//this->m_pScene->AddActor(ttext7);

		//TextActor* ttext8 = new TextActor();
		//ttext8->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//ttext8->GetNode()->Position() = tactor8->GetNode()->Position() + Vector3f(0, 15, 0);
		//ttext8->SetLineJustification(LineJustification::CENTER);
		//ttext8->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		//this->_text_elems.push_back(ttext8);
		//this->m_pScene->AddActor(ttext8);

		//TextActor* ttext9 = new TextActor();
		//ttext9->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//ttext9->GetNode()->Position() = tactor9->GetNode()->Position() + Vector3f(0, 15, 0);
		//ttext9->SetLineJustification(LineJustification::CENTER);
		//ttext9->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		//this->_text_elems.push_back(ttext9);
		//this->m_pScene->AddActor(ttext9);

		//TextActor* ttext10 = new TextActor();
		//ttext10->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//ttext10->GetNode()->Position() = tactor10->GetNode()->Position() + Vector3f(0, 15, 0);
		//ttext10->SetLineJustification(LineJustification::CENTER);
		//ttext10->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		//this->_text_elems.push_back(ttext10);
		//this->m_pScene->AddActor(ttext10);

		//}



	this->_objects[0]->GetNode()->Position() = Vector3f(0.0f, -2.0f, 0.0f);
	this->_objects[0]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[0]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));
	
	this->_objects[1]->GetNode()->Position() = Vector3f(-37.0f, 2.0f, 0.0f);
	this->_objects[1]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[1]->GetNode()->Rotation().RotationZYX(Vector3f(0.0f, 0, 0));
	
	this->_objects[2]->GetNode()->Position() = Vector3f(30.0f, 25.0f, 20.0f);
	this->_objects[2]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[2]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[3]->GetNode()->Position() = Vector3f(-10.0f, 25.0f, 0.0f);
	this->_objects[3]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[3]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[4]->GetNode()->Position() = Vector3f(-32.0f, 25.0f, 0.0f);
	this->_objects[4]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[4]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[5]->GetNode()->Position() = Vector3f(0.0f, 2.0f, 0.0f);
	this->_objects[5]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[5]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[6]->GetNode()->Position() = Vector3f(20.0f, 15.0f, 0.0f);
	this->_objects[6]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[6]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[7]->GetNode()->Position() = Vector3f(26.0f, 21.0f, 0.0f);
	this->_objects[7]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[7]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[8]->GetNode()->Position() = Vector3f(44.0f, 21.0f, 0.0f);
	this->_objects[8]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[8]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[9]->GetNode()->Position() = Vector3f(44.0f, 20.0f, -3.5f);
	this->_objects[9]->GetNode()->Scale() = Vector3f(0.75f, 0.75f, 0.75f);
	this->_objects[9]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_light = new PointLight();
	this->_light->SetAmbient(Vector4f(0.2f, 0.2f, 0.2f, 1.0f));
	this->_light->SetDiffuse(Vector4f(0.6f, 0.6f, 0.6f, 1.0f));
	this->_light->SetSpecular(Vector4f(0.6f, 0.6f, 0.6f, 1.0f));
	this->_light->GetNode()->Position() = Vector3f(0.0f, 100.0f, 25.0f);
	this->m_pScene->AddLight(this->_light);


	

}
////////////////////////////////////
// Initialise our DirectX 3D Scene
////////////////////////////////////
void LJMULevelDemo::Initialize()
{
	//Call the Input Assembly Stage to setup the layout of our Engine Objects
	/*this->inputAssemblyStage();

	this->_obj_camera = new Camera();

	Vector3f tcamerapos(0.0f, 20.0f, -50.0f);
	this->_obj_camera->Spatial().SetTranslation(tcamerapos);

	this->_render_view = new ViewPerspective(*this->_obj_renderer11,
		                                     this->_tgt_render, this->_tgt_depth);
	this->_render_view->SetBackColor(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
	this->_obj_camera->SetCameraView(this->_render_view);

	this->_render_text = new LJMUTextOverlay(*this->_obj_renderer11, 
		                                      this->_tgt_render, 
											  std::wstring(L"Cambria"), 
											  25);	

	this->_obj_camera->SetOverlayView(this->_render_text);
	
	float twidth = 1024.0f;
	float theight = 768.0f;
	this->_obj_camera->SetProjectionParams(0.1f, 1000.0f, twidth/ theight, 
		                                   static_cast<float>(GLYPH_PI) / 2.0f);
	
	this->m_pScene->AddCamera(this->_obj_camera);	*/

	this->inputAssemblyStage();

	this->_obj_camera = new FirstPersonCamera();
	this->_obj_camera->SetEventManager(&this->EvtManager);

	Vector3f tcamerapos(0.0f, 50.0f, -100.0f);
	this->_obj_camera->Spatial().SetTranslation(tcamerapos);

	this->_render_view = new ViewPerspective(*this->_obj_renderer11,
		this->_tgt_render, this->_tgt_depth);
	this->_render_view->SetBackColor(Vector4f(0.1f, 0.3f, 0.4f, 1.0f));
	this->_obj_camera->SetCameraView(this->_render_view);

	this->_render_text = new LJMUTextOverlay(*this->_obj_renderer11,
		this->_tgt_render,
		std::wstring(L"Cambria"),
		25);

	this->_obj_camera->SetOverlayView(this->_render_text);

	float twidth = this->_obj_window->GetWidth();
	float theight = this->_obj_window->GetHeight();
	this->_obj_camera->SetProjectionParams(0.1f, 1000.0f, twidth / theight, static_cast<float>(GLYPH_PI) / 4.0f);

	this->m_pScene->AddCamera(this->_obj_camera);

}

///////////////////////////////////
// Update the State of our Game and 
// Output the Results to Screen (Render)
/////////////////////////////////// 
void LJMULevelDemo::Update()
{
	this->m_pTimer->Update();
	EvtManager.ProcessEvent(EvtFrameStartPtr( new EvtFrameStart(this->m_pTimer->Elapsed())));

	//----------START RENDERING--------------------------------------------------------------

	//this->m_pScene->Update(m_pTimer->Elapsed());
	//this->m_pScene->Render(this->_obj_renderer11);

	//---------3D Scene Updates---------------------------------------------------------

	float ttpf = this->m_pTimer->Elapsed();

	// 1. Linear Interpolation

	static float tposx = 0;
	static float tposy = 0;
	static float tposz = 0;

	////int   direction = 0; // object will move to Y positive and X positive, otherwise direction == 1
	////int   boundary = 1; // object moves out of boundary, it will be zero, otherwise it will be one ;

	////Given point
	//Vector3f point(50.0, 50.0, 50.0);

	//tposx = this->_objects[3]->GetNode()->Position().x;
	//tposy = this->_objects[3]->GetNode()->Position().y;
	//tposz = this->_objects[3]->GetNode()->Position().z;

	//float x_min = -10.0;
	//float x_max = 20.0;
	//float y_min = 25.0;
	//float y_max = 55.0;
	//float z_min = 25.0;
	//float z_max = 55.0;

	//if (this->object_3_direction == 0)
	//{
	//	if (tposx <= x_max && tposy <= y_max)
	//	{
	//		tposx += 0.03;
	//		tposy += 0.03;
	//	}
	//	
	//	if (tposx > x_max || tposy > y_max)
	//	{
	//		tposx -= 0.03;
	//		tposy -= 0.03;
	//		this->object_3_direction = 1;
	//		
	//	}
	//}
	//else 
	//{
	//	if (tposx <= x_max && tposy <= y_max )
	//	{
	//		tposx -= 0.03;
	//		tposy -= 0.03;
	//	}
	//	
	//	if (tposx < x_min || tposy < y_min)
	//	{
	//		tposx += 0.03;
	//		tposy += 0.03;
	//		this->object_3_direction = 0;
	//	}
	//}

	

	//int   direction = 0; // object will move to Y positive and X positive, otherwise direction == 1
	//int   boundary = 1; // object moves out of boundary, it will be zero, otherwise it will be one ;

	//Given point
	Vector3f point(50.0, 50.0, 100.0);

	tposx = this->_objects[3]->GetNode()->Position().x;
	tposy = this->_objects[3]->GetNode()->Position().y;
	tposz = this->_objects[3]->GetNode()->Position().z;

	float x_min = -10.0;
	float x_max = 20.0;
	float y_min = 25.0;
	float y_max = 55.0;
	float z_min = -20.0;
	float z_max = 10.0;

	if (this->object_3_direction == 0)
	{
		if (tposz <= z_max)
		{
			tposz += 0.03;
			
		}
		
		if (tposz > z_max)
		{
			tposz -= 0.03;
			
			this->object_3_direction = 1;
			
		}
	}
	else 
	{
		if (tposz <= z_max)
		{
			tposz -= 0.03;
			
		}
		
		if (tposz < z_min)
		{
			tposz += 0.03;
			
			this->object_3_direction = 0;
		}
	}


	static float tposx5 = 0;
	static float tposy5 = 0;
	static float tposz5 = 0;

	tposx5 = this->_objects[5]->GetNode()->Position().x;
	tposy5 = this->_objects[5]->GetNode()->Position().y;
	tposz5 = this->_objects[5]->GetNode()->Position().z;

	float x_min5 = -10.0;
	float x_max5 = 20.0;
	float y_min5 = 25.0;
	float y_max5 = 55.0;
	float z_min5 = -20.0;
	float z_max5 = 30.0;

	if (this->object_5_direction == 0)
	{
		if (tposz5 <= z_max5)
		{
			tposz5 += 0.03;

		}

		if (tposz5 > z_max5)
		{
			tposz5 -= 0.03;

			this->object_5_direction = 1;

		}
	}
	else
	{
		if (tposz5 <= z_max5)
		{
			tposz5 -= 0.03;

		}

		if (tposz5 < z_min5)
		{
			tposz5 += 0.03;

			this->object_5_direction = 0;
		}
	}

	static float tposxobj = 0;
	static float tposyobj = 0;
	static float tposzobj = 0;

	tposxobj = this->_objects[5]->GetNode()->Position().x;
	tposyobj = this->_objects[5]->GetNode()->Position().y;
	tposzobj = this->_objects[5]->GetNode()->Position().z;

	float x_minobj = -10.0;
	float x_maxobj = 20.0;
	float y_minobj = 25.0;
	float y_maxobj = 55.0;
	float z_minobj = -20.0;
	float z_maxobj = 30.0;

	if (this->object_obj_direction == 0)
	{
		if (tposzobj <= z_maxobj)
		{
			tposzobj += 0.03;

		}

		if (tposzobj > z_maxobj)
		{
			tposzobj -= 0.03;

			this->object_obj_direction = 1;

		}
	}
	else
	{
		if (tposzobj <= z_maxobj)
		{
			tposzobj -= 0.03;

		}

		if (tposzobj < z_minobj)
		{
			tposzobj += 0.03;

			this->object_obj_direction = 0;
		}
	}


	static float tposx6 = 0;
	static float tposy6 = 0;
	static float tposz6 = 0;

	tposx6 = this->_objects[6]->GetNode()->Position().x;
	tposy6 = this->_objects[6]->GetNode()->Position().y;
	tposz6 = this->_objects[6]->GetNode()->Position().z;

	float x_min6 = -10.0;
	float x_max6 = 50.0;
	float y_min6 = 10.0;
	float y_max6 = 22.0;
	float z_min6 = 25.0;
	float z_max6 = 55.0;

	if (this->object_6_direction == 0)
	{
		if (tposx6 <= x_max6 && tposy6 <= y_max6)
		{
			tposx6 += 0.03;
			tposy6 += 0.03;
		}
		
		if (tposx6 > x_max6 || tposy6 > y_max6)
		{
			tposx6 -= 0.03;
			tposy6 -= 0.03;
			this->object_6_direction = 1;
			
		}
	}
	else 
	{
		if (tposx6 <= x_max6 && tposy6 <= y_max6 )
		{
			tposx6 -= 0.03;
			tposy6 -= 0.03;
		}
		
		if (tposx6 < x_min6 || tposy6 < y_min6)
		{
			tposx6 += 0.03;
			tposy6 += 0.03;
			this->object_6_direction = 0;
		}
	}


	static float tposx7 = 0;
	static float tposy7 = 0;
	static float tposz7 = 0;

	tposx7 = this->_objects[7]->GetNode()->Position().x;
	tposy7 = this->_objects[7]->GetNode()->Position().y;
	tposz7 = this->_objects[7]->GetNode()->Position().z;

	float x_min7 = -10.0;
	float x_max7 = 50.0;
	float y_min7 = 16.0;
	float y_max7 = 28.0;
	float z_min7 = 25.0;
	float z_max7 = 55.0;

	if (this->object_7_direction == 0)
	{
		if (tposx7 <= x_max7 && tposy7 <= y_max7)
		{
			tposx7 += 0.03;
			tposy7 += 0.03;
		}

		if (tposx7 > x_max7 || tposy7 > y_max7)
		{
			tposx7 -= 0.03;
			tposy7 -= 0.03;
			this->object_7_direction = 1;

		}
	}
	else
	{
		if (tposx7 <= x_max7 && tposy7 <= y_max7)
		{
			tposx7 -= 0.03;
			tposy7 -= 0.03;
		}

		if (tposx7 < x_min7 || tposy7 < y_min7)
		{
			tposx7 += 0.03;
			tposy7 += 0.03;
			this->object_7_direction = 0;
		}
	}

	//if (tposx > x_min && tposx <)
	//{
	//	tposx = 0;
	//	tposy = 0;
	//	tposz = 0;
	//}



	//if (tposx > point.x && tposy > point.x && tposz > point.x)
	//{
	//	tposx = 0;
	//	tposy = 0;
	//	tposz = 0;
	//}

	this->_objects[3]->GetNode()->Position() = Vector3f(tposx, tposy, tposz);

	this->_objects[5]->GetNode()->Position() = Vector3f(tposx5, tposy5, tposz5);

	this->_list_models[2]->GetNode()->Position() = Vector3f(tposxobj, tposyobj, tposzobj);


	this->_objects[6]->GetNode()->Position() = Vector3f(tposx6, tposy6, tposz6);

	this->_objects[7]->GetNode()->Position() = Vector3f(tposx7, tposy7, tposz7);

	////Vector3f ttranslate(tposx, tposy, 0);
	////
	////if (ttranslate.Magnitude() > 50.0f)
	////{
	////tposx = 0;
	////tposy = 0;
	////}
	///////
	////this->_objects[0]->GetNode()->Position() += ttranslate;

	static float trotx = 0;
	static float troty = 0;
	static float trotz = 0;
	const float LOCAL_PI = 3.14159265f;
	const float DEG_TO_RAD = LOCAL_PI / 180.0f;
	trotx += 180 * ttpf * DEG_TO_RAD;
	troty += 90 * ttpf * DEG_TO_RAD;
	trotz += 360 * ttpf * DEG_TO_RAD;

	Matrix3f trot1, trot2, trot3;
	trot1.RotationX(trotx);
	trot2.RotationY(troty);
	trot3.RotationZ(trotz);

	//Matrix3f tpos1, tpos2, tpos3;


	//this->_objects[4]->GetNode()->Rotation() = trot1;
	this->_objects[2]->GetNode()->Rotation() = trot2;
	//this->_objects[4]->GetNode()->Rotation() = trot2;
	this->_objects[4]->GetNode()->Rotation() = trot1;

	//this->_objects[5]->GetNode()->Rotation() = trot3;

	//Relative Change
	Matrix3f trelrot1;
	trelrot1.RotationY(180 * ttpf * DEG_TO_RAD);
	this->_objects[2]->GetNode()->Rotation() *= trelrot1;

	/*static float trotx = 0;
	static float troty = 0;
	static float trotz = 0;*/
	/*const float LOCAL_PI = 3.14159265f;
	const float DEG_TO_RAD = LOCAL_PI / 180.0f;*/
	/*trotx += 180 * ttpf * DEG_TO_RAD;*/
	/*troty += 90 * ttpf * DEG_TO_RAD;*/
	/*trotz += 360 * ttpf * DEG_TO_RAD;*/

	//Matrix3f trot1, trot2, trot3;
	///*trot1.RotationX(trotx);*/
	//trot2.RotationY(troty);
	/*trot3.RotationZ(trotz);*/

	//this->_objects[4]->GetNode()->Rotation() = trot1;
	
	/*this->_objects[0]->GetNode()->Rotation() = trot3;*/

	//Relative Change
	Matrix3f trelrot2;
	trelrot2.RotationY(180 * ttpf * DEG_TO_RAD);
	this->_objects[4]->GetNode()->Rotation() *= trelrot2;

	Matrix3f trelrot3;
	trelrot3.RotationY(180 * ttpf * DEG_TO_RAD);
	this->_objects[5]->GetNode()->Rotation() *= trelrot3;

	Matrix3f trelrot7;
	trelrot7.RotationY(180 * ttpf * DEG_TO_RAD);
	this->_list_models[2]->GetNode()->Rotation() *= trelrot7;


	Matrix3f trelrot4;
	trelrot4.RotationY(180 * ttpf * DEG_TO_RAD);
	this->_objects[3]->GetNode()->Rotation() *= trelrot4;

	Matrix3f trelrot5;
	trelrot5.RotationX(90 * ttpf * DEG_TO_RAD);
	this->_objects[6]->GetNode()->Rotation() *= trelrot5;

	Matrix3f trelrot6;
	trelrot6.RotationX(-90 * ttpf * DEG_TO_RAD);
	this->_objects[7]->GetNode()->Rotation() *= trelrot6;

	int i = 0;
	for (auto it = this->_text_elems.begin(); it != this->_text_elems.end(); ++it)
	{
		TextActor* ttext = *(it);
		ttext->SetText(this->outputDebugMatrix(*this->_objects[i]));
		ttext->SetColor(this->_objects[i]->GetColor());
		ttext->GetNode()->Position() = this->_objects[i]->GetNode()->Position() + Vector3f(0, 15, 0);
		i++;
	}

	////----------2D Text Rendering-------------------------------------------------------
	Matrix4f ttextpos = Matrix4f::Identity();
	float tx = 30.0f;	float ty = 30.0f;
	static Vector4f twhiteclr(1.0f, 1.0f, 1.0f, 1.0f);
	static Vector4f tyellowclr(1.0f, 1.0f, 0.0f, 1.0f);

	ttextpos.SetTranslation(Vector3f(tx, ty, 0.0f));
	this->_render_text->writeText(this->outputDebugInfoAll(), ttextpos, twhiteclr);

	tx = this->_obj_window->GetWidth() - 400.0f;
	ty = 30.0f;
	ttextpos.SetTranslation(Vector3f(tx, ty, 0.0f));

	std::wstringstream tcurrobjout;
	tcurrobjout << "Object " << this->_curr_obj + 1 << " Matrix \n";
	std::wstring tmatrixtext = tcurrobjout.str();
	tmatrixtext.append(this->outputDebugMatrix(*this->_objects[this->_curr_obj]));
	tmatrixtext.append(L"\n");
	tmatrixtext.append(this->outputDebugTransform(*this->_objects[this->_curr_obj], Vector3f(0, 0, 0)));
	this->_render_text->writeText(tmatrixtext, ttextpos, tyellowclr);




	Matrix4f ttextposfps = Matrix4f::Identity();
	float fpstx = 60.0f;
	float fpsty = 30.0f;
	Vector4f twhiteclrfps(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4f tredclrfps(1.0f, 0.0f, 0.0f, 1.0f);

	ttextposfps.SetTranslation(Vector3f(fpsty, fpstx, 0.0f));
	this->_render_text->writeText(this->outputFPSInfo(), ttextposfps, twhiteclrfps);

	fpsty += 30;

	ttextposfps.SetTranslation(Vector3f(fpsty, fpstx, 0.0f));



	//-----------Scene Updates----------------------------------------------------------
	this->m_pScene->Update(m_pTimer->Elapsed());
	this->m_pScene->Render(this->_obj_renderer11);

	//--------END RENDERING-------------------------------------------------------------
	this->_obj_renderer11->Present(this->_obj_window->GetHandle(), this->_obj_window->GetSwapChain());

}


//-------------HELPER METHODS--------------------------------------------------

BasicMeshPtr LJMULevelDemo::generateOBJMesh(std::wstring pmeshname, Vector4f pmeshcolour)
{
	LJMUDX::LJMUMeshOBJ* tmesh = new LJMUDX::LJMUMeshOBJ(this->_fs.GetModelsFolder() + pmeshname);
	int tvertcount = tmesh->positions.size();

	auto tia = std::make_shared<DrawExecutorDX11<BasicVertexDX11::Vertex>>();
	tia->SetLayoutElements(BasicVertexDX11::GetElementCount(), BasicVertexDX11::Elements);
	tia->SetPrimitiveType(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	tia->SetMaxVertexCount(tvertcount);

	BasicVertexDX11::Vertex tv;
	tv.color = pmeshcolour;

	for (auto& tobject : tmesh->objects)
	{
		for (auto& tface : tobject.faces)
		{
			for (size_t i = 0; i < 3; ++i)
			{
				tv.position = tmesh->positions[tface.PositionIndices[i]];
				tv.normal = tmesh->normals[tface.NormalIndices[i]];
				tv.texcoords = tmesh->coords[tface.CoordIndices[i]];
				tia->AddVertex(tv);
			}
		}
	}
	return tia;
}





///////////////////////////////////
// Configure the DirectX 11 Programmable
// Pipeline Stages and Create the Window
// Calls 
///////////////////////////////////
bool LJMULevelDemo::ConfigureEngineComponents()
{
	// The application currently supplies the 
	int twidth = 1366;
	int theight = 768;

	// Set the render window parameters and initialize the window
	this->_obj_window = new Win32RenderWindow();
	this->_obj_window->SetPosition(25, 25);
	this->_obj_window->SetSize(twidth, theight);
	this->_obj_window->SetCaption(this->GetName());
	this->_obj_window->Initialize(this);


	// Create the renderer and initialize it for the desired device
	// type and feature level.
	this->_obj_renderer11 = new RendererDX11();

	if (!this->_obj_renderer11->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0))
	{
		Log::Get().Write(L"Could not create hardware device, trying to create the reference device...");

		if (!this->_obj_renderer11->Initialize(D3D_DRIVER_TYPE_REFERENCE, D3D_FEATURE_LEVEL_10_0))
		{
			ShowWindow(this->_obj_window->GetHandle(), SW_HIDE);
			MessageBox(this->_obj_window->GetHandle(), L"Could not create a hardware or software Direct3D 11 device!", L"5002 MATH - Session 05", MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
			this->RequestTermination();
			return(false);
		}
		// If using the reference device, utilize a fixed time step for any animations.
		this->m_pTimer->SetFixedTimeStep(1.0f / 10.0f);
	}

	// Create a swap chain for the window that we started out with.  This
	// demonstrates using a configuration object for fast and concise object
	// creation.
	SwapChainConfigDX11 tconfig;
	tconfig.SetWidth(this->_obj_window->GetWidth());
	tconfig.SetHeight(this->_obj_window->GetHeight());
	tconfig.SetOutputWindow(this->_obj_window->GetHandle());
	this->_swap_index = this->_obj_renderer11->CreateSwapChain(&tconfig);
	this->_obj_window->SetSwapChain(this->_swap_index);
	
	//Create Colour and Depth Buffers
	this->_tgt_render = this->_obj_renderer11->GetSwapChainResource(this->_swap_index);

	Texture2dConfigDX11 tdepthconfig;
	tdepthconfig.SetDepthBuffer(twidth, theight);
	this->_tgt_depth = this->_obj_renderer11->CreateTexture2D(&tdepthconfig, 0);

	// Bind the swap chain render target and the depth buffer for use in rendering.  
	this->_obj_renderer11->pImmPipeline->ClearRenderTargets();
	this->_obj_renderer11->pImmPipeline->OutputMergerStage.DesiredState.RenderTargetViews.SetState(0, this->_tgt_render->m_iResourceRTV);
	this->_obj_renderer11->pImmPipeline->OutputMergerStage.DesiredState.DepthTargetViews.SetState(this->_tgt_depth->m_iResourceDSV);
	this->_obj_renderer11->pImmPipeline->ApplyRenderTargets();

	D3D11_VIEWPORT tviewport;
	tviewport.Width = static_cast< float >(twidth);
	tviewport.Height = static_cast< float >(theight);
	tviewport.MinDepth = 0.0f;
	tviewport.MaxDepth = 1.0f;
	tviewport.TopLeftX = 0;
	tviewport.TopLeftY = 0;

	int tvpindex = this->_obj_renderer11->CreateViewPort(tviewport);
	this->_obj_renderer11->pImmPipeline->RasterizerStage.DesiredState.ViewportCount.SetState(1);
	this->_obj_renderer11->pImmPipeline->RasterizerStage.DesiredState.Viewports.SetState(0, tvpindex);
	return(true);
}

//////////////////////////////////
//Handle Input Events in the Application
//////////////////////////////////
bool LJMULevelDemo::HandleEvent(EventPtr pevent)
{
	/*eEVENT e = pevent->GetEventType();

	if (e == SYSTEM_KEYBOARD_KEYDOWN)
	{
		EvtKeyDownPtr tkey_down = std::static_pointer_cast<EvtKeyDown>(pevent);
		unsigned int  tkeycode = tkey_down->GetCharacterCode();
	}
	else if (e == SYSTEM_KEYBOARD_KEYUP)
	{
		EvtKeyUpPtr tkey_up = std::static_pointer_cast<EvtKeyUp>(pevent);
		unsigned int tkeycode = tkey_up->GetCharacterCode();
	}

	return(Application::HandleEvent(pevent));*/

	eEVENT e = pevent->GetEventType();

	if (e == SYSTEM_KEYBOARD_KEYDOWN)
	{
		EvtKeyDownPtr tkey_down = std::static_pointer_cast<EvtKeyDown>(pevent);
		unsigned int  tkeycode = tkey_down->GetCharacterCode();

		if (tkeycode == '2')
			this->_curr_obj++;
		if (this->_curr_obj >= this->_objects.size())
			this->_curr_obj = 0;

	}
	else if (e == SYSTEM_KEYBOARD_KEYUP)
	{
		EvtKeyUpPtr tkey_up = std::static_pointer_cast<EvtKeyUp>(pevent);
		unsigned int tkeycode = tkey_up->GetCharacterCode();
	}

	return(Application::HandleEvent(pevent));

}

//////////////////////////////////
// Destroy Resources created by the engine
//////////////////////////////////
void LJMULevelDemo::ShutdownEngineComponents()
{
	if (this->_obj_renderer11)
	{
		this->_obj_renderer11->Shutdown();
		delete this->_obj_renderer11;
	}

	if (this->_obj_window)
	{
		this->_obj_window->Shutdown();
		delete this->_obj_window;
	}
}

//////////////////////////////////
// Shutdown the Application
//////////////////////////////////
void LJMULevelDemo::Shutdown()
{
	//NOTHING TO DO HERE
}

//////////////////////////////////
// Take a Screenshot of the Application
//////////////////////////////////
void LJMULevelDemo::TakeScreenShot()
{
	if (this->m_bSaveScreenshot)
	{
		this->m_bSaveScreenshot = false;
		this->_obj_renderer11->pImmPipeline->SaveTextureScreenShot(0, this->GetName());
	}
}

//////////////////////////////////////
// Output our Frame Rate
//////////////////////////////////////
std::wstring LJMULevelDemo::outputFPSInfo()
{
	std::wstringstream out;
	out << L"FPS: " << m_pTimer->Framerate();
	return out.str();
}


/////////////////////////////////////////
// Output our Debug Information
/////////////////////////////////////////
std::wstring LJMULevelDemo::outputDebugInfo(const GeometryActor& pactor)
{
	std::wstringstream out;
	Vector3f ttrans = pactor.GetNode()->Position();
	Vector3f tscale = pactor.GetNode()->Scale();
	out << L"Translation: [ ";
	out << std::fixed;
	out.precision(2);
	out << ttrans.x << " " << ttrans.y << " " << ttrans.z;
	out << "] ";
	out << L"Scale [";
	out << tscale.x << " " << tscale.y << " " << tscale.x;
	out << "] ";
	out << L"Dist [" << ttrans.Magnitude() << "]";
	return out.str();
}

///////////////////////////////////////////
// Output our Debug World Matrix
///////////////////////////////////////////
std::wstring LJMULevelDemo::outputDebugMatrix(const GeometryActor& pactor)
{
	std::wstringstream out;
	Matrix4f twm = pactor.GetNode()->WorldMatrix();

	out << std::fixed << std::setprecision(2);
	out << std::setw(10) << twm[Matrix4f::m11] << std::setw(10) << twm[Matrix4f::m12]
		<< std::setw(10) << twm[Matrix4f::m13] << std::setw(10) << twm[Matrix4f::m14] << std::endl;
	out << std::setw(10) << twm[Matrix4f::m21] << std::setw(10) << twm[Matrix4f::m22]
		<< std::setw(10) << twm[Matrix4f::m23] << std::setw(10) << twm[Matrix4f::m24] << std::endl;
	out << std::setw(10) << twm[Matrix4f::m31] << std::setw(10) << twm[Matrix4f::m32]
		<< std::setw(10) << twm[Matrix4f::m33] << std::setw(10) << twm[Matrix4f::m34] << std::endl;
	out << std::setw(10) << twm[Matrix4f::m41] << std::setw(10) << twm[Matrix4f::m42]
		<< std::setw(10) << twm[Matrix4f::m43] << std::setw(10) << twm[Matrix4f::m44] << std::endl;
	return out.str();
}



std::wstring LJMULevelDemo::outputDebugTransform(const Matrix4f& pmatrix, Vector3f ppoint)
{
	std::wstringstream out;
	Vector4f tvector;

	//Calculate our Transformed Homogenous Vector using
	//Matrix Multiplication (our Vector is a Row Vector, so use
	//Column Matrix Multiplication)
	tvector.x = (ppoint.x * pmatrix[0]) + (ppoint.y * pmatrix[4])
		+ (ppoint.z * pmatrix[8]) + (1 * pmatrix[12]);

	tvector.y = (ppoint.x * pmatrix[1]) + (ppoint.y * pmatrix[5])
		+ (ppoint.z * pmatrix[9]) + (1 * pmatrix[13]);

	tvector.z = (ppoint.x * pmatrix[2]) + (ppoint.y * pmatrix[6])
		+ (ppoint.z * pmatrix[10]) + (1 * pmatrix[14]);

	tvector.w = (ppoint.x * pmatrix[3]) + (ppoint.y * pmatrix[7])
		+ (ppoint.z * pmatrix[11]) + (1 * pmatrix[15]);

	//Output the Transformed Vector
	out << std::fixed << std::setprecision(2);
	out << L"[";
	out << tvector.x << " " << tvector.y << " " << tvector.z;
	out << "]";
	//Return the Formatted String
	return out.str();
}

///////////////////////////////////
// Transform the given point,by the
// given Actor's World Matrix.
///////////////////////////////////
std::wstring LJMULevelDemo::outputDebugTransform(const GeometryActor& pobject, Vector3f ppoint)
{
	return this->outputDebugTransform(pobject.GetNode()->WorldMatrix(), ppoint);
}

/////////////////////////////////////////
// Output our Debug Information
/////////////////////////////////////////
std::wstring LJMULevelDemo::outputDebugInfoAll()
{
	std::wstringstream out;

	int i = 1;
	//for 
		auto it = this->_objects.begin(); it != this->_objects.end(); /*++it*/
	{
		GeometryActor* pactor = *it;
		Vector3f ttrans = pactor->GetNode()->Position();
		Vector3f tscale = pactor->GetNode()->Scale();
		out << "Object " << i << ": ";
		out << L"Translation: [ ";
		out << std::fixed;
		out.precision(2);
		out << ttrans.x << " " << ttrans.y << " " << ttrans.z;
		out << "] ";
		out << L"Scale [";
		out << tscale.x << " " << tscale.y << " " << tscale.x;
		out << "] ";
		out << L"Dist [" << ttrans.Magnitude() << "]";
		out << std::endl;
		i;
	}
	return out.str();
}
