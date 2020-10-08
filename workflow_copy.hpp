#pragma once

#include <directx12-wrapper/resources/texture2d.hpp>
#include <directx12-wrapper/resources/buffer.hpp>
#include <directx12-wrapper/resources/buffer.hpp>

#include "cores/workflow_independent.hpp"

using namespace wrapper;

namespace workflows {

	using namespace cores;
	
	struct CpuMemory {};
	struct GpuUpload {};
	struct GpuTexture2D {};

	template <typename CopyFrom, typename CopyTo>
	struct CopyWorkflowInput;

	template <typename CopyFrom, typename CopyTo>
	struct CopyWorkflowOutput;

	template <>
	struct CopyWorkflowInput<CpuMemory, GpuUpload> {
		directx12::buffer upload;

		size_t size_in_bytes = 0;

		void* data = nullptr;
	};

	template <>
	struct CopyWorkflowInput<GpuUpload, GpuTexture2D> {
		directx12::graphics_command_list command_list;
		directx12::texture2d destination;
		directx12::buffer source;
	};

	template <>
	struct CopyWorkflowInput<CpuMemory, GpuTexture2D> {
		directx12::graphics_command_list command_list;
		directx12::texture2d destination;
		directx12::buffer upload;
		
		size_t size_in_bytes = 0;
		
		void* data = nullptr;
	};

	template <>
	struct CopyWorkflowOutput<CpuMemory, GpuUpload> {};
	
	template <>
	struct CopyWorkflowOutput<GpuUpload, GpuTexture2D> {};

	template <>
	struct CopyWorkflowOutput<CpuMemory, GpuTexture2D> {};

	template <typename CopyFrom, typename CopyTo>
	class CopyWorkflow final : public IndependentWorkflow<
		CopyWorkflowInput<CopyFrom, CopyTo>, CopyWorkflowOutput<CopyFrom, CopyTo>>
	{
	public:
		CopyWorkflow() = default;

		~CopyWorkflow() = default;

		using output_type = CopyWorkflowOutput<CopyFrom, CopyTo>;
		using input_type = CopyWorkflowInput<CopyFrom, CopyTo>;

		output_type start(const input_type& input) const override;
	};

	template <>
	inline CopyWorkflow<CpuMemory, GpuUpload>::output_type CopyWorkflow<CpuMemory, GpuUpload>::start(
		const input_type& input) const
	{
		assert(input.data != nullptr && input.size_in_bytes != 0);

		input.upload.copy_from_cpu(input.data, input.size_in_bytes);

		return {};
	}

	template <>
	inline CopyWorkflow<GpuUpload, GpuTexture2D>::output_type CopyWorkflow<GpuUpload, GpuTexture2D>::start(
		const input_type& input) const
	{
		assert(input.source.size_in_bytes() >= input.destination.height() * input.destination.alignment());

		input.destination.copy_from(input.command_list, input.source);

		return {};
	}

	template <>
	inline CopyWorkflow<CpuMemory, GpuTexture2D>::output_type CopyWorkflow<CpuMemory, GpuTexture2D>::start(
		const input_type& input) const
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
