#include "samples-workflow.hpp"

int main() {
	workflows::core::samples_workflow workflow({
		"samples-workflow",
		800, 600
	});
	
	workflow.start(workflows::core::null());
}