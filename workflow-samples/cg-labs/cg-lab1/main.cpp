#include "workflow_lab1.hpp"

int main()
{
	workflows::labs::Lab1Workflow workflow({
		"lab1-workflow",
		800, 600
	});

	workflow.start({});
}