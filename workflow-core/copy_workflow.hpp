#pragma once

#include "../references/directx-wrapper/directx12-wrapper/resources/texture2d.hpp"
#include "../references/directx-wrapper/directx12-wrapper/resources/buffer.hpp"

#include "workflows/independent_workflow.hpp"

using namespace wrapper;

namespace workflows::copy {

	struct cpu_memory {};
	struct gpu_upload {};
	struct gpu_texture2d {};
	
	template <typename CopyFrom, typename CopyTo>
	class copy_workflow;

	template <typename CopyFrom, typename CopyTo>
	struct copy_workflow_input;

	template <typename CopyFrom, typename CopyTo>
	struct copy_workflow_output;

	template <>
	struct copy_workflow_input<cpu_memory, gpu_upload> {
		directx12::buffer upload;

		size_t size_in_bytes = 0;

		void* data = nullptr;
	};

	template <>
	struct copy_workflow_input<gpu_upload, gpu_texture2d> {
		directx12::graphics_command_list command_list;
		directx12::texture2d destination;
		directx12::buffer source;
	};

	template <>
	struct copy_workflow_input<cpu_memory, gpu_texture2d> {
		directx12::graphics_command_list command_list;
		directx12::texture2d destination;
		directx12::buffer upload;
		
		size_t size_in_bytes = 0;
		
		void* data = nullptr;
	};

	template <>
	struct copy_workflow_output<cpu_memory, gpu_upload> {};
	
	template <>
	struct copy_workflow_output<gpu_upload, gpu_texture2d> {};

	template <>
	struct copy_workflow_output<cpu_memory, gpu_texture2d> {};

	template <>
	class copy_workflow<cpu_memory, gpu_upload> final : public core::independent_workflow<
		copy_workflow_input<cpu_memory, gpu_upload>,
		copy_workflow_output<cpu_memory, gpu_upload>> {
	public:
		copy_workflow() = default;

		~copy_workflow() = default;

		copy_workflow_output<cpu_memory, gpu_upload> start(
			const copy_workflow_input<cpu_memory, gpu_upload>& input) const override;
	};

	template <>
	class copy_workflow<gpu_upload, gpu_texture2d> final : public core::independent_workflow<
		copy_workflow_input<gpu_upload, gpu_texture2d>,
		copy_workflow_output<gpu_upload, gpu_texture2d>> {
	public:
		copy_workflow() = default;

		~copy_workflow() = default;

		copy_workflow_output<gpu_upload, gpu_texture2d> start(
			const copy_workflow_input<gpu_upload, gpu_texture2d>& input) const override;
	};

	template <>
	class copy_workflow<cpu_memory, gpu_texture2d> final : public core::independent_workflow<
		copy_workflow_input<cpu_memory, gpu_texture2d>,
		copy_workflow_output<cpu_memory, gpu_texture2d>> {
	public:
		copy_workflow() = default;

		~copy_workflow() = default;

		copy_workflow_output<cpu_memory, gpu_texture2d> start(
			const copy_workflow_input<cpu_memory, gpu_texture2d>& input) const override;
	};
	
	inline copy_workflow_output<cpu_memory, gpu_upload> copy_workflow<cpu_memory, gpu_upload>::start(
		const copy_workflow_input<cpu_memory, gpu_upload>& input) const
	{
		assert(input.data != nullptr && input.size_in_bytes != 0);
		
		input.upload.copy_from_cpu(input.data, input.size_in_bytes);

		return {};
	}

	inline copy_workflow_output<gpu_upload, gpu_texture2d> copy_workflow<gpu_upload, gpu_texture2d>::start(
		const copy_workflow_input<gpu_upload, gpu_texture2d>& input) const
	{
		assert(input.source.size_in_bytes() >= input.destination.height() * input.destination.alignment());

		input.destination.copy_from(input.command_list, input.source);

		return {};
	}

	inline copy_workflow_output<cpu_memory, gpu_texture2d> copy_workflow<cpu_memory, gpu_texture2d>::start(
		const copy_workflow_input<cpu_memory, gpu_texture2d>& input) const
	{
		assert(input.data != nullptr && input.size_in_bytes != 0);
		assert(input.upload.size_in_bytes() >= input.size_in_bytes);

		const auto logic_width = input.destination.width() *
			directx12::size_of(input.destination.format());

		if (input.destination.alignment() == logic_width) 
			input.upload.copy_from_cpu(input.data, input.size_in_bytes);
		else {
			const auto upload_memory = static_cast<byte*>(input.upload.begin_mapping());
			const auto cpu_memory = static_cast<byte*>(input.data);
			const auto alignment = input.destination.alignment();

			for (size_t y = 0; y < input.destination.height(); y++) {
				std::memcpy(upload_memory + y * alignment, cpu_memory + y * logic_width,
					logic_width);
			}
			
			input.upload.end_mapping();
		}

		input.destination.copy_from(input.command_list, input.upload);

		return {};
	}

}
