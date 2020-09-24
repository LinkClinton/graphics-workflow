#pragma once

#include "../../../workflow-graphics/cores/workflow.hpp"

namespace workflows::labs {

	using namespace cores;
	
	class ClippingRectangle final {
	public:
		ClippingRectangle() = default;

		~ClippingRectangle() = default;

		void set_rectangle(float left, float top, float right, float bottom);
		
		void draw_self(const vector4& color) const;
		
		float left() const noexcept;

		float top() const noexcept;

		float right() const noexcept;

		float bottom() const noexcept;
	private:
		float mLeft = 0, mTop = 0, mRight = 0, mBottom = 0;
	};
	
}
