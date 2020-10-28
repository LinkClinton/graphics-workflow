#ifndef __WORKFLOW_SHADERS_FILE_HPP__
#define __WORKFLOW_SHADERS_FILE_HPP__

#include <vector>

namespace workflows::shaders {

	inline const std::vector<unsigned char> workflow_line_vert_shader = { 68, 88, 66, 67, 119, 117, 69, 89, 49, 84, 82, 78, 54, 109, 218, 182, 24, 241, 208, 203, 1, 0, 0, 0, 248, 3, 0, 0, 5, 0, 0, 0, 52, 0, 0, 0, 124, 1, 0, 0, 204, 1, 0, 0, 32, 2, 0, 0, 92, 3, 0, 0, 82, 68, 69, 70, 64, 1, 0, 0, 1, 0, 0, 0, 108, 0, 0, 0, 1, 0, 0, 0, 60, 0, 0, 0, 1, 5, 254, 255, 0, 5, 0, 0, 24, 1, 0, 0, 19, 19, 68, 37, 60, 0, 0, 0, 24, 0, 0, 0, 40, 0, 0, 0, 40, 0, 0, 0, 36, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 118, 105, 101, 119, 0, 171, 171, 171, 100, 0, 0, 0, 1, 0, 0, 0, 132, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 2, 0, 0, 0, 244, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 118, 105, 101, 119, 95, 109, 97, 116, 114, 105, 120, 0, 102, 108, 111, 97, 116, 52, 120, 52, 0, 171, 171, 171, 3, 0, 3, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 184, 0, 0, 0, 100, 0, 0, 0, 196, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1, 0, 16, 0, 0, 0, 1, 0, 232, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 172, 0, 0, 0, 77, 105, 99, 114, 111, 115, 111, 102, 116, 32, 40, 82, 41, 32, 72, 76, 83, 76, 32, 83, 104, 97, 100, 101, 114, 32, 67, 111, 109, 112, 105, 108, 101, 114, 32, 49, 48, 46, 49, 0, 73, 83, 71, 78, 72, 0, 0, 0, 2, 0, 0, 0, 8, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 15, 15, 0, 0, 80, 79, 83, 73, 84, 73, 79, 78, 0, 67, 79, 76, 79, 82, 0, 171, 79, 83, 71, 78, 76, 0, 0, 0, 2, 0, 0, 0, 8, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 15, 0, 0, 0, 83, 86, 95, 80, 79, 83, 73, 84, 73, 79, 78, 0, 67, 79, 76, 79, 82, 0, 171, 171, 83, 72, 69, 88, 52, 1, 0, 0, 81, 0, 1, 0, 77, 0, 0, 0, 106, 8, 0, 1, 89, 0, 0, 7, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 95, 0, 0, 3, 114, 16, 16, 0, 0, 0, 0, 0, 95, 0, 0, 3, 242, 16, 16, 0, 1, 0, 0, 0, 103, 0, 0, 4, 242, 32, 16, 0, 0, 0, 0, 0, 1, 0, 0, 0, 101, 0, 0, 3, 242, 32, 16, 0, 1, 0, 0, 0, 104, 0, 0, 2, 1, 0, 0, 0, 54, 0, 0, 5, 114, 0, 16, 0, 0, 0, 0, 0, 70, 18, 16, 0, 0, 0, 0, 0, 54, 0, 0, 5, 130, 0, 16, 0, 0, 0, 0, 0, 1, 64, 0, 0, 0, 0, 128, 63, 17, 0, 0, 9, 18, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 0, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 9, 34, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 0, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 17, 0, 0, 9, 66, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 0, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 17, 0, 0, 9, 130, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 0, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 54, 0, 0, 5, 242, 32, 16, 0, 1, 0, 0, 0, 70, 30, 16, 0, 1, 0, 0, 0, 62, 0, 0, 1, 83, 84, 65, 84, 148, 0, 0, 0, 8, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline const std::vector<unsigned char> workflow_line_frag_shader = { 68, 88, 66, 67, 139, 86, 105, 107, 57, 130, 82, 163, 77, 145, 206, 125, 154, 242, 128, 84, 1, 0, 0, 0, 8, 2, 0, 0, 5, 0, 0, 0, 52, 0, 0, 0, 160, 0, 0, 0, 244, 0, 0, 0, 40, 1, 0, 0, 108, 1, 0, 0, 82, 68, 69, 70, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 1, 5, 255, 255, 0, 5, 0, 0, 60, 0, 0, 0, 19, 19, 68, 37, 60, 0, 0, 0, 24, 0, 0, 0, 40, 0, 0, 0, 40, 0, 0, 0, 36, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 77, 105, 99, 114, 111, 115, 111, 102, 116, 32, 40, 82, 41, 32, 72, 76, 83, 76, 32, 83, 104, 97, 100, 101, 114, 32, 67, 111, 109, 112, 105, 108, 101, 114, 32, 49, 48, 46, 49, 0, 73, 83, 71, 78, 76, 0, 0, 0, 2, 0, 0, 0, 8, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 15, 15, 0, 0, 83, 86, 95, 80, 79, 83, 73, 84, 73, 79, 78, 0, 67, 79, 76, 79, 82, 0, 171, 171, 79, 83, 71, 78, 44, 0, 0, 0, 1, 0, 0, 0, 8, 0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 83, 86, 95, 84, 65, 82, 71, 69, 84, 0, 171, 171, 83, 72, 69, 88, 60, 0, 0, 0, 81, 0, 0, 0, 15, 0, 0, 0, 106, 8, 0, 1, 98, 16, 0, 3, 242, 16, 16, 0, 1, 0, 0, 0, 101, 0, 0, 3, 242, 32, 16, 0, 0, 0, 0, 0, 54, 0, 0, 5, 242, 32, 16, 0, 0, 0, 0, 0, 70, 30, 16, 0, 1, 0, 0, 0, 62, 0, 0, 1, 83, 84, 65, 84, 148, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline const std::vector<unsigned char> workflow_wireframe_vert_shader = { 68, 88, 66, 67, 195, 130, 41, 59, 189, 70, 242, 77, 144, 61, 228, 137, 134, 52, 147, 122, 1, 0, 0, 0, 68, 7, 0, 0, 5, 0, 0, 0, 52, 0, 0, 0, 216, 2, 0, 0, 48, 3, 0, 0, 136, 3, 0, 0, 168, 6, 0, 0, 82, 68, 69, 70, 156, 2, 0, 0, 2, 0, 0, 0, 160, 0, 0, 0, 2, 0, 0, 0, 60, 0, 0, 0, 1, 5, 254, 255, 0, 5, 0, 0, 116, 2, 0, 0, 19, 19, 68, 37, 60, 0, 0, 0, 24, 0, 0, 0, 40, 0, 0, 0, 40, 0, 0, 0, 36, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 140, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 151, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 116, 114, 97, 110, 115, 102, 111, 114, 109, 115, 0, 99, 111, 110, 102, 105, 103, 0, 171, 171, 151, 0, 0, 0, 1, 0, 0, 0, 208, 0, 0, 0, 144, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 140, 0, 0, 0, 1, 0, 0, 0, 204, 1, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 151, 0, 0, 0, 0, 0, 0, 0, 132, 0, 0, 0, 2, 0, 0, 0, 168, 1, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 115, 104, 97, 100, 101, 114, 95, 99, 111, 110, 102, 105, 103, 0, 118, 105, 101, 119, 95, 109, 97, 116, 114, 105, 120, 0, 102, 108, 111, 97, 116, 52, 120, 52, 0, 171, 3, 0, 3, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 1, 0, 0, 112, 114, 111, 106, 95, 109, 97, 116, 114, 105, 120, 0, 105, 110, 115, 116, 97, 110, 99, 101, 95, 98, 97, 115, 101, 0, 100, 119, 111, 114, 100, 0, 0, 0, 19, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, 1, 0, 0, 6, 1, 0, 0, 28, 1, 0, 0, 0, 0, 0, 0, 64, 1, 0, 0, 28, 1, 0, 0, 64, 0, 0, 0, 76, 1, 0, 0, 96, 1, 0, 0, 128, 0, 0, 0, 5, 0, 0, 0, 1, 0, 33, 0, 0, 0, 3, 0, 132, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 0, 0, 0, 244, 1, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 2, 0, 0, 0, 80, 2, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 36, 69, 108, 101, 109, 101, 110, 116, 0, 115, 104, 97, 100, 101, 114, 95, 116, 114, 97, 110, 115, 102, 111, 114, 109, 115, 0, 108, 111, 99, 97, 108, 95, 116, 111, 95, 119, 111, 114, 108, 100, 0, 171, 171, 3, 0, 3, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 1, 0, 0, 15, 2, 0, 0, 32, 2, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1, 0, 16, 0, 0, 0, 1, 0, 68, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 253, 1, 0, 0, 77, 105, 99, 114, 111, 115, 111, 102, 116, 32, 40, 82, 41, 32, 72, 76, 83, 76, 32, 83, 104, 97, 100, 101, 114, 32, 67, 111, 109, 112, 105, 108, 101, 114, 32, 49, 48, 46, 49, 0, 73, 83, 71, 78, 80, 0, 0, 0, 2, 0, 0, 0, 8, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 80, 79, 83, 73, 84, 73, 79, 78, 0, 83, 86, 95, 73, 110, 115, 116, 97, 110, 99, 101, 73, 68, 0, 171, 79, 83, 71, 78, 80, 0, 0, 0, 2, 0, 0, 0, 8, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 14, 0, 0, 83, 86, 95, 80, 79, 83, 73, 84, 73, 79, 78, 0, 73, 100, 101, 110, 116, 105, 116, 121, 0, 171, 171, 171, 83, 72, 69, 88, 24, 3, 0, 0, 81, 0, 1, 0, 198, 0, 0, 0, 106, 8, 0, 1, 89, 0, 0, 7, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 1, 0, 0, 0, 162, 0, 0, 7, 70, 126, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 95, 0, 0, 3, 114, 16, 16, 0, 0, 0, 0, 0, 96, 0, 0, 4, 18, 16, 16, 0, 1, 0, 0, 0, 8, 0, 0, 0, 103, 0, 0, 4, 242, 32, 16, 0, 0, 0, 0, 0, 1, 0, 0, 0, 101, 0, 0, 3, 18, 32, 16, 0, 1, 0, 0, 0, 104, 0, 0, 2, 6, 0, 0, 0, 30, 0, 0, 9, 18, 0, 16, 0, 0, 0, 0, 0, 10, 16, 16, 0, 1, 0, 0, 0, 10, 128, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 167, 0, 0, 10, 242, 0, 16, 0, 1, 0, 0, 0, 10, 0, 16, 0, 0, 0, 0, 0, 1, 64, 0, 0, 0, 0, 0, 0, 70, 126, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 167, 0, 0, 10, 242, 0, 16, 0, 2, 0, 0, 0, 10, 0, 16, 0, 0, 0, 0, 0, 1, 64, 0, 0, 16, 0, 0, 0, 70, 126, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 167, 0, 0, 10, 242, 0, 16, 0, 3, 0, 0, 0, 10, 0, 16, 0, 0, 0, 0, 0, 1, 64, 0, 0, 32, 0, 0, 0, 70, 126, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 167, 0, 0, 10, 242, 0, 16, 0, 4, 0, 0, 0, 10, 0, 16, 0, 0, 0, 0, 0, 1, 64, 0, 0, 48, 0, 0, 0, 70, 126, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 5, 114, 0, 16, 0, 5, 0, 0, 0, 70, 18, 16, 0, 0, 0, 0, 0, 54, 0, 0, 5, 130, 0, 16, 0, 5, 0, 0, 0, 1, 64, 0, 0, 0, 0, 128, 63, 17, 0, 0, 7, 18, 0, 16, 0, 1, 0, 0, 0, 70, 14, 16, 0, 5, 0, 0, 0, 70, 14, 16, 0, 1, 0, 0, 0, 17, 0, 0, 7, 34, 0, 16, 0, 1, 0, 0, 0, 70, 14, 16, 0, 5, 0, 0, 0, 70, 14, 16, 0, 2, 0, 0, 0, 17, 0, 0, 7, 66, 0, 16, 0, 1, 0, 0, 0, 70, 14, 16, 0, 5, 0, 0, 0, 70, 14, 16, 0, 3, 0, 0, 0, 17, 0, 0, 7, 130, 0, 16, 0, 1, 0, 0, 0, 70, 14, 16, 0, 5, 0, 0, 0, 70, 14, 16, 0, 4, 0, 0, 0, 17, 0, 0, 9, 18, 0, 16, 0, 2, 0, 0, 0, 70, 14, 16, 0, 1, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 9, 34, 0, 16, 0, 2, 0, 0, 0, 70, 14, 16, 0, 1, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 17, 0, 0, 9, 66, 0, 16, 0, 2, 0, 0, 0, 70, 14, 16, 0, 1, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 17, 0, 0, 9, 130, 0, 16, 0, 2, 0, 0, 0, 70, 14, 16, 0, 1, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 17, 0, 0, 9, 18, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 2, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 17, 0, 0, 9, 34, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 2, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 17, 0, 0, 9, 66, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 2, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 17, 0, 0, 9, 130, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 2, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 54, 0, 0, 5, 18, 32, 16, 0, 1, 0, 0, 0, 10, 0, 16, 0, 0, 0, 0, 0, 62, 0, 0, 1, 83, 84, 65, 84, 148, 0, 0, 0, 21, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 12, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline const std::vector<unsigned char> workflow_wireframe_frag_shader = { 68, 88, 66, 67, 64, 197, 18, 200, 131, 152, 89, 235, 234, 205, 71, 220, 69, 145, 67, 201, 1, 0, 0, 0, 36, 3, 0, 0, 5, 0, 0, 0, 52, 0, 0, 0, 136, 1, 0, 0, 224, 1, 0, 0, 20, 2, 0, 0, 136, 2, 0, 0, 82, 68, 69, 70, 76, 1, 0, 0, 1, 0, 0, 0, 108, 0, 0, 0, 1, 0, 0, 0, 60, 0, 0, 0, 1, 5, 255, 255, 0, 5, 0, 0, 36, 1, 0, 0, 19, 19, 68, 37, 60, 0, 0, 0, 24, 0, 0, 0, 40, 0, 0, 0, 40, 0, 0, 0, 36, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 16, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 111, 108, 111, 114, 115, 0, 171, 100, 0, 0, 0, 1, 0, 0, 0, 132, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 172, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 36, 69, 108, 101, 109, 101, 110, 116, 0, 115, 104, 97, 100, 101, 114, 95, 99, 111, 108, 111, 114, 115, 0, 99, 111, 108, 111, 114, 0, 102, 108, 111, 97, 116, 52, 0, 1, 0, 3, 0, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 201, 0, 0, 0, 195, 0, 0, 0, 208, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1, 0, 4, 0, 0, 0, 1, 0, 244, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 181, 0, 0, 0, 77, 105, 99, 114, 111, 115, 111, 102, 116, 32, 40, 82, 41, 32, 72, 76, 83, 76, 32, 83, 104, 97, 100, 101, 114, 32, 67, 111, 109, 112, 105, 108, 101, 114, 32, 49, 48, 46, 49, 0, 73, 83, 71, 78, 80, 0, 0, 0, 2, 0, 0, 0, 8, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 83, 86, 95, 80, 79, 83, 73, 84, 73, 79, 78, 0, 73, 100, 101, 110, 116, 105, 116, 121, 0, 171, 171, 171, 79, 83, 71, 78, 44, 0, 0, 0, 1, 0, 0, 0, 8, 0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 83, 86, 95, 84, 65, 82, 71, 69, 84, 0, 171, 171, 83, 72, 69, 88, 108, 0, 0, 0, 81, 0, 0, 0, 27, 0, 0, 0, 106, 8, 0, 1, 162, 0, 0, 7, 70, 126, 48, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 98, 8, 0, 3, 18, 16, 16, 0, 1, 0, 0, 0, 101, 0, 0, 3, 242, 32, 16, 0, 0, 0, 0, 0, 167, 0, 0, 10, 242, 32, 16, 0, 0, 0, 0, 0, 10, 16, 16, 0, 1, 0, 0, 0, 1, 64, 0, 0, 0, 0, 0, 0, 70, 126, 32, 0, 0, 0, 0, 0, 1, 0, 0, 0, 62, 0, 0, 1, 83, 84, 65, 84, 148, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline const std::vector<unsigned char> workflow_filled_circle_vert_shader = { 68, 88, 66, 67, 91, 140, 5, 208, 14, 170, 194, 233, 87, 235, 208, 55, 189, 84, 107, 50, 1, 0, 0, 0, 52, 6, 0, 0, 5, 0, 0, 0, 52, 0, 0, 0, 124, 2, 0, 0, 212, 2, 0, 0, 44, 3, 0, 0, 152, 5, 0, 0, 82, 68, 69, 70, 64, 2, 0, 0, 2, 0, 0, 0, 160, 0, 0, 0, 2, 0, 0, 0, 60, 0, 0, 0, 1, 5, 254, 255, 0, 5, 0, 0, 24, 2, 0, 0, 19, 19, 68, 37, 60, 0, 0, 0, 24, 0, 0, 0, 40, 0, 0, 0, 40, 0, 0, 0, 36, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 140, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 151, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 116, 114, 97, 110, 115, 102, 111, 114, 109, 115, 0, 99, 111, 110, 102, 105, 103, 0, 171, 171, 151, 0, 0, 0, 1, 0, 0, 0, 208, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 140, 0, 0, 0, 1, 0, 0, 0, 112, 1, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 151, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 2, 0, 0, 0, 76, 1, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 115, 104, 97, 100, 101, 114, 95, 99, 111, 110, 102, 105, 103, 0, 118, 105, 101, 119, 95, 109, 97, 116, 114, 105, 120, 0, 102, 108, 111, 97, 116, 52, 120, 52, 0, 171, 3, 0, 3, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 1, 0, 0, 6, 1, 0, 0, 28, 1, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1, 0, 16, 0, 0, 0, 1, 0, 64, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 0, 0, 0, 152, 1, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 2, 0, 0, 0, 244, 1, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 36, 69, 108, 101, 109, 101, 110, 116, 0, 115, 104, 97, 100, 101, 114, 95, 116, 114, 97, 110, 115, 102, 111, 114, 109, 115, 0, 108, 111, 99, 97, 108, 95, 116, 111, 95, 119, 111, 114, 108, 100, 0, 171, 171, 3, 0, 3, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 1, 0, 0, 179, 1, 0, 0, 196, 1, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1, 0, 16, 0, 0, 0, 1, 0, 232, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 161, 1, 0, 0, 77, 105, 99, 114, 111, 115, 111, 102, 116, 32, 40, 82, 41, 32, 72, 76, 83, 76, 32, 83, 104, 97, 100, 101, 114, 32, 67, 111, 109, 112, 105, 108, 101, 114, 32, 49, 48, 46, 49, 0, 73, 83, 71, 78, 80, 0, 0, 0, 2, 0, 0, 0, 8, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 80, 79, 83, 73, 84, 73, 79, 78, 0, 83, 86, 95, 73, 110, 115, 116, 97, 110, 99, 101, 73, 68, 0, 171, 79, 83, 71, 78, 80, 0, 0, 0, 2, 0, 0, 0, 8, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 14, 0, 0, 83, 86, 95, 80, 79, 83, 73, 84, 73, 79, 78, 0, 73, 100, 101, 110, 116, 105, 116, 121, 0, 171, 171, 171, 83, 72, 69, 88, 100, 2, 0, 0, 81, 0, 1, 0, 153, 0, 0, 0, 106, 8, 0, 1, 89, 0, 0, 7, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 162, 0, 0, 7, 70, 126, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 95, 0, 0, 3, 114, 16, 16, 0, 0, 0, 0, 0, 96, 0, 0, 4, 18, 16, 16, 0, 1, 0, 0, 0, 8, 0, 0, 0, 103, 0, 0, 4, 242, 32, 16, 0, 0, 0, 0, 0, 1, 0, 0, 0, 101, 0, 0, 3, 18, 32, 16, 0, 1, 0, 0, 0, 104, 0, 0, 2, 5, 0, 0, 0, 167, 0, 0, 10, 242, 0, 16, 0, 0, 0, 0, 0, 10, 16, 16, 0, 1, 0, 0, 0, 1, 64, 0, 0, 0, 0, 0, 0, 70, 126, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 167, 0, 0, 10, 242, 0, 16, 0, 1, 0, 0, 0, 10, 16, 16, 0, 1, 0, 0, 0, 1, 64, 0, 0, 16, 0, 0, 0, 70, 126, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 167, 0, 0, 10, 242, 0, 16, 0, 2, 0, 0, 0, 10, 16, 16, 0, 1, 0, 0, 0, 1, 64, 0, 0, 32, 0, 0, 0, 70, 126, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 167, 0, 0, 10, 242, 0, 16, 0, 3, 0, 0, 0, 10, 16, 16, 0, 1, 0, 0, 0, 1, 64, 0, 0, 48, 0, 0, 0, 70, 126, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 5, 114, 0, 16, 0, 4, 0, 0, 0, 70, 18, 16, 0, 0, 0, 0, 0, 54, 0, 0, 5, 130, 0, 16, 0, 4, 0, 0, 0, 1, 64, 0, 0, 0, 0, 128, 63, 17, 0, 0, 7, 18, 0, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 4, 0, 0, 0, 70, 14, 16, 0, 0, 0, 0, 0, 17, 0, 0, 7, 34, 0, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 4, 0, 0, 0, 70, 14, 16, 0, 1, 0, 0, 0, 17, 0, 0, 7, 66, 0, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 4, 0, 0, 0, 70, 14, 16, 0, 2, 0, 0, 0, 17, 0, 0, 7, 130, 0, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 4, 0, 0, 0, 70, 14, 16, 0, 3, 0, 0, 0, 17, 0, 0, 9, 18, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 0, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 9, 34, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 0, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 17, 0, 0, 9, 66, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 0, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 17, 0, 0, 9, 130, 32, 16, 0, 0, 0, 0, 0, 70, 14, 16, 0, 0, 0, 0, 0, 70, 142, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 54, 0, 0, 5, 18, 32, 16, 0, 1, 0, 0, 0, 10, 16, 16, 0, 1, 0, 0, 0, 62, 0, 0, 1, 83, 84, 65, 84, 148, 0, 0, 0, 16, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline const std::vector<unsigned char> workflow_filled_circle_frag_shader = { 68, 88, 66, 67, 64, 197, 18, 200, 131, 152, 89, 235, 234, 205, 71, 220, 69, 145, 67, 201, 1, 0, 0, 0, 36, 3, 0, 0, 5, 0, 0, 0, 52, 0, 0, 0, 136, 1, 0, 0, 224, 1, 0, 0, 20, 2, 0, 0, 136, 2, 0, 0, 82, 68, 69, 70, 76, 1, 0, 0, 1, 0, 0, 0, 108, 0, 0, 0, 1, 0, 0, 0, 60, 0, 0, 0, 1, 5, 255, 255, 0, 5, 0, 0, 36, 1, 0, 0, 19, 19, 68, 37, 60, 0, 0, 0, 24, 0, 0, 0, 40, 0, 0, 0, 40, 0, 0, 0, 36, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 16, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 111, 108, 111, 114, 115, 0, 171, 100, 0, 0, 0, 1, 0, 0, 0, 132, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 172, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 36, 69, 108, 101, 109, 101, 110, 116, 0, 115, 104, 97, 100, 101, 114, 95, 99, 111, 108, 111, 114, 115, 0, 99, 111, 108, 111, 114, 0, 102, 108, 111, 97, 116, 52, 0, 1, 0, 3, 0, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 201, 0, 0, 0, 195, 0, 0, 0, 208, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1, 0, 4, 0, 0, 0, 1, 0, 244, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 181, 0, 0, 0, 77, 105, 99, 114, 111, 115, 111, 102, 116, 32, 40, 82, 41, 32, 72, 76, 83, 76, 32, 83, 104, 97, 100, 101, 114, 32, 67, 111, 109, 112, 105, 108, 101, 114, 32, 49, 48, 46, 49, 0, 73, 83, 71, 78, 80, 0, 0, 0, 2, 0, 0, 0, 8, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 68, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 83, 86, 95, 80, 79, 83, 73, 84, 73, 79, 78, 0, 73, 100, 101, 110, 116, 105, 116, 121, 0, 171, 171, 171, 79, 83, 71, 78, 44, 0, 0, 0, 1, 0, 0, 0, 8, 0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 83, 86, 95, 84, 65, 82, 71, 69, 84, 0, 171, 171, 83, 72, 69, 88, 108, 0, 0, 0, 81, 0, 0, 0, 27, 0, 0, 0, 106, 8, 0, 1, 162, 0, 0, 7, 70, 126, 48, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 98, 8, 0, 3, 18, 16, 16, 0, 1, 0, 0, 0, 101, 0, 0, 3, 242, 32, 16, 0, 0, 0, 0, 0, 167, 0, 0, 10, 242, 32, 16, 0, 0, 0, 0, 0, 10, 16, 16, 0, 1, 0, 0, 0, 1, 64, 0, 0, 0, 0, 0, 0, 70, 126, 32, 0, 0, 0, 0, 0, 1, 0, 0, 0, 62, 0, 0, 1, 83, 84, 65, 84, 148, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

}

#endif

