#include "workflow_lab2.hpp"

int main()
{
	workflows::labs::Lab2Workflow workflow({
		"lab2-workflow",
		800, 600
	});

	workflow.start({});
}