#include "workflow_samples.hpp"

int main() {
	workflows::samples::SamplesWorkflow workflow({
		"samples-workflow",
		800, 600
	});
	
	workflow.start(workflows::cores::null());
}