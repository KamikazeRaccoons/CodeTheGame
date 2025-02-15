#include "ScriptEditor.h"

void ScriptEditor::update()
{
	if (rgl::InputHandler::get()->getMouseButtonState(rgl::InputHandler::LEFT))
	{
		std::shared_ptr<rgl::Vector2> pMousePos = rgl::InputHandler::get()->getMousePosition();

		bool shouldBeEnabled = pMousePos->getX() < (m_x + m_width) &&
			pMousePos->getX() >= m_x &&
			pMousePos->getY() < (m_y + m_height) &&
			pMousePos->getY() >= m_y ? true : false;
		
		if (m_enabled != shouldBeEnabled)
		{
			m_enabled = shouldBeEnabled;
			invalidate();
		}
	}
	
	if (m_enabled)
	{
		m_fa = 255;
		m_ba = 127;
	}
	else
	{
		m_fa = 127;
		m_ba = 63;
	}

	rgl::TextBox::update();
}

void ScriptEditor::draw()
{
	rgl::TextBox::draw();
}