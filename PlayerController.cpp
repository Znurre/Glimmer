#include "PlayerController.h"
#include "IInputMethod.h"

PlayerController::PlayerController(const QColor &color, IInputMethod *inputMethod)
	: m_color(color)
	, m_inputMethod(inputMethod)
	, m_ready(false)
{
}

PlayerController::~PlayerController()
{
	delete m_inputMethod;
}

QColor PlayerController::color() const
{
	return m_color;
}

IInputMethod *PlayerController::inputMethod() const
{
	return m_inputMethod;
}

void PlayerController::toggleReady()
{
	m_ready = !m_ready;
}

bool PlayerController::isReady() const
{
	return m_ready;
}
