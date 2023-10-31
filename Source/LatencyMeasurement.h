
#ifndef PROCESSORPLUGIN_H_DEFINED
#define PROCESSORPLUGIN_H_DEFINED

#include <ProcessorHeaders.h>


class ProcessorPlugin : public GenericProcessor
{

private:
    zmq::context_t context;
    zmq::socket_t socket;

public:
	/** The class constructor, used to initialize any members. */
	ProcessorPlugin();

	/** The class destructor, used to deallocate memory */
	~ProcessorPlugin();

	/** If the processor has a custom editor, this method must be defined to instantiate it. */
	AudioProcessorEditor* createEditor() override;

	/** Called every time the settings of an upstream plugin are changed.
		Allows the processor to handle variations in the channel configuration or any other parameter
		passed through signal chain. The processor can use this function to modify channel objects that
		will be passed to downstream plugins. */
	void updateSettings() override;

	/** Defines the functionality of the processor.
		The process method is called every time a new data buffer is available.
		Visualizer plugins typically use this method to send data to the canvas for display purposes */
	void process(AudioBuffer<float>& buffer) override;

	/** Handles events received by the processor
		Called automatically for each received event whenever checkForEvents() is called from
		the plugin's process() method */
	void handleTTLEvent(TTLEventPtr event) override;

	/** Handles spikes received by the processor
		Called automatically for each received spike whenever checkForEvents(true) is called from
		the plugin's process() method */
	void handleSpike(SpikePtr spike) override;

	/** Handles broadcast messages sent during acquisition
		Called automatically whenever a broadcast message is sent through the signal chain */
	void handleBroadcastMessage(String message) override;

	/** Saving custom settings to XML. This method is not needed to save the state of
		Parameter objects */
	void saveCustomParametersToXml(XmlElement* parentElement) override;

	/** Load custom settings from XML. This method is not needed to load the state of
		Parameter objects*/
	void loadCustomParametersFromXml(XmlElement* parentElement) override;

};

#endif