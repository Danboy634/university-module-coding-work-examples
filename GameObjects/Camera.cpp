#include "Camera.h"

Camera::Camera()
{
	m_Active = true;
}

Camera::~Camera()
{
	RemoveCamera();
}

void Camera::Initialise()
{
	//playerPtr = new Player();
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	//Set m_View to the default view
	m_View = pWindowManager->GetWindow()->getDefaultView();
}

void Camera::Update()
{
}

void Camera::Update(int positionX, int positionY)
{
	m_View.setCenter(sf::Vector2f((float)positionX, (float)positionY));

	if (m_Active)
	{
		WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
		pWindowManager->GetWindow()->setView(m_View);
	}
}

void Camera::GetPosition(int& x, int& y)
{
	x = (int)m_View.getCenter().x;
	y = (int)m_View.getCenter().y;
}

void Camera::SetAsCurrentCamera()
{
	m_Active = true;
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	pWindowManager->GetWindow()->setView(m_View);
}

void Camera::RemoveCamera()
{
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	pWindowManager->GetWindow()->setView(pWindowManager->GetWindow()->getDefaultView());

	m_Active = false;
}
