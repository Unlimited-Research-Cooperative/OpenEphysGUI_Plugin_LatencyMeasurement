

#include <PluginInfo.h>

#include "LatencyMeasurement.h"
#include <string>

#ifdef WIN32
#include <Windows.h>
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

using namespace Plugin;

#define NUM_PLUGINS 1

extern "C" EXPORT void getLibInfo(Plugin::LibraryInfo* info)
{
	/* API version, defined by the GUI source.
	Should not be changed to ensure it is always equal to the one used in the latest codebase.
	The GUI refueses to load plugins with mismatched API versions */
	info->apiVersion = PLUGIN_API_VER;
	info->name = "Latency Measurement"; // <---- update
	info->libVersion = "0.1.0"; // <---- update
	info->numPlugins = NUM_PLUGINS;
}

extern "C" EXPORT int getPluginInfo(int index, Plugin::PluginInfo* info)
{
	switch (index)
	{
		//one case per plugin. This example is for a processor which connects directly to the signal chain
	case 0:
		//Type of plugin. See "Source/Processors/PluginManager/OpenEphysPlugin.h" for complete info about the different type structures
		info->type = Plugin::Type::PROCESSOR;

		//Processor name
		info->processor.name = "Latency Measurement"; //Processor name shown in the GUI

		//Type of processor. Can be FILTER, SOURCE, SINK or UTILITY. Specifies where on the processor list will appear
		info->processor.type = Processor::Type::FILTER;

		//Class factory pointer. Replace "ProcessorPluginSpace::ProcessorPlugin" with the namespace and class name.
		info->processor.creator = &(Plugin::createProcessor<LatencyMeasurement>);
		break;
	default:
		return -1;
		break;
	}
	return 0;
}

#ifdef WIN32
BOOL WINAPI DllMain(IN HINSTANCE hDllHandle,
	IN DWORD     nReason,
	IN LPVOID    Reserved)
{
	return TRUE;
}

#endif
