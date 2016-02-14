#include "Label.h"

void Label::draw()
{
	rgl::TextureManager::get()->draw(m_textureID, m_x, m_y, m_width, m_height);
}