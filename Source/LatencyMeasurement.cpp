#include <zmq.hpp>
#include "LatencyMeasurement.h"
#include "LatencyMeasurementEditor.h"

LatencyMeasurement::LatencyMeasurement()
    : GenericProcessor("Latency Measurement"),
      context(1),  // 1 is the number of I/O threads in the context
      socket(context, ZMQ_PUB)  // ZMQ_PUB means this socket will be publishing messages
{
    socket.bind("tcp://*:5555");  // Replace with your specific address and port
}

LatencyMeasurement::~LatencyMeasurement()
{
    socket.close();
    context.close();
}

AudioProcessorEditor* LatencyMeasurement::createEditor()
{
    editor = std::make_unique<LatencyMeasurementEditor>(this);
    return editor.get();
}

void LatencyMeasurement::updateSettings()
{
    // Implement this method if you need to update settings
}

void LatencyMeasurement::process(AudioBuffer<float>& buffer)
{
    // Get the current timestamp
    uint64 timestamp = getTimestamp(0);

    // Convert the timestamp to a string or other appropriate format
    std::string timestampStr = std::to_string(timestamp);

    // Send the timestamp via ZMQ
    zmq::message_t message(timestampStr.size());
    memcpy(message.data(), timestampStr.data(), timestampStr.size());
    socket.send(message);

    // Call the parent class's process method
    GenericProcessor::process(buffer);
}