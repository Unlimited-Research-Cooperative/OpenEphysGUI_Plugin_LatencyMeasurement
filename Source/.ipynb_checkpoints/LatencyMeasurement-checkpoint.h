#ifndef LATENCY_MEASUREMENT_H
#define LATENCY_MEASUREMENT_H

#include "JuceHeader.h"
#include "ProcessorHeaders.h"

class LatencyMeasurement : public GenericProcessor
{
public:
    /** Constructor */
    LatencyMeasurement();

    /** Destructor */
    virtual ~LatencyMeasurement();

    /** Creates and returns the plugin's editor */
    AudioProcessorEditor* createEditor() override;

    /** Called when the settings of the processor are updated */
    void updateSettings() override;

    /** Processes the incoming audio buffer */
    void process(AudioBuffer<float>& buffer) override;

    /** Handles incoming TTL events */
    void handleTTLEvent(TTLEventPtr event);

    /** Handles incoming spikes */
    void handleSpike(SpikePtr spike);

    /** Handles broadcast messages */
    void handleBroadcastMessage(String message);

    /** Saves custom parameters to an XML element */
    void saveCustomParametersToXml(XmlElement* parentElement) override;

    /** Loads custom parameters from an XML element */
    void loadCustomParametersFromXml(XmlElement* parentElement) override;

private:
    zmq::context_t context;
    zmq::socket_t socket;
};

#endif // LATENCY_MEASUREMENT_H
