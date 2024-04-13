#pragma once

struct RenderContext {
	float m_ClearColor[4];
	float m_window_width;
	float m_window_height;
	float m_nearPlane_z;
	float m_farPlane_z;

	RenderContext(float clearColor[4], float window_width, float window_height, float nearPlane_z, float farPlane_z)
		: m_ClearColor{ clearColor[0],clearColor[1],clearColor[2],clearColor[3] }
		, m_window_width(window_width)
		, m_window_height(window_height)
		, m_nearPlane_z(nearPlane_z)
		, m_farPlane_z(farPlane_z)
	{


	}
};
