#pragma once

struct RenderContext {
	float m_window_width;
	float m_window_height;
	float m_nearPlane_z;
	float m_farPlane_z;
	float m_pixels_per_unit;

	RenderContext(float window_width, float window_height, float nearPlane_z, float farPlane_z,float pixels_per_unit=100)
		:m_window_width(window_width),
		m_window_height(window_height),
		m_nearPlane_z(nearPlane_z),
		m_farPlane_z(farPlane_z),
		m_pixels_per_unit(pixels_per_unit)
	{


	}
};
