#include "clipping_rectangle.hpp"

#include "../../../references/directx-wrapper/directx12-wrapper/extensions/imgui.hpp"

void workflows::labs::ClippingRectangle::set_rectangle(float left, float top, float right, float bottom)
{
	mLeft = left; mTop = top; mRight = right; mBottom = bottom;
}

void workflows::labs::ClippingRectangle::draw_self(const vector4& color) const
{
	ImGui::GetBackgroundDrawList()->AddRect(
		ImVec2(mLeft, mTop), ImVec2(mRight, mBottom),
		ImColor(color.r, color.g, color.b, color.a)
	);
}

float workflows::labs::ClippingRectangle::left() const noexcept
{
	return mLeft;
}

float workflows::labs::ClippingRectangle::top() const noexcept
{
	return mTop;
}

float workflows::labs::ClippingRectangle::right() const noexcept
{
	return mRight;
}

float workflows::labs::ClippingRectangle::bottom() const noexcept
{
	return mBottom;
}
